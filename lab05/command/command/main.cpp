#pragma once
#include "pch.h"
#include "CHtmlDocument.h"
#include "CEditor.h"

using namespace std;
namespace fs = std::filesystem;

void WriteRandomString()
{
	for (size_t i = 0; i < 10; ++i)
	{

		std::mt19937 generator{ std::random_device{}() };
		std::uniform_int_distribution<int> distribution{ 'A', 'Z' };

		std::string resultName(30, '\0');
		for (auto& ch : resultName)
		{
			ch = static_cast<char>(distribution(generator));
		}
		cout << resultName << endl;
	}
}

void GenDir()
{
	fs::create_directories(std::filesystem::current_path() / "abc/test");
	cout << (std::filesystem::current_path() / "abc/test").string() << endl;
	cout << fs::relative(std::filesystem::current_path() / "abc/test").string() << endl;
	cout << fs::relative(std::filesystem::current_path() / "abc/test", std::filesystem::current_path() / "abc") << endl;
}

void CopyFile()
{
	fs::create_directories(std::filesystem::current_path() / "abc");
	Path from = fs::current_path() / "CAbstractCommand.cpp";
	fs::copy_file(from, (fs::current_path() / "abc" /  "pop").replace_extension(from.extension()));
}

void Test1()
{
	CHtmlDocument document;
	document.InsertImage(Path("C:/Users/Егор/Pictures/40v9h9I.png"), 100, 100);
	document.GetItem(0).GetImage()->Resize(50, 50);
	document.InsertParagraph("some text", 0);
	document.InsertParagraph("some textwww", 0);
	document.InsertImage(Path("C:/Users/Егор/Pictures/bonbishka.jpg"), 100, 100, 0);
	document.GetItem(0).GetImage()->Resize(50, 50);
	document.Undo();
	document.Save(fs::current_path() / "abc");
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); 
	CEditor editor(cin, cout);
	editor.Run();
}
