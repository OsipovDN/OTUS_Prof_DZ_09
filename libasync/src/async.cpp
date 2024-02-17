#include <sstream>
#include <memory>
#include "ComandDistr.h"
#include "Observers.h"
#include "async.h"

namespace async {

    handle_t connect(std::size_t bulk) {
        return std::make_unique<lib::ComandDistr>(bulk).release();
    }

    void receive(handle_t handler, const char* data, std::size_t size) {

        auto controller = static_cast<lib::ComandDistr*>(handler);
        if (handler == nullptr)
            return;

        std::istringstream stream (std::string(data,size));
        std::string temp;
        while (stream >> temp)
            controller->addComand(temp);

    }

    void disconnect(handle_t ) {

    }

}
