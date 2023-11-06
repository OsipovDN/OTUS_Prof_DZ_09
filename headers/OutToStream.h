#pragma once
#include<memory>

#include"PubSub.h"

class ToFile :public IObserver {
private:
	ISubject *distr;
public:
	ToFile(ISubject *obj):distr(obj){
		this->distr->attach(this);
	};
	void update()override {
	
	};
	~ToFile() {
		this->distr->detach(this);
	};

};

class ToCOut :public IObserver{
private:
	ISubject *distr;
public:
	ToCOut(ISubject *obj) :distr(obj) {
		this->distr->attach(this);
	};
	void update()override {};
	~ToCOut() {
		this->distr->detach(this);
	};

};