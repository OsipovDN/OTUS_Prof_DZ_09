#pragma once
#include<memory>

#include "ISubject.h"

class IObserver: public std::enable_shared_from_this<IObserver> {

public:
	virtual void update() = 0;
	virtual ~IObserver() {};
};


