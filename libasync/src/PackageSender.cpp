#include "PackageSender.h"

namespace Sender {

	void PackageSender::attach(std::unique_ptr<IObserver> obj)
	{
		if (std::find(_observers.cbegin(), _observers.cend(), obj) == _observers.cend())
			_observers.emplace_back(obj.release());
	}
	void PackageSender::detach(std::unique_ptr<IObserver> obj)
	{
		auto it=std::find(_observers.cbegin(), _observers.cend(), obj);
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


	void PackageSender::putMsg(std::vector <std::string>& massage)
	{
		for (const auto& it : massage)
		{
			std::cerr << it<<" ";
		}
		std::cerr << std::endl;
		_queue.push(massage);
		notify();
	}
}