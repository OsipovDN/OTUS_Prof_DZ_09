#pragma once
#include<memory>

#include "IObserver.h"

class ToFile :public IObserver{
private:
	std::shared_ptr<ISubject> _subject;
public:
	ToFile(std::shared_ptr<ISubject> obj){
		_subject = obj;
		this->_subject->attach(shared_from_this());
	};
	void update()override {
	
	};
	~ToFile() {
		this->_subject->detach(shared_from_this());
	};

};

class ToCOut :public IObserver {
private:
	std::shared_ptr<ISubject> _subject;
public:
	ToCOut(std::shared_ptr<ISubject> obj) {
		_subject = obj;
		this->_subject->attach(shared_from_this());
	};
	void update()override {};
	~ToCOut() {
		this->_subject->detach(shared_from_this());
	};

};