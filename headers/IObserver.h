#pragma once
#include <memory>

class IObserver: public std::enable_shared_from_this<IObserver>{
public:
	virtual void update(std::vector<std::string>& obj) = 0;
	virtual ~IObserver() {};
};




