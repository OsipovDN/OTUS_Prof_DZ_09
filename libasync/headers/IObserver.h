#pragma once

class IObserver {
public:
	virtual bool update(std::vector<std::string>& obj) = 0;
	virtual ~IObserver() {};
};




