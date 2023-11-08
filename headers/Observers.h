#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "IObserver.h"



class ToFile :public IObserver {
private:
	std::string getNameFile();
	void printToStream(std::ofstream& stream, std::vector<std::string>& block);
public:
	void update(std::vector<std::string>& block) override;
	~ToFile() {};
};

class ToCOut :public IObserver {
private:
	void printToStream(std::vector<std::string>& block);
public:
	void update(std::vector<std::string>& block) override;
	~ToCOut() {};
};