#include <sstream>
#include <memory>
#include "ComandController.h"
#include "Observers.h"
#include "async.h"

namespace async {

	handle_t connect(std::size_t bulk) {
		auto temp = new libComand::ComandController(bulk);
		temp->attach(std::make_unique<ToFile>());
		temp->attach(std::make_unique<ToFile>());
		temp->attach(std::make_unique<ToCOut>());
		return std::move(temp);
	}

	void receive(handle_t handler, const char* data, std::size_t size) {

		auto controller = static_cast<libComand::ComandController*>(handler);
		if (handler == nullptr)
			return;

		std::istringstream stream(std::string(data, size));
		std::string temp;

		while (stream >> temp)
			controller->addComand(temp);

	}

	void disconnect(handle_t handler) {
		auto controller = static_cast<libComand::ComandController*>(handler);
		controller->detachAll();
		if (handler != nullptr)
		{
			delete controller;
		}
	}

}
