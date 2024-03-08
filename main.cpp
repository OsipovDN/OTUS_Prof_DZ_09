
//namespace std::
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
//namespace async::
#include <async.h>
#include "CommandController.h"

bool isDig(char* arg) 
{
	std::string num = arg;
	auto isdig = [](char ch) {return std::isdigit(ch); };
	return std::all_of(num.cbegin(), num.cend(), isdig);
}

int main(int argc, char* argv[])
{
	std::size_t bulk;
	if (argc == 1)
	{
		bulk = 5;
		std::cout << "The number of commands is not specified by the user.By default, the number of commands is "<< bulk << std::endl;
	}
	else if (argc == 2)
	{
		if (!isDig(argv[1]))
		{
			std::cout << "Not a val" << std::endl;
			exit(1);
		}
		bulk = atoi(argv[1]);
	}
	else
	{
		std::cout << "Something is wrong" << std::endl;
		exit(1);
	}

	auto h = async::connect(bulk);
	auto h2 = async::connect(bulk);

	async::receive(h, "1", 1);
	async::receive(h2, "1\n", 2);
	async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
	async::receive(h, "b\nc\nd\n}\n89\n", 11);

	async::disconnect(h);
	async::disconnect(h2);

	return 0;
}