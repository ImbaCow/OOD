#include "pch.h"
#include "CParagraph.h"
#include "CReplaceTextCommand.h"

CParagraph::CParagraph(ExecuteCommandFunc executeCommandFunc, const std::string& text)
	: m_executeCommandFunc(executeCommandFunc)
	, m_text(text)
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const std::string& text)
{
	std::unique_ptr<ICommand> command = std::make_unique<CReplaceTextCommand>(m_text, text);
	m_executeCommandFunc(std::move(command));
}
