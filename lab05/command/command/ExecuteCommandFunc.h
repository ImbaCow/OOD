#pragma once
#include "pch.h"
#include "ICommand.h"

typedef std::function<void(std::unique_ptr<ICommand>&& commandPtr)> ExecuteCommandFunc;
