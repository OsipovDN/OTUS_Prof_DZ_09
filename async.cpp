#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include "ComandDistr.h"
#include "OutToStream.h"

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

	auto CmdDis = std::make_shared <ComandDistr>(count);
	auto save_to_file = new ToFile(CmdDis);
	auto save_to_cout = new ToCOut(CmdDis);


	CmdDis->run();

	
	delete save_to_file;
	delete save_to_cout;



	return 0;
}
