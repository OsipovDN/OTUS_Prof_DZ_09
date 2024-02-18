#include "ComandController.h"

namespace libComand
{
	void ComandController::attach(std::unique_ptr<IObserver> obj)
	{
		if (std::find(_observers.cbegin(), _observers.cend(), obj) == _observers.cend())
			_observers.emplace_back(obj.release());
	}
	void ComandController::detach(std::unique_ptr<IObserver> obj)
	{
		_observers.remove(obj);
	}

	void ComandController::detachAll()
	{
		if (!_observers.empty())
			_observers.clear();
	}
	void ComandController::notify(std::vector<std::string>& block)
	{
		for (auto& object : _observers)
			object->update(block);
	}

	ComandController::ComandController(std::size_t count) :scope_block(0), is_open(false)
	{
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
			notify(st_pl_cmd);
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
				notify(st_pl_cmd);
				st_pl_cmd.clear();
			}
			else if (scope_block == 0 && !is_open)
			{
				addDynBlock(temp);
				notify(dn_pl_cmd);
				dn_pl_cmd.clear();
			}
		}
		if (scope_block == 0 && dn_pl_cmd.size() == 0)
			addStBlock(cmd);
		else
			temp.emplace_back(cmd);
		if (st_pl_cmd.size() != 0)
		{
			notify(st_pl_cmd);
			st_pl_cmd.clear();
		}

	}
}