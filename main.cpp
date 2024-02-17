#include <iostream>
#include <string>
#include <thread>
#include <algorithm>

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
	/*
	std::size_t bulk = 5;
	auto h = async::connect(bulk);
	auto h2 = async::connect(bulk);
	async::receive(h, "1", 1);
	async::receive(h2, "1\n", 2);
	async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
	async::receive(h, "b\nc\nd\n}\n89\n", 11);
	async::disconnect(h);
	async::disconnect(h2);
	*/
	return 0;
}