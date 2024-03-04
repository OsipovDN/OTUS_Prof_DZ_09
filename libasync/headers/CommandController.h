#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include <IObserver.h>
#include <IController.h>
#include <PackageSender.h>

using PullBlock = std::vector<std::string>;

class PackageSender;

namespace Controller
{
	class CommandController: public IController {
	private:
		std::unique_ptr<Sender::PackageSender> _msgQueue;

		PullBlock _statPull;
		PullBlock _dynamPull;
		PullBlock _buf;
		size_t _scopeBlockCount;
		bool _isOpen;
		std::list<std::unique_ptr<IObserver>> _observers;

		bool isScope(const std::string& str);
		void addStatBlock(const std::string& str);
		void addDynBlock(PullBlock& obj);

	public:

		CommandController(std::unique_ptr<Sender::PackageSender> q,std::size_t count);
		~CommandController() {};
		void addCommand(std::string &s) override;

	};
}