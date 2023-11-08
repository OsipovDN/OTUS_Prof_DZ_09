#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>

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

	bool isScope(const std::string& str);
	void addStBlock(const std::string& str);
	void addDynBlock(PullBlock& obj);

public:
	explicit ComandDistr(int count);
	void run();

	void attach(std::shared_ptr<IObserver> obj) override;
	void detach(std::shared_ptr<IObserver> obj) override;
	void notify(std::vector<std::string>& block) override;
	~ComandDistr() {};

	
	

};