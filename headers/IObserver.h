#pragma once
#include<memory>

#include "ISubject.h"

class IObserver {

public:
	virtual void update() = 0;
	virtual ~IObserver() {};
};


