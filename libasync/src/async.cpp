#include <sstream>
#include <memory>

#include "ComandController.h"
#include "Observers.h"
#include "async.h"

namespace async {

	handle_t connect(std::size_t bulk) {
		auto msgSender=std::make_unique<Sender::PackageSender>();
		msgSender->attach(std::make_unique<ToFile>());
		msgSender->attach(std::make_unique<ToFile>());
		msgSender->attach(std::make_unique<ToCOut>());


		return std::move(new Controller::ComandController(std::move(msgSender), bulk));
	}

	void receive(handle_t handler, const char* data, std::size_t size) {

		auto controller = static_cast<Controller::ComandController*>(handler);
		if (handler == nullptr)
			return;

		std::istringstream stream(std::string(data, size));
		std::string temp;

		while (stream >> temp)
			controller->addComand(temp);

	}

	void disconnect(handle_t handler) {
		receive(handler, "EOF", 1);
		if (handler != nullptr)
		{
			delete handler;
		}
	}

}
