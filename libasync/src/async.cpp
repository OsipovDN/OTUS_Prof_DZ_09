#include <sstream>
#include <memory>
#include <algorithm>

#include "CommandController.h"
#include "Observers.h"
#include "async.h"

namespace async {


	handle_t connect(std::size_t bulk) {
		auto msgSender=std::make_unique<Sender::PackageSender>();
		msgSender->attach(std::make_unique<ToFile>());
		msgSender->attach(std::make_unique<ToFile>());
		msgSender->attach(std::make_unique<ToCOut>());
		

		return std::make_unique<Controller::CommandController>(std::move(msgSender), bulk).release();
	}

	void receive(handle_t handler, const char* data, std::size_t size) {

		auto controller = static_cast<Controller::CommandController*>(handler);
		if (handler == nullptr)
			return;

		std::istringstream stream(std::string(data, size));
		std::string temp;

		while (stream >> temp)
			controller->addCommand(temp);

		controller = nullptr;

	}

	void disconnect(handle_t handler) {
		receive(std::move(handler), "EOF", 3);
		if (handler != nullptr)
		{
			delete handler;
		}
	}

}
