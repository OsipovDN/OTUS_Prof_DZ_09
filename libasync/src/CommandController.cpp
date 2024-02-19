#include "CommandController.h"

namespace Controller
{
	CommandController::CommandController(std::unique_ptr<Sender::PackageSender> q, std::size_t count) :_scopeBlockCount(0), _isOpen(false)
	{
		_msgQueue = std::move(q);
		_statPull.reserve(count);
	}

	bool CommandController::isScope(const std::string& str)
	{
		if (str == "{") {
			_isOpen = !_isOpen;
			_scopeBlockCount++;
			return true;
		}
		else if (str == "}") {
			_isOpen = !_isOpen;
			_scopeBlockCount--;
			return true;
		}
		else
			return false;
	}

	void CommandController::addStatBlock(const std::string& str)
	{
		if (_statPull.size() != _statPull.capacity())
			_statPull.emplace_back(str);

		if (_statPull.size() == _statPull.capacity()) {
			_msgQueue->putMsg(_statPull);
			_statPull.clear();
		}
	}

	void CommandController::addDynBlock(PullBlock& obj)
	{
		for (const auto& it : obj)
			_dynamPull.emplace_back(it);
		obj.clear();
	}

	void CommandController::addCommand(std::string cmd)
	{
		PullBlock temp;
		if (isScope(cmd))
		{
			if (_statPull.size() != 0 && _isOpen)
			{
				_msgQueue->putMsg(_statPull);
				_statPull.clear();
			}
			else if (_scopeBlockCount == 0 && !_isOpen)
			{
				addDynBlock(temp);
				_msgQueue->putMsg(_dynamPull);
				_dynamPull.clear();
			}
		}
		if (_scopeBlockCount == 0 && _dynamPull.size() == 0)
			addStatBlock(cmd);
		else
			temp.emplace_back(cmd);
		if (_statPull.size() != 0)
		{
			_msgQueue->putMsg(_statPull);
			_statPull.clear();
		}

	}
}