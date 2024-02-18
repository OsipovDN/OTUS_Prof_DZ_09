#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include <IObserver.h>
#include <PackageSender.h>

using PullBlock = std::vector<std::string>;

class PackageSender;

namespace Controller
{
	class ComandController {
	private:
		std::unique_ptr<Sender::PackageSender> _msgQueue;

		PullBlock st_pl_cmd;
		PullBlock dn_pl_cmd;
		size_t scope_block;
		bool is_open;
		std::list<std::unique_ptr<IObserver>> _observers;

		bool isScope(const std::string& str);
		void addStBlock(const std::string& str);
		void addDynBlock(PullBlock& obj);

	public:

		ComandController(std::unique_ptr<Sender::PackageSender> q,std::size_t count);
		~ComandController() {};
		void addComand(std::string cmd);

	};
}