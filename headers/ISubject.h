#pragma once
#include "IObserver.h"


class ISubject {

public:
	virtual void attach(std::shared_ptr<IObserver>) = 0;
	virtual void detach(std::shared_ptr<IObserver>) = 0;
	virtual void notify() = 0;
	virtual ~ISubject() {};

};