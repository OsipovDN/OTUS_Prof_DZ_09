#pragma once
#include<memory>

#include "IObserver.h"


class ToFile :public IObserver, std::enable_shared_from_this<ToFile> {

public:
	ToFile(ISubject &obj) {
		obj.attach(shared_from_this());
	};
	void update()override {};
	~ToFile() {};

};

class ToCOut :public IObserver, std::enable_shared_from_this<ToCOut> {

public:
	ToCOut(ISubject &obj) {
		obj.attach(shared_from_this());
	};
	void update()override {};
	~ToCOut() {};

};