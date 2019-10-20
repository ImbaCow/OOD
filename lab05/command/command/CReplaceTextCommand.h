#pragma once
#include "pch.h"
#include "IParagraph.h"
#include "CAbstractCommand.h"

class CReplaceTextCommand : public CAbstractCommand
{
public:
	CReplaceTextCommand(std::string& textContainer, const std::string& nextText);
	virtual ~CReplaceTextCommand() = default;

protected:
	virtual void DoExecute() override;
	virtual void DoUnexecute() override;

private:
	std::string& m_textContainer;
	std::string m_nextText;
};
