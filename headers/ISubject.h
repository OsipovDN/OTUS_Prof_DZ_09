#pragma once
#include "IObserver.h"


class ISubject {

public:
	virtual void attach(IObserver*) = 0;
	virtual void detach(IObserver*) = 0;
	virtual void notify() = 0;
	virtual ~ISubject() {};

};