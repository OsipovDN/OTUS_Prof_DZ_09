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
		//������� ��������� ��� ������
		std::queue<Command> _queue;
		bool _finish;

		std::mutex _mut;

	public:
		MassageQueue() :_finish(false) {};
		MassageQueue(MassageQueue&) = delete;
		MassageQueue operator =(MassageQueue&) = delete;
		~MassageQueue() = default;

		//IQueue
		void push(Command& massage) override;
		Command& front() override;
		void pop() override;
		bool empty() const override;
		bool isFinish()const override { return _finish; };
		void finish() override { _finish = true; };
		//IQueue

		void print(Command& c)const;
	};
}