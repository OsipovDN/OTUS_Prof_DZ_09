#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include "ComandDistr.h"
#include "Observers.h"

bool isDig(char* arg) {
	std::string num = arg;
	auto isdig = [](char ch) {return std::isdigit(ch); };
	return std::all_of(num.cbegin(), num.cend(), isdig);
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cout << "Incorrect argument input" << std::endl;
		exit(1);
	}
	if (!isDig(argv[1])) {
		std::cout << "Not a val" << std::endl;
		exit(1);
	}
	int count = atoi(argv[1]);

	ComandDistr CmdDis(count);

	auto save_to_file = std::make_shared <ToFile>();
	auto save_to_cout = std::make_shared <ToCOut>();

	CmdDis.attach(save_to_file);
	CmdDis.attach(save_to_cout);

	CmdDis.run();


	return 0;
}
