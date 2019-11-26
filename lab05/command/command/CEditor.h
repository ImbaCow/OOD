#pragma once
#include "CHtmlDocument.h"
#include "CCommandMenu.h"

class CEditor
{
public:
	CEditor(std::istream& input, std::ostream& output);
	
	void Run();

private:
	typedef void (CEditor::*Command)(std::istream& input);

	CCommandMenu m_menu;
	CHtmlDocument m_document;
	std::ostream& m_output;

	void InsertParagraph(std::istream& input);
	void InsertImage(std::istream& input);
	void SetTitle(std::istream& input);
	void ReplaceText(std::istream& input);
	void ResizeImage(std::istream& input);
	void DeleteItem(std::istream& input);
	void Save(std::istream& input);
	void Undo(std::istream&);
	void Redo(std::istream&);
	void List(std::istream&);

	void InitCommands();
	void AddCommand(const std::string& shortcut, const std::string& description, Command handler);
};
