#include "pch.h"
#include "CResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(int& widthContainer, int& heightContainer, int newWidth, int newHeight)
	: m_widthHeightContainer(widthContainer, heightContainer)
	, m_nextWidthHeight(newWidth, newHeight)
{
}

void CResizeImageCommand::DoExecute()
{
	SwapPairs();
}

void CResizeImageCommand::DoUnexecute()
{
	SwapPairs();
}

void CResizeImageCommand::SwapPairs()
{
	std::swap(m_widthHeightContainer.first, m_nextWidthHeight.first);
	std::swap(m_widthHeightContainer.second, m_nextWidthHeight.second);
}
