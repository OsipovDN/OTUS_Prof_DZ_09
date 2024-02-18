#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "IObserver.h"
#include "ISubject.h"

using PullBlock = std::vector<std::string>;

namespace libComand
{
	class ComandController : public ISubject {
	private:
		PullBlock st_pl_cmd;
		PullBlock dn_pl_cmd;
		size_t scope_block;
		bool is_open;
		std::list<std::unique_ptr<IObserver>> _observers;

		bool isScope(const std::string& str);
		void addStBlock(const std::string& str);
		void addDynBlock(PullBlock& obj);

	public:
		//ISubject
		void attach(std::unique_ptr<IObserver> obj) override;
		void detach(std::unique_ptr<IObserver> obj) override;
		void detachAll() override;
		void notify(std::vector<std::string>& block) override;
		//ISubject

		explicit ComandController(std::size_t count);
		~ComandController() {};
		void addComand(std::string cmd);








	};
}