#pragma once
#include <vector>
#include <deque>
#include <list>
#include <chrono>
#include <fstream>

#include "IObserver.h"
#include "ISubject.h"

using PullBlock = std::vector<std::string>;


class ComandDistr : public ISubject {
private:
	PullBlock st_pl_cmd;
	PullBlock dn_pl_cmd;
	size_t scope_block;
	bool is_open;
	std::list<std::shared_ptr<IObserver>> _observers;

public:
	explicit ComandDistr(int count) :scope_block(0), is_open(false) {
		st_pl_cmd.reserve(count);
	}
	void attach(std::shared_ptr<IObserver> obj)override {
		if (std::find(_observers.cbegin(), _observers.cend(), obj) == _observers.cend())
			_observers.emplace_back(obj);
	}
	void detach(std::shared_ptr<IObserver> obj)override {
		_observers.remove(obj);
	}
	void notify(std::vector<std::string> &block)override {

			for (auto object : _observers) {
				object->update(block);
			}
	}
	~ComandDistr() {};

	void run();
	bool isScope(const std::string& str);
	void addStBlock(const std::string& str);
	void addDynBlock(PullBlock& obj);

};