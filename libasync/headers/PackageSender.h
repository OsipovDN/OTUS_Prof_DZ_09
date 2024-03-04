#pragma once

#include <iostream>
#include <list>
#include <queue>
#include <algorithm>

#include <IPublisher.h>
#include <IObserver.h>

namespace Sender {

	class PackageSender :public IPublisher
	{
	private:
		//Очередь сообщений для печати
		std::queue<std::vector <std::string>>  _queue;
		//Различные принтеры для вывода сообщений
		std::list<std::unique_ptr<IObserver>> _observers;

	public:
		~PackageSender() {};

		//IPublisher
		void attach(std::unique_ptr<IObserver> obj) override;
		void detach(std::unique_ptr<IObserver> obj) override;
		void detachAll() override;
		void notify(std::vector<std::string>& block) override;
		//IPublisher

		void putMsg(std::vector <std::string>& massage);
		void send();
		std::vector <std::string> getMsg();

	};
}