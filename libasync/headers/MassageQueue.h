#pragma once

#include <iostream>
#include <queue>

#include <mutex>
#include <thread>

#include <IQueue.h>

namespace msg {
	using Command = std::vector <std::string>;
	class MassageQueue :public IQueue
	{
	private:
		//Очередь сообщений для печати
		std::queue<Command> _queue;

		std::mutex _mut;

	public:
		MassageQueue() {};
		MassageQueue(MassageQueue&) = delete;
		MassageQueue operator =(MassageQueue&) = delete;
		~MassageQueue() = default;

		//IQueue
		void push(Command& massage) override;
		Command& front() override;
		void pop() override;
		bool empty() const override;
		//IQueue

		void print(Command& c)const;
	};
}