#pragma once
#include "ICommand.h"

class CCommandHistory
{
public:
	virtual bool CanUndo() const;
	virtual bool CanRedo() const;
	virtual void Undo();
	virtual void Redo();
	void ExecuteCommand(std::unique_ptr<ICommand>&& commandPtr);

private:
	std::deque<std::unique_ptr<ICommand>> m_historyQueue;
	size_t m_nextCommandIndex = 0;
};
