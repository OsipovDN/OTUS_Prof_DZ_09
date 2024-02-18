#pragma once

#include <IObserver.h>

class ToFile :public IObserver {
private:
	std::string getNameFile();
	void printToStream(std::ofstream& stream, std::vector<std::string>& block);
public:
	void update(std::vector<std::string>& block) override;
};

class ToCOut :public IObserver {
private:
	void printToStream(std::vector<std::string>& block);
public:
	void update(std::vector<std::string>& block) override;
};