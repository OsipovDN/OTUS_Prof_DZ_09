#pragma once

#include <iostream>
#include <list>
#include <queue>
#include <thread>
#include <condition_variable>
#include <algorithm>

#include <Observers.h>
#include <IQueue.h>

namespace Sender {

	class PackageSender :public IQueue
	{
	private:
		//Очередь сообщений для печати
		std::queue<std::vector <std::string>>  _queue;
		//Различные принтеры для вывода сообщений
		std::list<std::unique_ptr<IObserver>> _observers;

		std::condition_variable _condition;
		std::mutex _mut;


	public:
		PackageSender(int coutThrCount, int fileThrCount)
		{
			for (auto i = 0; i < coutThrCount; ++i)
			{
				attach(std::make_unique<ToCOut>());
			}
			for (auto i = 0; i < fileThrCount; ++i)
			{
				attach(std::make_unique<ToFile>());
			}

		}
		~PackageSender() {};

		//IPublisher
		void attach(std::unique_ptr<IObserver> obj) override;
		void detach(std::unique_ptr<IObserver> obj) override;
		void detachAll() override;
		void notify(std::vector<std::string>& block) override;
		//IPublisher

		//IQueue
		void push(std::vector <std::string>& massage) override;
		void pop() override;
		std::vector <std::string>& front() override;
		void wait() override;
		//IQueue

	};
}