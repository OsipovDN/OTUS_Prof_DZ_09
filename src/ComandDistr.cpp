#include "ComandDistr.h"

ComandDistr::ComandDistr(int count) :scope_block(0), is_open(false) {
	st_pl_cmd.reserve(count);
}

bool ComandDistr::isScope(const std::string& str) {
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

void ComandDistr::addStBlock(const std::string& str) {
	if (st_pl_cmd.size() != st_pl_cmd.capacity())
		st_pl_cmd.emplace_back(str);

	if (st_pl_cmd.size() == st_pl_cmd.capacity()) {
		notify(st_pl_cmd);
		st_pl_cmd.clear();
	}
}

void ComandDistr::addDynBlock(PullBlock& obj) {
	for (const auto& it : obj)
		dn_pl_cmd.emplace_back(it);
	obj.clear();
}

void ComandDistr::run() {
	std::string cmd;
	PullBlock temp;
	while (std::getline(std::cin, cmd)) {
		if (isScope(cmd)) {
			if (st_pl_cmd.size() != 0 && is_open) {
				notify(st_pl_cmd);
				st_pl_cmd.clear();
			}
			else if (scope_block == 0 && !is_open) {
				addDynBlock(temp);
				notify(dn_pl_cmd);
				dn_pl_cmd.clear();
			}
			continue;
		}
		if (scope_block == 0 && dn_pl_cmd.size() == 0)
			addStBlock(cmd);
		else
			temp.emplace_back(cmd);
	}
	if (st_pl_cmd.size() != 0) {
		notify(st_pl_cmd);
		st_pl_cmd.clear();
	}
}

void ComandDistr::attach(std::shared_ptr<IObserver> obj) {
	if (std::find(_observers.cbegin(), _observers.cend(), obj) == _observers.cend())
		_observers.emplace_back(obj);
}
void ComandDistr::detach(std::shared_ptr<IObserver> obj) {
	_observers.remove(obj);
}
void ComandDistr::notify(std::vector<std::string>& block) {
	for (auto object : _observers)
		object->update(block);
}