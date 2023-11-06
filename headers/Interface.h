#pragma once

class IObserver {
public:
	virtual void update() = 0;
	virtual ~IObserver() {};
};

class ISubject {
public:
	virtual void attach(IObserver* obj) = 0;
	virtual void detach(IObserver* obj) = 0;
	virtual void notify() = 0;
	virtual ~ISubject() {};

};
