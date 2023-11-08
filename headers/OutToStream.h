#pragma once
#include<memory>

#include "IObserver.h"


class ToFile :public IObserver, std::enable_shared_from_this<IObserver>{
private:
	std::shared_ptr<ComandDistr> _subject;

public:
	ToFile(ComandDistr &obj){
		_subject = std::make_shared<ComandDistr>(obj);
	};

	void update()override {
		
	}
	~ToFile() {
	};

};

class ToCOut :public IObserver, std::enable_shared_from_this<IObserver> {
private:
	std::shared_ptr<ComandDistr> _subject;
public:
	ToCOut(ComandDistr &obj) {
		_subject = std::make_shared<ComandDistr>(obj);
	};
	void update()override {};
	~ToCOut() {};

};