#pragma once
#include <IPublisher.h>

class IQueue : public IPublisher
{
public:
	//IPublisher
	void attach(std::unique_ptr<IObserver> obj) override = 0;
	void detach(std::unique_ptr<IObserver> obj) override = 0;
	void detachAll() override = 0;
	void notify(std::vector<std::string>& block) override = 0;
	//IPublisher


	virtual void push(std::vector <std::string>& massage) = 0;
	virtual void pop() = 0;
	virtual  std::vector <std::string>& front() = 0;
	virtual void wait() = 0;
	~IQueue()=default;
};