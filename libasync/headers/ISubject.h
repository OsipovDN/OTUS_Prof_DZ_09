#pragma once
#include <memory>
#include <string>
#include <vector>

class ISubject {
public:
	virtual void attach(std::unique_ptr<IObserver> obj) = 0;
	virtual void detach(std::unique_ptr<IObserver> obj) = 0;
	virtual void detachAll() = 0;
	virtual void notify(std::vector<std::string> &block) = 0;
	virtual ~ISubject() {};
};