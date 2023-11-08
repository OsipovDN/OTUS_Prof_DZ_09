#pragma once

class IObserver {
public:
	virtual void update(std::vector<std::string>& obj) = 0;
	virtual ~IObserver() {};
};




