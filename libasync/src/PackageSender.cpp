#include "PackageSender.h"

namespace Sender {

	void PackageSender::attach(std::unique_ptr<IObserver> obj)
	{
		if (std::find(_observers.cbegin(), _observers.cend(), obj) == _observers.cend())
			_observers.emplace_back(obj.release());
	}
	void PackageSender::detach(std::unique_ptr<IObserver> obj)
	{
		_observers.remove(obj);
	}

	void PackageSender::detachAll()
	{
		if (!_observers.empty())
			_observers.clear();
	}
	void PackageSender::notify(std::vector<std::string>& block)
	{
		for (auto& object : _observers)
			object->update(block);
	}


	void PackageSender::putMsg(std::vector <std::string>& massage)
	{
		_queue.push(massage);
	}

	std::vector <std::string> PackageSender::getMsg()
	{
		if (_queue.empty())
		{
			std::cerr << "Container is empty" << std::endl;
			return std::vector<std::string>();
		}
		return _queue.front();

	}
}