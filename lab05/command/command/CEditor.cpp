#include "pch.h"
#include "CEditor.h"

std::optional<size_t> ParsePos(std::istream& input)
{
	std::string pos;
	input >> pos;
	std::optional<size_t> posOpt = std::nullopt;

	if (std::all_of(pos.begin(), pos.end(), std::isdigit))
	{
		try
		{
			posOpt = boost::lexical_cast<size_t>(pos);
		}
		catch (const std::exception&)
		{
			throw std::invalid_argument("Invalid position argument: " + pos + " given");
		}
	}
	else if (pos != "end")
	{
		throw std::invalid_argument("Invalid position argument: " + pos + " given");
	}

	return posOpt;
}

CEditor::CEditor(std::istream& input, std::ostream& output)
	: m_menu(input, output)
	, m_output(output)
{
	InitCommands();
}

void CEditor::Run()
{
	m_menu.Run();
}

void CEditor::InsertParagraph(std::istream& input)
{
	std::optional<size_t> posOpt = ParsePos(input);
	std::string text;
	std::getline(input >> std::ws, text);

	m_document.InsertParagraph(text, posOpt);
}

void CEditor::InsertImage(std::istream& input)
{
	std::optional<size_t> posOpt = ParsePos(input);
	int width;
	int height;
	Path path;
	input >> width >> height >> path;

	m_document.InsertImage(path, width, height, posOpt);
}

void CEditor::SetTitle(std::istream& input)
{
	std::string title;
	std::getline(input >> std::ws, title);
	m_document.SetTitle(title);
}

void CEditor::ReplaceText(std::istream& input)
{
	std::optional<size_t> posOpt = ParsePos(input);
	if (!posOpt)
	{
		throw std::invalid_argument("Invalid position argument");
	}
	std::shared_ptr<IParagraph> paragraphPtr = m_document.GetItem(posOpt.value()).GetParagraph();
	if (!paragraphPtr)
	{
		throw std::invalid_argument("Document item is not paragraph");
	}
	std::string text;
	std::getline(input >> std::ws, text);

	paragraphPtr->SetText(text);
}

void CEditor::ResizeImage(std::istream& input)
{
	std::optional<size_t> posOpt = ParsePos(input);
	if (!posOpt)
	{
		throw std::invalid_argument("Invalid position argument");
	}
	int width;
	int height;
	input >> width >> height;

	std::shared_ptr<IImage> imagePtr = m_document.GetItem(posOpt.value()).GetImage();
	if (!imagePtr)
	{
		throw std::invalid_argument("Document item is not image");
	}

	imagePtr->Resize(width, height);
}

void CEditor::DeleteItem(std::istream& input)
{
	std::optional<size_t> posOpt = ParsePos(input);
	if (!posOpt)
	{
		throw std::invalid_argument("Invalid position argument");
	}

	m_document.DeleteItem(posOpt.value());
}

void CEditor::Undo(std::istream&)
{
	if (m_document.CanUndo())
	{
		m_document.Undo();
	}
	else
	{
		throw std::logic_error("Can't undo");
	}
}

void CEditor::Redo(std::istream&)
{
	if (m_document.CanRedo())
	{
		m_document.Redo();
	}
	else
	{
		throw std::logic_error("Can't redo");
	}
}

void CEditor::Save(std::istream& input)
{
	std::string path;
	input >> path;

	if (!path.size())
	{
		throw std::invalid_argument("Empty save directory given");
	}
	m_document.Save(path);
}

void CEditor::List(std::istream&)
{
	if (m_document.GetTitle().size())
	{
		m_output << "Title: " << m_document.GetTitle() << std::endl;
	}
	for (size_t i = 0; i < m_document.GetItemsCount(); i++)
	{
		CDocumentItem item = m_document.GetItem(i);
		std::shared_ptr<IImage> imagePtr = item.GetImage();
		if (imagePtr)
		{
			m_output << i << ". Image: " << imagePtr->GetWidth() << ' ' << imagePtr->GetHeight() << ' ' << "images/" << imagePtr->GetPath().filename().string() << std::endl;
		}
		else
		{
			m_output << i << ". Paragraph: " << item.GetParagraph()->GetText() << std::endl;
		}
	}
}

void CEditor::InitCommands()
{
	AddCommand("InsertParagraph", "InsertParagraph <позиция>|end <текст параграфа>", &CEditor::InsertParagraph);
	AddCommand("InsertImage", "InsertImage <позиция>|end <ширина> <высота> <путь к файлу изображения>", &CEditor::InsertImage);
	AddCommand("SetTitle", "SetTitle <заголовок документа>", &CEditor::SetTitle);
	AddCommand("ReplaceText", "ReplaceText <позиция> <текст параграфа>", &CEditor::ReplaceText);
	AddCommand("ResizeImage", "ResizeImage <позиция> <ширина> <высота>", &CEditor::ResizeImage);
	AddCommand("DeleteItem", "DeleteItem <позиция>", &CEditor::DeleteItem);
	m_menu.AddCommand("Help", "Help", [this](std::istream&) { m_menu.ShowCommands(); });
	m_menu.AddCommand("Exit", "Exit", [this](std::istream&) { m_menu.Exit(); });
	AddCommand("Undo", "Undo", &CEditor::Undo);
	AddCommand("Redo", "Redo", &CEditor::Redo);
	AddCommand("List", "List", &CEditor::List);
	AddCommand("Save", "Save <путь>", &CEditor::Save);
}

void CEditor::AddCommand(const std::string& shortcut, const std::string& description, Command handler)
{
	m_menu.AddCommand(shortcut, description, std::bind(handler, this, std::placeholders::_1));
}
