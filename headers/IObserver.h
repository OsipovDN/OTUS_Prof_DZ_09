#pragma once

class IObserver {
public:
	virtual void update(std::vector<std::string>&) = 0;
	virtual ~IObserver() {};
};




