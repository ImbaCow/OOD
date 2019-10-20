#pragma once
#include "pch.h"
#include "IParagraph.h"
#include "CCommandHistory.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(CCommandHistory& m_history, const std::string& text);
	virtual ~CParagraph() = default;

	virtual std::string GetText() const override;
	virtual void SetText(const std::string& text) override;

private:
	CCommandHistory& m_history;
	std::string m_text;
};
