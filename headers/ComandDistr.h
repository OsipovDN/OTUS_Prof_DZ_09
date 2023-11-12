#pragma once
#include <vector>
#include <deque>
#include <list>
#include <chrono>
#include <fstream>

#include "ISubject.h"
#include "IObserver.h"

using StaticPullBlock = std::vector<std::string>;
using DynamicPullBlock = std::deque<std::string>;


class ComandDistr: public ISubject {
private:
	StaticPullBlock st_pl_cmd;
	DynamicPullBlock dn_pl_cmd;
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
	void detach(std::shared_ptr<IObserver> obj) override {
		_observers.remove(obj);
	}
	void notify() {
		for (auto object : _observers) {
			object->update();
		}
	}
	~ComandDistr(){};
	
	void run();
	bool isScope(const std::string& str);
	void addStBlock(const std::string& str);
	void addDynBlock(DynamicPullBlock& obj);
	std::string getNameFile();

	template <typename T>
	bool saveBlock(T obj) {
		std::string name = getNameFile();
		std::ofstream file(name);
		if (!file.is_open()) {
			std::cout << "file is not open!" << std::endl;
			return false;
		}
		else {
			printBlockToStream <std::ofstream, T>(file, obj);
			return true;
		}
	}

	template <typename T, typename U>
	void printBlockToStream(T& stream, const U& obj) {
		stream << "bulk: ";
		std::for_each(obj.cbegin(), obj.cend() - 1, [&stream](const std::string& str) {
			stream << str << ",";
			});
		stream << *(obj.cend() - 1) << std::endl;
	}

	
};