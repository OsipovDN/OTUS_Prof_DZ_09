#include "ComandController.h"

namespace Controller
{
	ComandController::ComandController(std::unique_ptr<Sender::PackageSender> q, std::size_t count) :scope_block(0), is_open(false)
	{
		_msgQueue = std::move(q);
		st_pl_cmd.reserve(count);
	}

	bool ComandController::isScope(const std::string& str)
	{
		if (str == "{") {
			is_open = !is_open;
			scope_block++;
			return true;
		}
		else if (str == "}") {
			is_open = !is_open;
			scope_block--;
			return true;
		}
		else
			return false;
	}

	void ComandController::addStBlock(const std::string& str)
	{
		if (st_pl_cmd.size() != st_pl_cmd.capacity())
			st_pl_cmd.emplace_back(str);

		if (st_pl_cmd.size() == st_pl_cmd.capacity()) {
			_msgQueue->notify(st_pl_cmd);
			st_pl_cmd.clear();
		}
	}

	void ComandController::addDynBlock(PullBlock& obj)
	{
		for (const auto& it : obj)
			dn_pl_cmd.emplace_back(it);
		obj.clear();
	}

	void ComandController::addComand(std::string cmd)
	{
		PullBlock temp;
		if (isScope(cmd))
		{
			if (st_pl_cmd.size() != 0 && is_open)
			{
				_msgQueue->putMsg(st_pl_cmd);
				st_pl_cmd.clear();
			}
			else if (scope_block == 0 && !is_open)
			{
				addDynBlock(temp);
				_msgQueue->putMsg(dn_pl_cmd);
				dn_pl_cmd.clear();
			}
		}
		if (scope_block == 0 && dn_pl_cmd.size() == 0)
			addStBlock(cmd);
		else
			temp.emplace_back(cmd);
		if (st_pl_cmd.size() != 0)
		{
			_msgQueue->putMsg(st_pl_cmd);
			st_pl_cmd.clear();
		}

	}
}