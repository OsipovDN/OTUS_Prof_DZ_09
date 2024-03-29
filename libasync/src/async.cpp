#include <sstream>
#include <memory>
#include <thread>
#include <algorithm>

#include "CommandController.h"
#include "PackageSender.h"
#include "Observers.h"
#include "async.h"

namespace async {

	handle_t connect(std::size_t bulk) {

		static auto msgSender = std::make_shared<Sender::PackageSender>();
		static auto filePrinter = std::make_unique<ToFile>(msgSender,2);
		static auto COutPrinter = std::make_unique<ToCOut>(msgSender,1);
		msgSender->attach(std::move(filePrinter));
		msgSender->attach(std::move(COutPrinter));

		return std::make_unique<Controller::CommandController>(msgSender, bulk).release();
	}

	void receive(handle_t handler, const char* data, std::size_t size) {

		auto controller = static_cast<Controller::CommandController*>(handler);
		if (handler == nullptr)
			return;

		std::istringstream stream(std::string(data, size));

		std::string temp;
		while (stream >> temp)
		{
			controller->addCommand(temp);
		}
		controller = nullptr;
	}

	void disconnect(handle_t handler) {
		receive(std::move(handler), "EOF", 3);
		if (handler != nullptr)
		{
			//delete handler;
		}
	}

}
