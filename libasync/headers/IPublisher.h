#pragma once
#include <memory>
#include <string>
#include <vector>

#include <IObserver.h>

class IPublisher {
public:
	virtual void attach(std::unique_ptr<IObserver> obj) = 0;
	virtual void detach(std::unique_ptr<IObserver> obj) = 0;
	virtual void detachAll() = 0;
	virtual void notify(std::vector<std::string> &block) = 0;
	virtual ~IPublisher() {};
};