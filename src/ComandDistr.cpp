#include <iostream>
#include <string>
#include <algorithm>

#include "ComandDistr.h"

void ComandDistr::run() {
	std::string cmd;
	DynamicPullBlock temp;
	while (std::getline(std::cin, cmd)) {
		if (isScope(cmd)) {
			if (st_pl_cmd.size() != 0 && is_open) {
				saveBlock(st_pl_cmd);
				printBlockToStream(std::cout, st_pl_cmd);
				st_pl_cmd.clear();
			}
			else if (scope_block == 0 && !is_open) {
				addDynBlock(temp);
				saveBlock(dn_pl_cmd);
				printBlockToStream(std::cout, dn_pl_cmd);
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
		saveBlock(st_pl_cmd);
		printBlockToStream(std::cout, st_pl_cmd);
		st_pl_cmd.clear();
	}
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
		saveBlock(st_pl_cmd);
		printBlockToStream(std::cout, st_pl_cmd);
		st_pl_cmd.clear();
	}
}

void ComandDistr::addDynBlock(DynamicPullBlock& obj) {
	for (const auto& it : obj)
		dn_pl_cmd.emplace_back(it);

	obj.clear();
}

std::string ComandDistr::getNameFile() {
	std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string name = "bulk" + std::to_string(time) + ".log";
	return name;
}