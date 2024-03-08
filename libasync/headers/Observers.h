#pragma once

#include <IObserver.h>

class ToFile :public IObserver {
private:
	bool _isBusy = false;
	std::string getNameFile();
	void printToStream(std::ofstream& stream, std::vector<std::string>& block);
public:
	bool update(std::vector<std::string>& block) override;
};

class ToCOut :public IObserver {
private:
	bool _isBusy = false;
	void printToStream(std::vector<std::string>& block);
public:
	bool update(std::vector<std::string>& block) override;
};