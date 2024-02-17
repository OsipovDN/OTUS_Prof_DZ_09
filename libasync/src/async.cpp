#include <sstream>
#include <memory>
#include "ComandDistr.h"
#include "Observers.h"
#include "async.h"

namespace async {

    handle_t connect(std::size_t bulk) {
        return std::make_unique<lib::ComandDistr>(bulk).release();
    }

    void receive(handle_t handle, const char* data, std::size_t size) {

        std::istringstream stream (std::string(data,size));
        std::string temp;
        while (stream >> temp)
            handle->addComand(temp);

    }

    void disconnect(handle_t handle) {
    }

}
