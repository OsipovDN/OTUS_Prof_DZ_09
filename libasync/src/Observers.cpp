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
	idTread << std::this_thread::get_id();
	std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string name = "bulk"+ idTread.str() + std::to_string(time) + ".log";
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

void ToFile::update(std::vector<std::string>& block)  
{
	if (block.size() != 0) {
		std::string name = getNameFile();
		std::ofstream file(name);
		if (!file.is_open())
			std::cout << "file is not open!" << std::endl;
		else
			printToStream(file, block);
	}
}

void ToCOut::printToStream(std::vector<std::string>& block) 
{
	std::cout << "bulk: " << std::this_thread::get_id();
	std::for_each(block.cbegin(), block.cend() - 1, [](const std::string& str) {
		std::cout << str << ",";
		});
	std::cout << *(block.cend() - 1) << std::endl;
}

void ToCOut::update(std::vector<std::string>& block)  
{
	if (block.size() != 0)
		printToStream(block);
}


