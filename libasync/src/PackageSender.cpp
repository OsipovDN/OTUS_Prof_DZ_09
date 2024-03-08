#include "PackageSender.h"

namespace Sender {
	void PackageSender::printQueue()
	{
		for (const auto& it : _queue.back())
		{
			for (const auto& i : it)
			{
				std::cout << i << " ";
			}

		}
		std::cout << std::endl;
	}

	void PackageSender::attach(std::unique_ptr<IObserver> obj, size_t count)
	{
		for (auto i = 0; i < count; ++i)
		{
			if (std::find(_observers.cbegin(), _observers.cend(), obj) == _observers.cend())
				_observers.emplace_back(obj.release());
		}
	}
	void PackageSender::detach(std::unique_ptr<IObserver> obj)
	{
		auto it = std::find(_observers.cbegin(), _observers.cend(), obj);
		if (it != _observers.cend())
		{
			_observers.erase(std::find(_observers.cbegin(), _observers.cend(), obj));
		}
	}
	void PackageSender::detachAll()
	{
		if (!_observers.empty())
			_observers.clear();
	}

	void PackageSender::notify(std::vector<std::string>& block)
	{
		for (auto& object : _observers)
			if (!object->update(block))
				continue;
	}

	void PackageSender::push(std::vector <std::string>& massage)
	{
		std::unique_lock<std::mutex> lg(_mut);
		_queue.push(massage);

		lg.unlock();
		if (_queue.empty())
		{
			_condition.notify_all();
		}
		printQueue();
	}

	std::vector <std::string>& PackageSender::front()
	{
		std::unique_lock<std::mutex> lg(_mut);
		return _queue.front();
	}

	void PackageSender::pop()
	{
		std::unique_lock<std::mutex> lg(_mut);
		_queue.pop();
	}

	void PackageSender::wait()
	{
		std::unique_lock<std::mutex> lg(_mut);
		while (_queue.empty())
		{
			_condition.wait(lg);
		}
	}
}