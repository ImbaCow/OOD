#include "pch.h"
#include "CFileInputStream.h"
#include "CFileOutputStream.h"
#include "CEncryptOutputStreamDecorator.h"
#include "CDecryptInputStreamDecorator.h"
#include "CCompressOutputStreamDecorator.h"
#include "CDecompressInputStreamDecorator.h"

using namespace std;

const string ENCRYPT_OPTION = "--encrypt";
const string DECRYPT_OPTION = "--decrypt";
const string COMPRESS_OPTION = "--compress";
const string DECOMPRESS_OPTION = "--decompress";

void HandleArgs(const vector<string>& args)
{
	if (args.size() < 3)
	{
		throw logic_error("Not enough arguments");
	}

	unique_ptr<IInputStream> input = make_unique<CFileInputStream>(args[args.size() - 2]);
	unique_ptr<IOutputStream> output = make_unique<CFileOutputStream>(args[args.size() - 1]);

	for (size_t i = 1; i < args.size() - 2; ++i)
	{
		if (args[i] == ENCRYPT_OPTION)
		{
			size_t key = boost::lexical_cast<size_t>(args[++i]);
			output = make_unique<CEncryptOutputStreamDecorator>(move(output), key);
		}
		else if (args[i] == DECRYPT_OPTION)
		{
			size_t key = boost::lexical_cast<size_t>(args[++i]);
			input = make_unique<CDecryptInputStreamDecorator>(move(input), key);
		}
		else if (args[i] == COMPRESS_OPTION)
		{
			output = make_unique<CCompressOutputStreamDecorator>(move(output));
		}
		else if (args[i] == DECOMPRESS_OPTION)
		{
			input = make_unique<CDecompressInputStreamDecorator>(move(input));
		}
		else
		{
			throw logic_error("Unhandled option");
		}
	}

	bool isContinue = true;
	while (isContinue)
	{
		uint8_t ch = input->ReadByte();
		isContinue = !input->IsEOF();
		if (isContinue)
		{
			output->WriteByte(ch);
		}
	};
}

int main(int argc, char* argv[])
{
	vector<string> args(argv, argv + argc);
	//vector<string> args{ "", ENCRYPT_OPTION, "123", COMPRESS_OPTION, ENCRYPT_OPTION, "42", "input.txt", "output.txt" };
	//vector<string> args{ "", DECRYPT_OPTION, "123", DECOMPRESS_OPTION, DECRYPT_OPTION, "42", "output.txt", "out.txt" };
	try
	{
		HandleArgs(args);
	}
	catch (const std::exception& exception)
	{
		cerr << exception.what() << endl;
	}
}
