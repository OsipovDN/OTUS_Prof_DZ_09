#pragma once
#include<memory>

class IObserver {

public:
	virtual void update() = 0;
	virtual ~IObserver() {};
};




