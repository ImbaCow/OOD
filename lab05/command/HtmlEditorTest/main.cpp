#pragma once
#include "pch.h"
#include "CHtmlDocument.h"
#include "CCommandMenu.h"
#include "CAbstractCommand.h"
#include "CEditor.h"
#include "CReplaceTextCommand.h"
#include "CResizeImageCommand.h"
#include "CInsertDocumentItemCommand.h"
#include "CDeleteDocumentItemCommand.h"
#include "CImage.h"
#include "CParagraph.h"

#define BOOST_TEST_MODULE HtmlEditorTest
#include <boost/test/unit_test.hpp>

using namespace std;
namespace fs = filesystem;

string GetFileContent(const Path& filePath)
{
	std::ifstream in(filePath, ios::binary);

	std::stringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

string MakeImgHtml(const string& fileName, int width, int height)
{
	return "<img src=\"images\\" + fileName + "\" width=\"" + to_string(width) + "\" height=\"" + to_string(height) + "\">";
}

class TestFile
{
public:
	TestFile(const string& name, const string& content)
		: m_name(name)
	{
		fs::create_directory(m_path);
		std::ofstream output(m_path / m_name);
		output << content;
	}

	Path GetFilePath() const
	{
		return m_path / m_name;
	}

	~TestFile()
	{
		error_code ec;
		fs::remove(m_path / m_name, ec);
		if (fs::is_empty(m_path, ec))
		{
			fs::remove(m_path, ec);
		}
	}

private:
	string m_name;
	Path m_path = "./test";
};

class TestDir
{
public:
	TestDir()
	{
		fs::create_directory(m_path);
	}

	Path GetDirPath() const
	{
		return m_path;
	}

	~TestDir()
	{
		error_code ec;
		fs::remove_all(m_path, ec);
	}

private:
	Path m_path = "./test";
};

BOOST_AUTO_TEST_SUITE(HtmlEditorTest)

	BOOST_AUTO_TEST_SUITE(TestHtmlDocument)

		BOOST_AUTO_TEST_SUITE(TestDocumentInsert)
			BOOST_AUTO_TEST_CASE(TestInsertParagraphEnd)
			{
				CHtmlDocument doc;

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 0u);
				doc.InsertParagraph("test text");

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 1u);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() != nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetParagraph()->GetText(), "test text");

				doc.InsertParagraph("text test 22");

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 2u);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() != nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetImage() == nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetParagraph()->GetText(), "test text");

				BOOST_CHECK(doc.GetItem(1u).GetParagraph() != nullptr);
				BOOST_CHECK(doc.GetItem(1u).GetImage() == nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetParagraph()->GetText(), "text test 22");
			}
			BOOST_AUTO_TEST_CASE(TestInsertParagraph)
			{
				CHtmlDocument doc;

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 0u);
				doc.InsertParagraph("random text");
				doc.InsertParagraph("test ", 0u);

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 2u);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() != nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetImage() == nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetParagraph()->GetText(), "test ");

				BOOST_CHECK(doc.GetItem(1u).GetParagraph() != nullptr);
				BOOST_CHECK(doc.GetItem(1u).GetImage() == nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetParagraph()->GetText(), "random text");
			}
			BOOST_AUTO_TEST_CASE(TestInsertImage)
			{
				CHtmlDocument doc;
				TestFile img1("img1.png", "content1");
				TestFile img2("img2.png", "2content2");
				doc.InsertImage(img1.GetFilePath(), 11, 22);
				doc.InsertImage(img2.GetFilePath(), 24, 12, 0u);

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 2u);
				BOOST_CHECK(doc.GetItem(0u).GetImage() != nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() == nullptr);
				BOOST_CHECK_EQUAL(GetFileContent(doc.GetItem(0u).GetImage()->GetPath()), "2content2");
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetImage()->GetWidth(), 24);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetImage()->GetHeight(), 12);

				BOOST_CHECK(doc.GetItem(1u).GetImage() != nullptr);
				BOOST_CHECK(doc.GetItem(1u).GetParagraph() == nullptr);
				BOOST_CHECK_EQUAL(GetFileContent(doc.GetItem(1u).GetImage()->GetPath()), "content1");
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetImage()->GetWidth(), 11);
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetImage()->GetHeight(), 22);
			}
			BOOST_AUTO_TEST_CASE(TestInsertSameImage)
			{
				CHtmlDocument doc;
				TestFile img1("img1.png", "content1");
				doc.InsertImage(img1.GetFilePath(), 11, 22);
				doc.InsertImage(img1.GetFilePath(), 24, 12, 0u);

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 2u);
				BOOST_CHECK(doc.GetItem(0u).GetImage() != nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() == nullptr);
				BOOST_CHECK_EQUAL(GetFileContent(doc.GetItem(0u).GetImage()->GetPath()), "content1");
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetImage()->GetWidth(), 24);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetImage()->GetHeight(), 12);

				BOOST_CHECK(doc.GetItem(1u).GetImage() != nullptr);
				BOOST_CHECK(doc.GetItem(1u).GetParagraph() == nullptr);
				BOOST_CHECK_EQUAL(GetFileContent(doc.GetItem(1u).GetImage()->GetPath()), "content1");
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetImage()->GetWidth(), 11);
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetImage()->GetHeight(), 22);

				BOOST_CHECK(doc.GetItem(0u).GetImage()->GetPath().compare(doc.GetItem(1u).GetImage()->GetPath()) != 0);
			}
			BOOST_AUTO_TEST_CASE(TestInsertBoth)
			{
				CHtmlDocument doc;
				TestFile img1("img1.png", "content");
				TestFile img2("img2.png", "contentt");
				doc.InsertParagraph("text between img");
				doc.InsertImage(img1.GetFilePath(), 11, 22);
				doc.InsertImage(img2.GetFilePath(), 24, 12, 0u);

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 3u);
				BOOST_CHECK(doc.GetItem(0u).GetImage() != nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() == nullptr);
				BOOST_CHECK_EQUAL(GetFileContent(doc.GetItem(0u).GetImage()->GetPath()), "contentt");
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetImage()->GetWidth(), 24);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetImage()->GetHeight(), 12);

				BOOST_CHECK(doc.GetItem(1u).GetImage() == nullptr);
				BOOST_CHECK(doc.GetItem(1u).GetParagraph() != nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetParagraph()->GetText(), "text between img");

				BOOST_CHECK(doc.GetItem(2u).GetImage() != nullptr);
				BOOST_CHECK(doc.GetItem(2u).GetParagraph() == nullptr);
				BOOST_CHECK_EQUAL(GetFileContent(doc.GetItem(2u).GetImage()->GetPath()), "content");
				BOOST_CHECK_EQUAL(doc.GetItem(2u).GetImage()->GetWidth(), 11);
				BOOST_CHECK_EQUAL(doc.GetItem(2u).GetImage()->GetHeight(), 22);
			}
			BOOST_AUTO_TEST_CASE(TestInsertUndo)
			{
				CHtmlDocument doc;

				BOOST_CHECK(!doc.CanUndo());
				doc.InsertParagraph("test text 1");
				BOOST_CHECK(doc.CanUndo());
				TestFile img1("img1.png", "content1");
				doc.InsertImage(img1.GetFilePath(), 11, 22);
				BOOST_CHECK(doc.CanUndo());
				doc.Undo();
				BOOST_CHECK(doc.CanUndo());

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 1u);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() != nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetParagraph()->GetText(), "test text 1");

				doc.Undo();
				BOOST_CHECK(!doc.CanUndo());
				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 0u);
			}
			BOOST_AUTO_TEST_CASE(TestInsertRedo)
			{
				CHtmlDocument doc;

				BOOST_CHECK(!doc.CanRedo());
				doc.InsertParagraph("test text 1");
				BOOST_CHECK(!doc.CanRedo());
				TestFile img1("img1.png", "content1");
				doc.InsertImage(img1.GetFilePath(), 11, 22);
				BOOST_CHECK(!doc.CanRedo());
				doc.Undo();
				BOOST_CHECK(doc.CanRedo());
				doc.Undo();
				BOOST_CHECK(doc.CanRedo());
				doc.Redo();
				BOOST_CHECK(doc.CanRedo());

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 1u);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() != nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetParagraph()->GetText(), "test text 1");

				doc.Redo();
				BOOST_CHECK(!doc.CanRedo());

				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 2u);
				BOOST_CHECK(doc.GetItem(0u).GetImage() == nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() != nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetParagraph()->GetText(), "test text 1");

				BOOST_CHECK(doc.GetItem(1u).GetImage() != nullptr);
				BOOST_CHECK(doc.GetItem(1u).GetParagraph() == nullptr);
				BOOST_CHECK_EQUAL(GetFileContent(doc.GetItem(1u).GetImage()->GetPath()), "content1");
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetImage()->GetWidth(), 11);
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetImage()->GetHeight(), 22);
			}
			BOOST_AUTO_TEST_CASE(TestInsertError)
			{
				CHtmlDocument doc;
				doc.InsertParagraph("test text 1");
				BOOST_CHECK_THROW(doc.InsertParagraph("text1 tesst", 1u), out_of_range);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestDeleteDocumentItem)
			BOOST_AUTO_TEST_CASE(TestDeleteItem)
			{
				CHtmlDocument doc;
				doc.InsertParagraph("test text 1");
				TestFile img1("img1.png", "content1");
				doc.InsertImage(img1.GetFilePath(), 11, 22);

				doc.DeleteItem(0);
				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 1u);
				BOOST_CHECK(doc.GetItem(0u).GetImage() != nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() == nullptr);
				BOOST_CHECK_EQUAL(GetFileContent(doc.GetItem(0u).GetImage()->GetPath()), "content1");
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetImage()->GetWidth(), 11);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetImage()->GetHeight(), 22);

				doc.DeleteItem(0);
				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 0u);
			}
			BOOST_AUTO_TEST_CASE(TestDeleteUndo)
			{
				CHtmlDocument doc;
				doc.InsertParagraph("test text 1");
				TestFile img1("img1.png", "content1");
				doc.InsertImage(img1.GetFilePath(), 11, 22);

				doc.DeleteItem(1);
				BOOST_CHECK(doc.CanUndo());

				doc.DeleteItem(0);
				BOOST_CHECK(doc.CanUndo());

				doc.Undo();
				BOOST_CHECK(doc.CanUndo());
				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 1u);
				BOOST_CHECK(doc.GetItem(0u).GetImage() == nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() != nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetParagraph()->GetText(), "test text 1");

				doc.Undo();
				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 2u);
				BOOST_CHECK(doc.GetItem(0u).GetImage() == nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() != nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetParagraph()->GetText(), "test text 1");

				BOOST_CHECK(doc.GetItem(1u).GetImage() != nullptr);
				BOOST_CHECK(doc.GetItem(1u).GetParagraph() == nullptr);
				BOOST_CHECK_EQUAL(GetFileContent(doc.GetItem(1u).GetImage()->GetPath()), "content1");
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetImage()->GetWidth(), 11);
				BOOST_CHECK_EQUAL(doc.GetItem(1u).GetImage()->GetHeight(), 22);
			}
			BOOST_AUTO_TEST_CASE(TestDeleteRedo)
			{
				CHtmlDocument doc;
				doc.InsertParagraph("test text 1");
				TestFile img1("img1.png", "content1");
				doc.InsertImage(img1.GetFilePath(), 11, 22);

				doc.DeleteItem(1);
				BOOST_CHECK(!doc.CanRedo());
				doc.DeleteItem(0);
				BOOST_CHECK(!doc.CanRedo());
				doc.Undo();
				BOOST_CHECK(doc.CanRedo());
				doc.Undo();
				BOOST_CHECK(doc.CanRedo());

				doc.Redo();
				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 1u);
				BOOST_CHECK(doc.GetItem(0u).GetImage() == nullptr);
				BOOST_CHECK(doc.GetItem(0u).GetParagraph() != nullptr);
				BOOST_CHECK_EQUAL(doc.GetItem(0u).GetParagraph()->GetText(), "test text 1");

				doc.Redo();
				BOOST_CHECK_EQUAL(doc.GetItemsCount(), 0u);
			}
			BOOST_AUTO_TEST_CASE(TestDeleteError)
			{
				CHtmlDocument doc;
				doc.InsertParagraph("test text");
				BOOST_CHECK_THROW(doc.DeleteItem(1u), out_of_range);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestDocumentTitle)
			BOOST_AUTO_TEST_CASE(TestSetTitle)
			{
				CHtmlDocument doc;
				BOOST_CHECK_EQUAL(doc.GetTitle().size(), 0u);

				doc.SetTitle("test title");
				BOOST_CHECK_EQUAL(doc.GetTitle(), "test title");

				doc.SetTitle("another title");
				BOOST_CHECK_EQUAL(doc.GetTitle(), "another title");
			}
			BOOST_AUTO_TEST_CASE(TestTitleUndo)
			{
				CHtmlDocument doc;
				BOOST_CHECK(!doc.CanUndo());

				doc.SetTitle("title test");
				BOOST_CHECK(doc.CanUndo());

				doc.SetTitle("title another");
				BOOST_CHECK(doc.CanUndo());

				doc.Undo();
				BOOST_CHECK_EQUAL(doc.GetTitle(), "title test");
				BOOST_CHECK(doc.CanUndo());

				doc.Undo();
				BOOST_CHECK_EQUAL(doc.GetTitle().size(), 0u);
			}
			BOOST_AUTO_TEST_CASE(TestTitleRedo)
			{
				CHtmlDocument doc;

				doc.SetTitle("test title test");
				doc.SetTitle("another title test");
				doc.Undo();
				doc.Undo();

				doc.Redo();
				BOOST_CHECK(doc.CanRedo());
				BOOST_CHECK_EQUAL(doc.GetTitle(), "test title test");

				doc.Redo();
				BOOST_CHECK_EQUAL(doc.GetTitle(), "another title test");
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestDocumentSave)
			BOOST_AUTO_TEST_CASE(TestEmptySave)
			{
				CHtmlDocument doc;
				TestDir dir;

				doc.Save(dir.GetDirPath());
				BOOST_CHECK(fs::exists(dir.GetDirPath() / "index.html"));
				BOOST_CHECK_EQUAL(GetFileContent(dir.GetDirPath() / "index.html"), "<html><head></head><body></body></html>");
			}
			BOOST_AUTO_TEST_CASE(TestSaveTitle)
			{
				CHtmlDocument doc;
				doc.SetTitle("html save test title");
				TestDir dir;

				doc.Save(dir.GetDirPath());
				BOOST_CHECK(fs::exists(dir.GetDirPath() / "index.html"));
				BOOST_CHECK_EQUAL(GetFileContent(dir.GetDirPath() / "index.html"), "<html><head><title>html save test title</title></head><body></body></html>");
			}
			BOOST_AUTO_TEST_CASE(TestSaveTitleEscape)
			{
				CHtmlDocument doc;
				doc.SetTitle("<p>text&\"'</p>");
				TestDir dir;

				doc.Save(dir.GetDirPath());
				BOOST_CHECK(fs::exists(dir.GetDirPath() / "index.html"));
				BOOST_CHECK_EQUAL(GetFileContent(dir.GetDirPath() / "index.html"), "<html><head><title>&lt;p&gt;text&amp;&quot;&apos;&lt;/p&gt;</title></head><body></body></html>");
			}
			BOOST_AUTO_TEST_CASE(TestSaveImage)
			{
				CHtmlDocument doc;
				TestDir dir;
				TestFile img1("img1.png", "img2 content");
				TestFile img2("img2.png", "img1 content");
				doc.InsertImage(img1.GetFilePath(), 120, 110);
				doc.InsertImage(img2.GetFilePath(), 20, 10);

				doc.Save(dir.GetDirPath());
				BOOST_CHECK(fs::exists(dir.GetDirPath() / "index.html"));
				BOOST_CHECK_EQUAL(GetFileContent(dir.GetDirPath() / "index.html"),
					"<html><head></head><body>"
						+ MakeImgHtml(doc.GetItem(0).GetImage()->GetPath().filename().string(), 120, 110)
						+ MakeImgHtml(doc.GetItem(1).GetImage()->GetPath().filename().string(), 20, 10)
						+ "</body></html>");
				BOOST_CHECK(fs::exists(dir.GetDirPath() / "images" / doc.GetItem(0).GetImage()->GetPath().filename()));
				BOOST_CHECK_EQUAL(GetFileContent(dir.GetDirPath() / "images" / doc.GetItem(0).GetImage()->GetPath().filename()), "img2 content");
				BOOST_CHECK_EQUAL(GetFileContent(dir.GetDirPath() / "images" / doc.GetItem(1).GetImage()->GetPath().filename()), "img1 content");
			}
			BOOST_AUTO_TEST_CASE(TestSaveParagraph)
			{
				CHtmlDocument doc;
				TestDir dir;
				doc.InsertParagraph("test 1");
				doc.InsertParagraph("test 2");

				doc.Save(dir.GetDirPath());
				BOOST_CHECK(fs::exists(dir.GetDirPath() / "index.html"));
				BOOST_CHECK_EQUAL(GetFileContent(dir.GetDirPath() / "index.html"), "<html><head></head><body><p>test 1</p><p>test 2</p></body></html>");
				BOOST_CHECK(fs::is_empty(dir.GetDirPath() / "images"));
			}
			BOOST_AUTO_TEST_CASE(TestSaveParagraphEscape)
			{
				CHtmlDocument doc;
				TestDir dir;
				doc.InsertParagraph("<p>text&\"'</p>");

				doc.Save(dir.GetDirPath());
				BOOST_CHECK(fs::exists(dir.GetDirPath() / "index.html"));
				BOOST_CHECK_EQUAL(GetFileContent(dir.GetDirPath() / "index.html"), "<html><head></head><body><p>&lt;p&gt;text&amp;&quot;&apos;&lt;/p&gt;</p></body></html>");
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestCommandMenu)
		BOOST_AUTO_TEST_CASE(TestCommandRunStart)
		{
			istringstream in;
			ostringstream out;
			CCommandMenu menu(in, out);
			menu.AddCommand("test", "test descr", [&out](std::istream& inp) { string str; inp >> str; out << str; });
			menu.Run();

			BOOST_CHECK_EQUAL(out.str(), "test: test descr\n>");
		}
		BOOST_AUTO_TEST_CASE(TestCommand)
		{
			istringstream in("test testString");
			ostringstream out;
			CCommandMenu menu(in, out);
			menu.AddCommand("test", "test descr", [&out](std::istream& inp) { string str; inp >> str; out << str; });
			menu.Run();

			BOOST_CHECK_EQUAL(out.str(), "test: test descr\n>testString>");
		}
		BOOST_AUTO_TEST_CASE(TestSameCommand)
		{
			istringstream in("test testString");
			ostringstream out;
			CCommandMenu menu(in, out);
			menu.AddCommand("test", "test1 descr", [&out](std::istream& inp) { string str; inp >> str; out << str; });
			menu.AddCommand("test", "test2 descr", [&out](std::istream&) { out << "text"; });
			menu.Run();

			BOOST_CHECK_EQUAL(out.str(), "test: test2 descr\n>text>");
		}
		BOOST_AUTO_TEST_CASE(TestShowCommand)
		{
			istringstream in("test");
			ostringstream out;
			CCommandMenu menu(in, out);
			menu.AddCommand("test", "d", [&out](std::istream&) { out << "testStr"; });
			menu.ShowCommands();
			menu.Run();

			BOOST_CHECK_EQUAL(out.str(), "test: d\ntest: d\n>testStr>");
		}
		BOOST_AUTO_TEST_CASE(TestExitCommand)
		{
			istringstream in("test\nexit\ntest");
			ostringstream out;
			CCommandMenu menu(in, out);
			menu.AddCommand("test", "d", [&out](std::istream&) { out << "testStr"; });
			menu.AddCommand("exit", "d", [&menu](std::istream&) { menu.Exit(); });
			menu.Run();

			BOOST_CHECK_EQUAL(out.str(), "exit: d\ntest: d\n>testStr>");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestCommandHistory)

		class TestCommand : public CAbstractCommand
		{
		public:
			virtual ~TestCommand() = default;

		protected:
			virtual void DoExecute() override
			{
				throw exception("test");
			}
			virtual void DoUnexecute() override
			{
			}
		};

		BOOST_AUTO_TEST_CASE(TestThrowCommand)
		{
			CCommandHistory history;

			BOOST_CHECK(!history.CanUndo());
			BOOST_CHECK(!history.CanRedo());
			unique_ptr<ICommand> command = make_unique<TestCommand>();
			BOOST_CHECK_THROW(history.ExecuteCommand(move(command)), exception);
			BOOST_CHECK(!history.CanUndo());
			BOOST_CHECK(!history.CanRedo());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestCommands)
		BOOST_AUTO_TEST_CASE(TestReplaceTextCommand)
		{
			string container = "first";
			string newText = "second";
			CReplaceTextCommand command(container, newText);

			command.Execute();
			BOOST_CHECK_EQUAL(container, "second");
			command.Execute();
			BOOST_CHECK_EQUAL(container, "second");

			command.Unexecute();
			BOOST_CHECK_EQUAL(container, "first");
			command.Unexecute();
			BOOST_CHECK_EQUAL(container, "first");
		}
		BOOST_AUTO_TEST_CASE(TestResizeImageCommand)
		{
			int widthContainer = 32;
			int heightContainer = 23;

			int newWidth = 10;
			int newHeight = 20;
			CResizeImageCommand command(widthContainer, heightContainer, newWidth, newHeight);

			command.Execute();
			BOOST_CHECK_EQUAL(widthContainer, 10);
			BOOST_CHECK_EQUAL(heightContainer, 20);
			command.Execute();
			BOOST_CHECK_EQUAL(widthContainer, 10);
			BOOST_CHECK_EQUAL(heightContainer, 20);

			command.Unexecute();
			BOOST_CHECK_EQUAL(widthContainer, 32);
			BOOST_CHECK_EQUAL(heightContainer, 23);
			command.Unexecute();
			BOOST_CHECK_EQUAL(widthContainer, 32);
			BOOST_CHECK_EQUAL(heightContainer, 23);
		}
		BOOST_AUTO_TEST_CASE(TestInsertDocItemCommand)
		{
			CCommandHistory history;
			ExecuteCommandFunc func = std::bind(&CCommandHistory::ExecuteCommand, &history, std::placeholders::_1);
			shared_ptr<IParagraph> paragraphPtr = make_shared<CParagraph>(func, "test text");
			CDocumentItem item(paragraphPtr);
			vector<CDocumentItem> docItemArr;
			CInsertDocumentItemCommand command(item, docItemArr);

			command.Execute();
			BOOST_CHECK_EQUAL(docItemArr.size(), 1u);
			BOOST_CHECK_EQUAL(docItemArr[0].GetParagraph(), paragraphPtr);
			command.Execute();
			BOOST_CHECK_EQUAL(docItemArr.size(), 1u);
			BOOST_CHECK_EQUAL(docItemArr[0].GetParagraph(), paragraphPtr);

			command.Unexecute();
			BOOST_CHECK_EQUAL(docItemArr.size(), 0u);
			command.Unexecute();
			BOOST_CHECK_EQUAL(docItemArr.size(), 0u);
		}
		BOOST_AUTO_TEST_CASE(TestInsertDocItemCommandError)
		{
			CCommandHistory history;
			ExecuteCommandFunc func = std::bind(&CCommandHistory::ExecuteCommand, &history, std::placeholders::_1);
			shared_ptr<IParagraph> paragraphPtr = make_shared<CParagraph>(func, "test text");
			CDocumentItem item(paragraphPtr);
			vector<CDocumentItem> docItemArr;
			CInsertDocumentItemCommand command(item, docItemArr, 1);

			BOOST_CHECK_THROW(command.Execute(), out_of_range);
		}
		BOOST_AUTO_TEST_CASE(TestDeleteDocItemCommand)
		{
			CCommandHistory history;
			ExecuteCommandFunc func = std::bind(&CCommandHistory::ExecuteCommand, &history, std::placeholders::_1);
			shared_ptr<IParagraph> paragraphPtr = make_shared<CParagraph>(func, "test text");
			CDocumentItem item(paragraphPtr);
			vector<CDocumentItem> docItemArr{ item };
			CDeleteDocumentItemCommand command(docItemArr, 0);

			command.Execute();
			BOOST_CHECK_EQUAL(docItemArr.size(), 0u);
			command.Execute();
			BOOST_CHECK_EQUAL(docItemArr.size(), 0u);

			command.Unexecute();
			BOOST_CHECK_EQUAL(docItemArr.size(), 1u);
			BOOST_CHECK_EQUAL(docItemArr[0].GetParagraph(), paragraphPtr);
			command.Unexecute();
			BOOST_CHECK_EQUAL(docItemArr.size(), 1u);
			BOOST_CHECK_EQUAL(docItemArr[0].GetParagraph(), paragraphPtr);
		}
		BOOST_AUTO_TEST_CASE(TestDeleteDocItemCommandError)
		{
			CCommandHistory history;
			ExecuteCommandFunc func = std::bind(&CCommandHistory::ExecuteCommand, &history, std::placeholders::_1);
			shared_ptr<IParagraph> paragraphPtr = make_shared<CParagraph>(func, "test text");
			CDocumentItem item(paragraphPtr);
			vector<CDocumentItem> docItemArr{ item };
			CDeleteDocumentItemCommand command(docItemArr, 1);

			BOOST_CHECK_THROW(command.Execute(), out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TestEditor)

		const string EDITOR_HELP_TEXT = R"(DeleteItem: DeleteItem <позиция>
Exit: Exit
Help: Help
InsertImage: InsertImage <позиция>|end <ширина> <высота> <путь к файлу изображения>
InsertParagraph: InsertParagraph <позиция>|end <текст параграфа>
List: List
Redo: Redo
ReplaceText: ReplaceText <позиция> <текст параграфа>
ResizeImage: ResizeImage <позиция> <ширина> <высота>
Save: Save <путь>
SetTitle: SetTitle <заголовок документа>
Undo: Undo
)";

		BOOST_AUTO_TEST_CASE(TestRun)
		{
			istringstream in;
			ostringstream out;
			CEditor editor(in, out);

			editor.Run();
			BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + '>');
		}
		BOOST_AUTO_TEST_CASE(TestHelp)
		{
			istringstream in("Help");
			ostringstream out;
			CEditor editor(in, out);

			editor.Run();
			BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + '>' + EDITOR_HELP_TEXT + '>');
		}
		BOOST_AUTO_TEST_CASE(TestExit)
		{
			istringstream in("Exit\nHelp");
			ostringstream out;
			CEditor editor(in, out);

			editor.Run();
			BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + '>');
		}
		BOOST_AUTO_TEST_SUITE(TestSaveCommand)
			BOOST_AUTO_TEST_CASE(TestSaveEmpty)
			{
				TestDir dir;
				istringstream in("Save " + dir.GetDirPath().string());
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(GetFileContent(dir.GetDirPath() / "index.html"), "<html><head></head><body></body></html>");
			}
			BOOST_AUTO_TEST_CASE(TestSaveEmptyPath)
			{
				istringstream in("Save");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">Empty save directory given\n>");
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestInsertParagraph)
			BOOST_AUTO_TEST_CASE(TestInsert)
			{
				istringstream in("InsertParagraph end text test\nInsertParagraph 0 test text\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>0. Paragraph: test text\n1. Paragraph: text test\n>");
			}
			BOOST_AUTO_TEST_CASE(TestInsertEmpty)
			{
				istringstream in("InsertParagraph end\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>0. Paragraph: \n>");
			}
			BOOST_AUTO_TEST_CASE(TestInsertErrorPosition)
			{
				istringstream in("InsertParagraph endd text1\nInsertParagraph 1 text2\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">Invalid position argument: endd given\n>Document item position is out of range\n>>");
			}
			BOOST_AUTO_TEST_CASE(TestInsertUndo)
			{
				istringstream in("InsertParagraph end text test\nInsertParagraph 0 test text\nUndo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>>0. Paragraph: text test\n>");
			}
			BOOST_AUTO_TEST_CASE(TestInsertRedo)
			{
				istringstream in("InsertParagraph end text test\nInsertParagraph 0 test text\nUndo\nRedo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>>>0. Paragraph: test text\n1. Paragraph: text test\n>");
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestInsertImage)
			BOOST_AUTO_TEST_CASE(TestInsertErrorPosition)
			{
				TestFile img("img1.png", "content1");
				istringstream in("InsertImage endd 10 20 " + img.GetFilePath().string() + "\nInsertImage 1 22 33 " + img.GetFilePath().string() + "\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">Invalid position argument: endd given\n>Document item position is out of range\n>>");
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestReplaceText)
			BOOST_AUTO_TEST_CASE(TestReplace)
			{
				istringstream in("InsertParagraph end text test\nReplaceText 0 test text\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>0. Paragraph: test text\n>");
			}
			BOOST_AUTO_TEST_CASE(TestReplaceErrorPosition)
			{
				istringstream in("InsertParagraph end text test\nReplaceText 1 test text\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>Document item position out of range\n>0. Paragraph: text test\n>");
			}
			BOOST_AUTO_TEST_CASE(TestReplaceUndo)
			{
				istringstream in("InsertParagraph end text test\nReplaceText 0 test text\nUndo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>>0. Paragraph: text test\n>");
			}
			BOOST_AUTO_TEST_CASE(TestReplaceRedo)
			{
				istringstream in("InsertParagraph end text test\nReplaceText 0 test text\nUndo\nRedo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>>>0. Paragraph: test text\n>");
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestSetTitleCommand)
			BOOST_AUTO_TEST_CASE(TestSetTitle)
			{
				istringstream in("SetTitle test title test\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>Title: test title test\n>");
			}
			BOOST_AUTO_TEST_CASE(TestSetEmpty)
			{
				istringstream in("SetTitle\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>");
			}
			BOOST_AUTO_TEST_CASE(TestSetTitleUndo)
			{
				istringstream in("SetTitle title1\nSetTitle title2\nUndo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>>Title: title1\n>");
			}
			BOOST_AUTO_TEST_CASE(TestSetTitleRedo)
			{
				istringstream in("SetTitle title1\nSetTitle title2\nUndo\nRedo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>>>Title: title2\n>");
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestDeleteItemCommand)
			BOOST_AUTO_TEST_CASE(TestDelete)
			{
				istringstream in("InsertParagraph end text test\nInsertParagraph end test text\nDeleteItem 0\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>>0. Paragraph: test text\n>");
			}
			BOOST_AUTO_TEST_CASE(TestDeleteErrorPosition)
			{
				istringstream in("InsertParagraph end text test\nInsertParagraph end test text\nDeleteItem 2\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>Document item position is out of range\n>0. Paragraph: text test\n1. Paragraph: test text\n>");
			}
			BOOST_AUTO_TEST_CASE(TestDeleteUndo)
			{
				istringstream in("InsertParagraph end text test\nInsertParagraph end test text\nDeleteItem 0\nUndo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>>>0. Paragraph: text test\n1. Paragraph: test text\n>");
			}
			BOOST_AUTO_TEST_CASE(TestDeleteRedo)
			{
				istringstream in("InsertParagraph end text test\nInsertParagraph end test text\nDeleteItem 0\nUndo\nRedo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">>>>>>0. Paragraph: test text\n>");
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestUndoCommand)
			BOOST_AUTO_TEST_CASE(TestUndoError)
			{
				istringstream in("Undo\nInsertParagraph end test\nUndo\nUndo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">Can't undo\n>>>Can't undo\n>>");
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestRedoCommand)
			BOOST_AUTO_TEST_CASE(TestRedoError)
			{
				istringstream in("Redo\nInsertParagraph end test\nUndo\nRedo\nRedo\nList");
				ostringstream out;
				CEditor editor(in, out);

				editor.Run();
				BOOST_CHECK_EQUAL(out.str(), EDITOR_HELP_TEXT + ">Can't redo\n>>>>Can't redo\n>0. Paragraph: test\n>");
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
