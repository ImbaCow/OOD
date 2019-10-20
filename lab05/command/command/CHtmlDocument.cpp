#include "pch.h"
#include "CHtmlDocument.h"
#include "CParagraph.h"
#include "CImage.h"
#include "CInsertDocumentItemCommand.h"
#include "CDeleteDocumentItemCommand.h"
#include "CReplaceTextCommand.h"
#include "CResizeImageCommand.h"

std::shared_ptr<IParagraph> CHtmlDocument::InsertParagraph(const std::string& text, std::optional<size_t> position)
{
	std::shared_ptr<IParagraph> paragraphPtr = std::make_shared<CParagraph>(m_history, text);
	CDocumentItem documentItem(paragraphPtr);

	std::unique_ptr<ICommand> commandPtr = std::make_unique<CInsertDocumentItemCommand>(documentItem, m_documentItemArr, position);
	m_history.ExecuteCommand(std::move(commandPtr));

	return paragraphPtr;
}

size_t TMP_FILENAME_SIZE = 32;

std::string GenTmpFileName()
{
	std::mt19937 generator{ std::random_device{}() };
	std::uniform_int_distribution<int> distribution{ 'a', 'z' };

	std::string resultName(TMP_FILENAME_SIZE, '\0');
	for (auto& ch : resultName)
	{
		ch = static_cast<char>(distribution(generator));
	}

	return resultName;
}

Path GetCopiedImagePath(const Path& oldPath)
{
	Path tempPath = (std::filesystem::temp_directory_path() / GenTmpFileName()).replace_extension(oldPath.extension());
	std::filesystem::copy_file(oldPath, tempPath);

	return tempPath;
}

std::shared_ptr<IImage> CHtmlDocument::InsertImage(const Path& path, int width, int height, std::optional<size_t> position)
{
	std::shared_ptr<IImage> imagePtr = std::make_shared<CImage>(m_history, GetCopiedImagePath(path), width, height);
	CDocumentItem documentItem(imagePtr);
	
	std::unique_ptr<ICommand> commandPtr = std::make_unique<CInsertDocumentItemCommand>(documentItem, m_documentItemArr, position);
	m_history.ExecuteCommand(std::move(commandPtr));

	return imagePtr;
}

size_t CHtmlDocument::GetItemsCount() const
{
	return m_documentItemArr.size();
}

CConstDocumentItem CHtmlDocument::GetItem(size_t index) const
{
	if (index >= m_documentItemArr.size())
	{
		throw std::out_of_range("Document item position out of range");
	}
	return m_documentItemArr[index];
}

CDocumentItem CHtmlDocument::GetItem(size_t index)
{
	if (index >= m_documentItemArr.size())
	{
		throw std::out_of_range("Document item position out of range");
	}
	return m_documentItemArr[index];
}

void CHtmlDocument::DeleteItem(size_t index)
{
	std::unique_ptr<ICommand> commandPtr = std::make_unique<CDeleteDocumentItemCommand>(m_documentItemArr, index);
	m_history.ExecuteCommand(std::move(commandPtr));
}

std::string CHtmlDocument::GetTitle() const
{
	return m_title;
}

void CHtmlDocument::SetTitle(const std::string& title)
{
	std::unique_ptr<ICommand> commandPtr = std::make_unique<CReplaceTextCommand>(m_title, title);
	m_history.ExecuteCommand(std::move(commandPtr));
}

const std::string IMAGES_DIR_NAME = "images";
const std::string INDEX_HTML_NAME = "index.html";

Path CopyImage(const Path& imageFilePath, const Path& targetDirPath)
{
	Path newImagePath = targetDirPath / imageFilePath.filename();
	std::filesystem::copy_file(imageFilePath, newImagePath);

	return newImagePath;
}

Path CreateImagesDir(const Path& targetPath)
{
	Path imageDir = targetPath / IMAGES_DIR_NAME;
	std::filesystem::create_directory(imageDir);

	return imageDir;
}

Path GetIndexHtmlFilePath(const Path& targetPath)
{
	return targetPath / INDEX_HTML_NAME;
}

std::string ImageToHtml(std::shared_ptr<const IImage> imagePtr, const Path& relativeImagePath)
{
	return "<img src=\"" + relativeImagePath.string() + "\" width=\"" + std::to_string(imagePtr->GetWidth()) + "\" height=\"" + std::to_string(imagePtr->GetHeight()) + "\">";
}

std::string ExcapeHtml(const std::string& text)
{
	std::string escapedText;
	escapedText.reserve(text.size());
	for (auto ch : text)
	{
		switch (ch)
		{
		case '<':
			escapedText += "&lt;";
			break;
		case '>':
			escapedText += "&gt;";
			break;
		case '&':
			escapedText += "&amp;";
			break;
		case '"':
			escapedText += "&quot;";
			break;
		case '\'':
			escapedText += "&apos;";
			break;
		default:
			escapedText += ch;
			break;
		}
	}

	return escapedText;
}

std::string ParagrapgToHtml(std::shared_ptr<const IParagraph> paragraphPtr)
{
	return "<p>" + ExcapeHtml(paragraphPtr->GetText()) + "</p>";
}

std::string OpenHtml(const std::string& title)
{
	std::string titleTag = title.size() != 0 ? "<title>" + title + "</title>" : "";
	return "<html><head>" + titleTag + "</head><body>";
}

std::string CloseHtml()
{
	return "</body></html>";
}

void CHtmlDocument::Save(const Path& path) const
{
	Path imageDir = CreateImagesDir(path);
	std::ofstream indexHtml(GetIndexHtmlFilePath(path));
	indexHtml << OpenHtml(m_title);

	for (const CConstDocumentItem& documentItem : m_documentItemArr)
	{
		std::shared_ptr<const IImage> imagePtr = documentItem.GetImage();
		if (imagePtr)
		{
			Path newImagePath = CopyImage(imagePtr->GetPath(), imageDir);
			Path relativeImagePath = std::filesystem::relative(newImagePath, path);
			indexHtml << ImageToHtml(imagePtr, relativeImagePath);
		}
		else
		{
			indexHtml << ParagrapgToHtml(documentItem.GetParagraph());
		}
	}
	indexHtml << CloseHtml();
}

bool CHtmlDocument::CanUndo() const
{
	return m_history.CanUndo();
}

bool CHtmlDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CHtmlDocument::Undo()
{
	m_history.Undo();
}

void CHtmlDocument::Redo()
{
	m_history.Redo();
}
