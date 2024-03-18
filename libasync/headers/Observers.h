#pragma once

#include <IObserver.h>
#include <IQueue.h>
#include <vector>
#include <thread>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>

class ToFile :public IObserver {
private:
	std::weak_ptr<IQueue> _queue;
	size_t _thr_count;
	std::vector<std::thread> _thr;

	std::string getNameFile();
	bool printToStream(std::ofstream& stream);

public:
	ToFile(std::shared_ptr<IQueue> queue, size_t thr_count) :
		_queue(queue),
		_thr_count(thr_count)
	{
		_thr.reserve(2);
	}
	bool update() override;
};

class ToCOut :public IObserver {
private:
	std::weak_ptr<IQueue> _queue;
	size_t _thr_count;
	std::vector<std::thread> _thr;

	bool printToStream();
public:
	ToCOut(std::shared_ptr<IQueue> queue, size_t thr_count) :
		_queue(queue), 
		_thr_count(thr_count)
	{
		_thr.reserve(2);
	}
	bool update() override;
};