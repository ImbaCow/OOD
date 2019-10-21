#pragma once
#include "pch.h"
#include "IParagraph.h"
#include "ExecuteCommandFunc.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(ExecuteCommandFunc executeCommandFunc, const std::string& text);
	virtual ~CParagraph() = default;

	virtual std::string GetText() const override;
	virtual void SetText(const std::string& text) override;

private:
	ExecuteCommandFunc m_executeCommandFunc;
	std::string m_text;
};
