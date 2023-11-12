#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "ISubject.h"
#include "IObserver.h"




class ToFile :public IObserver {
private:
	std::shared_ptr<ISubject> _subject;

	std::string getNameFile();
	void printToStream(std::ofstream& stream, std::vector<std::string>& block);
public:
	ToFile(std::shared_ptr<ISubject> obj) 
	{
		this->_subject->attach(shared_from_this());	
	}

	void update(std::vector<std::string>& block) override;
	~ToFile() {};
};

class ToCOut :public IObserver {
private:
	std::shared_ptr<ISubject> _subject;

	void printToStream(std::vector<std::string>& block);
public:
	ToCOut(std::shared_ptr<ISubject> obj)
	{
		this->_subject->attach(shared_from_this());
	}
	void update(std::vector<std::string>& block) override;
	~ToCOut() {};
};