#pragma once
#include<memory>

#include "IObserver.h"

class ToFile :public IObserver{
private:
	ISubject* _subject;
public:
	ToFile(ISubject *obj){
		_subject = obj;
		this->_subject->attach(this);
	};
	void update()override {
	
	};
	~ToFile() {
		this->_subject->detach(this);
	};

};

class ToCOut :public IObserver {
private:
	ISubject* _subject;
public:
	ToCOut(ISubject *obj) {
		_subject = obj;
		this->_subject->attach(this);
	};
	void update()override {};
	~ToCOut() {
		this->_subject->detach(this);
	};

};