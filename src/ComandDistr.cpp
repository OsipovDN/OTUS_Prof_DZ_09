#include <iostream>
#include <string>
#include <algorithm>

#include "ComandDistr.h"



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
