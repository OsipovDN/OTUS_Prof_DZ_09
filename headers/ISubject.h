#pragma once

class ISubject {
public:
	virtual void attach(std::shared_ptr<IObserver> obj) = 0;
	virtual void detach(std::shared_ptr<IObserver> obj) = 0;
	virtual void notify() = 0;
	virtual ~ISubject() {};
};