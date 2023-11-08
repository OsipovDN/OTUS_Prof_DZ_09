#pragma once
#include<memory>

#include "IObserver.h"


class ToFile :public IObserver, std::enable_shared_from_this<ToFile>{
private:
	std::shared_ptr<ComandDistr> _subject;	

public:
	ToFile(ComandDistr&obj){
		_subject = std::make_shared<ComandDistr>(obj);
		this->_subject->attach(shared_from_this());
	};

	void update()override {
		
	}
	~ToFile() {
	};

};

class ToCOut :public IObserver, std::enable_shared_from_this<ToCOut> {
private:
	std::shared_ptr<ComandDistr> _subject;
public:
	ToCOut(ComandDistr& obj) {
		_subject = std::make_shared<ComandDistr>(obj);
		this->_subject->attach(shared_from_this());
	};
	void update()override {};
	~ToCOut() {
	};

};