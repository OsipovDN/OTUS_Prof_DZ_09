#pragma once
#include<memory>
#include "IObserver.h"


class ToFile :public IObserver, std::enable_shared_from_this<IObserver> {
private:
	std::string getNameFile() {
		std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string name = "bulk" + std::to_string(time) + ".log";
		return name;
	}
	void printToStream(std::ofstream& stream, std::vector<std::string>& block) {
		stream << "bulk: ";
		std::for_each(block.cbegin(), block.cend() - 1, [&stream](const std::string& str) {
			stream << str << ",";
			});
		stream << *(block.cend() - 1) << std::endl;
	}
public:
	void update(std::vector<std::string>& block)override {
		if (block.size() != 0) {
			std::string name = getNameFile();
			std::ofstream file(name);
			if (!file.is_open())
				std::cout << "file is not open!" << std::endl;
			else
				printToStream(file, block);
		}
	};
	~ToFile() {};
};

class ToCOut :public IObserver, std::enable_shared_from_this<IObserver> {
private:
	void printToStream(std::vector<std::string>& block) {
		std::cout << "bulk: ";
		std::for_each(block.cbegin(), block.cend() - 1, [](const std::string& str) {
			std::cout << str << ",";
			});
		std::cout << *(block.cend() - 1) << std::endl;
	}
public:
	void update(std::vector<std::string>& block)override {
		if (block.size() != 0)
			printToStream(block);
	};
	~ToCOut() {};
};