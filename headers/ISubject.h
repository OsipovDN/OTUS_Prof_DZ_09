#pragma once
#include <memory>
#include <string>
#include <vector>

class ISubject {
public:
	virtual void attach(std::shared_ptr<IObserver> obj) = 0;
	virtual void detach(std::shared_ptr<IObserver> obj) = 0;
	virtual void notify(std::vector<std::string>& block) = 0;
	virtual ~ISubject() {};
};