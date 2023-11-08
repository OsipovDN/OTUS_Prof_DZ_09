#pragma once

class ISubject {
public:
	virtual void attach(std::shared_ptr<IObserver> ) = 0;
	virtual void detach(std::shared_ptr<IObserver> ) = 0;
	virtual void notify(std::vector<std::string>&) = 0;
	virtual ~ISubject() {};
};