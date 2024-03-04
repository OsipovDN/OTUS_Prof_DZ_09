#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <thread>
#include <sstream>

#include "Observers.h"


std::string ToFile::getNameFile() 
{
	std::ostringstream idTread;
	std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string name = "bulk" + std::to_string(time) + ".log";
	return name;
}
void ToFile::printToStream(std::ofstream& stream, std::vector<std::string>& block) 
{
	stream << "bulk: ";
	std::for_each(block.cbegin(), block.cend() - 1, [&stream](const std::string& str) {
		stream << str << ",";
		});
	stream << *(block.cend() - 1) << std::endl;
}

bool ToFile::update(std::vector<std::string>& block)
{
	if (!_isBusy)
	{
		_isBusy = true;
		std::string name = getNameFile();
		std::ofstream file(name);
		if (!file.is_open())
			std::cout << "file is not open!" << std::endl;
		else
			printToStream(file, block);
		_isBusy = false;
		return false;
	}
	else
		return true;
}

void ToCOut::printToStream(std::vector<std::string>& block) 
{
	std::cout << "bulk: ";
	std::for_each(block.cbegin(), block.cend() - 1, [](const std::string& str) {
		std::cout << str << ",";
		});
	std::cout << *(block.cend() - 1) << std::endl;
}

bool ToCOut::update(std::vector<std::string>& block)
{
	if (!_isBusy)
	{
		_isBusy = true;
		printToStream(block);
		_isBusy = false;
		return false;
	}
	else
		return true;
}


