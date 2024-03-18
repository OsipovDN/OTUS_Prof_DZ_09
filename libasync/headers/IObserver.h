#pragma once

class IObserver {
public:

	virtual bool update() = 0;
	virtual ~IObserver()=default;
};




