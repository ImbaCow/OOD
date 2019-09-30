#pragma once
#include "pch.h"
#include "CMemoryInputStream.h"
#include "CFileInputStream.h"
#include "CFileOutputStream.h"
#include "CMemoryOutputStream.h"
#include "CDecompressInputStreamDecorator.h"
#include "CCompressOutputStreamDecorator.h"
#include "CEncryptOutputStreamDecorator.h"
#include "CDecryptInputStreamDecorator.h"

#define BOOST_TEST_MODULE StreamTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestStream)

	BOOST_AUTO_TEST_SUITE(TestMemoryOutputStream)
		BOOST_AUTO_TEST_CASE(TestWriteWhenNotEmpty)
		{
			ostringstream oss("not empty", std::ios_base::ate);
			CMemoryOutputStream stream(oss);

			stream.WriteByte(' ');
			BOOST_CHECK_EQUAL("not empty ", oss.str());
			stream.WriteBlock("value", 5);
			BOOST_CHECK_EQUAL("not empty value", oss.str());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestMemoryInputStream)
		BOOST_AUTO_TEST_CASE(TestReadWhenNotEmpty)
		{
			istringstream iss("not empty");
			CMemoryInputStream stream(iss);

			BOOST_CHECK(!stream.IsEOF());
			BOOST_CHECK_EQUAL(stream.ReadByte(), 'n');
			char* buff = new char[8];
			BOOST_CHECK_EQUAL(8, stream.ReadBlock(buff, 8));
			BOOST_CHECK_EQUAL(string(buff, 8), "ot empty");
			delete[] buff;
		}
		BOOST_AUTO_TEST_CASE(TestReadWhenEmpty)
		{
			istringstream iss;
			CMemoryInputStream stream(iss);

			stream.ReadByte();
			BOOST_CHECK(stream.IsEOF());
			char* buff = new char[4]{ '1', '2', '3', '4' };
			BOOST_CHECK_EQUAL(0, stream.ReadBlock(buff, 4));
			delete[] buff;
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestCompressOutputStream)
		BOOST_AUTO_TEST_CASE(TestWriteByte)
		{
			ostringstream oss;
			unique_ptr<IOutputStream> stream = make_unique<CMemoryOutputStream>(oss);
			stream = make_unique<CCompressOutputStreamDecorator>(move(stream));

			stream->WriteByte('2');
			stream->WriteByte('2');
			stream->WriteByte('3');
			stream->WriteByte('4');
			stream->WriteByte('4');
			stream->WriteByte('4');
			stream.reset();
			BOOST_CHECK_EQUAL(string("\2") + "2\1" + "3\3" + "4", oss.str());
		}
		BOOST_AUTO_TEST_CASE(TestWriteBlock)
		{
			ostringstream oss;
			unique_ptr<IOutputStream> stream = make_unique<CMemoryOutputStream>(oss);
			stream = make_unique<CCompressOutputStreamDecorator>(move(stream));

			stream->WriteBlock("===", 3);
			stream->WriteBlock("vw", 2);
			stream->WriteBlock("0009", 4);
			stream.reset();
			BOOST_CHECK_EQUAL(string("\3") + "=\1v\1w" + "\3" + "0\1" + "9", oss.str());
		}
		BOOST_AUTO_TEST_CASE(TestWriteOverflowBlock)
		{
			ostringstream oss;
			unique_ptr<IOutputStream> stream = make_unique<CMemoryOutputStream>(oss);
			stream = make_unique<CCompressOutputStreamDecorator>(move(stream));

			for (size_t i = 0; i < 255; ++i)
			{
				stream->WriteByte('v');
			}
			stream.reset();
			BOOST_CHECK(0xffffffff == oss.str()[0]);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestDecompressInputStream)
		BOOST_AUTO_TEST_CASE(TestWriteByte)
		{
			istringstream iss("\1v\2d");
			unique_ptr<IInputStream> stream = make_unique<CMemoryInputStream>(iss);
			stream = make_unique<CDecompressInputStreamDecorator>(move(stream));

			BOOST_CHECK(!stream->IsEOF());
			BOOST_CHECK_EQUAL(stream->ReadByte(), 'v');
			BOOST_CHECK(!stream->IsEOF());
			BOOST_CHECK_EQUAL(stream->ReadByte(), 'd');
			BOOST_CHECK_EQUAL(stream->ReadByte(), 'd');
			BOOST_CHECK(!stream->IsEOF());
			stream->ReadByte();
			BOOST_CHECK(stream->IsEOF());
		}
		BOOST_AUTO_TEST_CASE(TestWriteBlock)
		{
			istringstream iss("\1v\3d\2o");
			unique_ptr<IInputStream> stream = make_unique<CMemoryInputStream>(iss);
			stream = make_unique<CDecompressInputStreamDecorator>(move(stream));

			char* buff = new char[6]();
			BOOST_CHECK_EQUAL(3, stream->ReadBlock(buff, 3));
			BOOST_CHECK_EQUAL(string("vdd"), string(buff, 3));
			BOOST_CHECK_EQUAL(3, stream->ReadBlock(buff + 3, 3));
			BOOST_CHECK_EQUAL(string("vdddoo"), string(buff, 6));
			BOOST_CHECK(!stream->IsEOF());
			stream->ReadByte();
			BOOST_CHECK(stream->IsEOF());
			delete[] buff;
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestCryptStream)
		BOOST_AUTO_TEST_CASE(TestByte)
		{
			ostringstream oss;
			unique_ptr<IOutputStream> ostr = make_unique<CMemoryOutputStream>(oss);
			ostr = make_unique<CEncryptOutputStreamDecorator>(move(ostr), 123);

			ostr->WriteByte('2');
			ostr.reset();
			BOOST_CHECK("2" != oss.str());

			istringstream iss(oss.str());
			unique_ptr<IInputStream> istr = make_unique<CMemoryInputStream>(iss);
			istr = make_unique<CDecryptInputStreamDecorator>(move(istr), 123);

			BOOST_CHECK(!istr->IsEOF());
			BOOST_CHECK_EQUAL('2', istr->ReadByte());
			BOOST_CHECK(!istr->IsEOF());
			istr->ReadByte();
			BOOST_CHECK(istr->IsEOF());
		}
		BOOST_AUTO_TEST_CASE(TestBlock)
		{
			ostringstream oss;
			unique_ptr<IOutputStream> ostr = make_unique<CMemoryOutputStream>(oss);
			ostr = make_unique<CEncryptOutputStreamDecorator>(move(ostr), 123);

			ostr->WriteBlock("vdddoo", 6);
			ostr.reset();
			BOOST_CHECK("vdddoo" != oss.str());

			istringstream iss(oss.str());
			unique_ptr<IInputStream> istr = make_unique<CMemoryInputStream>(iss);
			istr = make_unique<CDecryptInputStreamDecorator>(move(istr), 123);

			BOOST_CHECK(!istr->IsEOF());
			char* buff = new char[6]();
			BOOST_CHECK_EQUAL(6, istr->ReadBlock(buff, 6));
			BOOST_CHECK_EQUAL("vdddoo", string(buff, 6));
			BOOST_CHECK(!istr->IsEOF());
			istr->ReadByte();
			BOOST_CHECK(istr->IsEOF());
			delete[] buff;
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestFileStream)
		BOOST_AUTO_TEST_CASE(TestWrite)
		{
			unique_ptr<IOutputStream> ostr = make_unique<CFileOutputStream>("test.txt");

			ostr->WriteByte('0');
			ostr->WriteBlock("000999888", 9);
			ostr.reset();

			unique_ptr<IInputStream> istr = make_unique<CFileInputStream>("test.txt");
			BOOST_CHECK_EQUAL('0', istr->ReadByte());
			char* buff = new char[9];
			BOOST_CHECK_EQUAL(9, istr->ReadBlock(buff, 9));
			BOOST_CHECK_EQUAL("000999888", string(buff, 9));
			delete[] buff;
		}

		BOOST_AUTO_TEST_CASE(TestWriteCompress)
		{
			unique_ptr<IOutputStream> ostr = make_unique<CFileOutputStream>("test.txt");
			ostr = make_unique<CCompressOutputStreamDecorator>(move(ostr));

			ostr->WriteByte('0');
			ostr->WriteBlock("000999888", 9);
			ostr.reset();

			unique_ptr<IInputStream> istr = make_unique<CFileInputStream>("test.txt");
			istr = make_unique<CDecompressInputStreamDecorator>(move(istr));
			BOOST_CHECK_EQUAL('0', istr->ReadByte());
			char* buff = new char[9];
			BOOST_CHECK_EQUAL(9, istr->ReadBlock(buff, 9));
			BOOST_CHECK_EQUAL("000999888", string(buff, 9));
			delete[] buff;
		}

		BOOST_AUTO_TEST_CASE(TestWriteCrypt)
		{
			unique_ptr<IOutputStream> ostr = make_unique<CFileOutputStream>("test.txt");
			ostr = make_unique<CEncryptOutputStreamDecorator>(move(ostr), 321);

			ostr->WriteByte('0');
			ostr->WriteBlock("000999888", 9);
			ostr.reset();

			unique_ptr<IInputStream> istr = make_unique<CFileInputStream>("test.txt");
			istr = make_unique<CDecryptInputStreamDecorator>(move(istr), 321);
			BOOST_CHECK_EQUAL('0', istr->ReadByte());
			char* buff = new char[9];
			BOOST_CHECK_EQUAL(9, istr->ReadBlock(buff, 9));
			BOOST_CHECK_EQUAL("000999888", string(buff, 9));
			delete[] buff;
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()