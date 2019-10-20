#include "pch.h"
#include "CAbstractCommand.h"

void CAbstractCommand::Execute()
{
	if (!m_isExecuted)
	{
		DoExecute();
		m_isExecuted = true;
	}
}

void CAbstractCommand::Unexecute()
{
	if (m_isExecuted)
	{
		DoUnexecute();
		m_isExecuted = false;
	}
}
