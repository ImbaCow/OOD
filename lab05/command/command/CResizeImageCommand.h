#pragma once
#include "pch.h"
#include "CAbstractCommand.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(int& widthContainer, int& heightContainer, int newWidth, int newHeight);
	virtual ~CResizeImageCommand() = default;

protected:
	virtual void DoExecute() override;
	virtual void DoUnexecute() override;

private:
	const std::pair<int&, int&> m_widthHeightContainer;
	std::pair<int, int> m_nextWidthHeight;

	void SwapPairs();
};
