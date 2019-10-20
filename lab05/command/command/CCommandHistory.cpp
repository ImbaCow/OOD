#include "pch.h"
#include "CCommandHistory.h"

const size_t MAX_HISTORY_QUEUE_SIZE = 10;

bool CCommandHistory::CanUndo() const
{
	return m_nextCommandIndex > 0;
}

bool CCommandHistory::CanRedo() const
{
	return m_nextCommandIndex < m_historyQueue.size();
}

void CCommandHistory::Undo()
{
	if (CanUndo())
	{
		m_historyQueue[m_nextCommandIndex - 1]->Unexecute();
		--m_nextCommandIndex;
	}
}

void CCommandHistory::Redo()
{
	if (CanRedo())
	{
		m_historyQueue[m_nextCommandIndex]->Execute();
		++m_nextCommandIndex;
	}
}

void CCommandHistory::ExecuteCommand(std::unique_ptr<ICommand>&& commandPtr)
{
	if (m_nextCommandIndex < m_historyQueue.size())
	{
		commandPtr->Execute();
		m_historyQueue[m_nextCommandIndex++] = std::move(commandPtr);
		m_historyQueue.resize(m_nextCommandIndex);
	}
	else
	{
		m_historyQueue.push_back(nullptr);
		try
		{
			commandPtr->Execute();
			m_historyQueue.back() = std::move(commandPtr);
		}
		catch (...)
		{
			m_historyQueue.pop_back();
			throw;
		}
		if (m_historyQueue.size() > MAX_HISTORY_QUEUE_SIZE)
		{
			m_historyQueue.pop_front();
		}
		else
		{
			++m_nextCommandIndex;
		}
	}
}