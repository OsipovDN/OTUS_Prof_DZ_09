#include "Observers.h"


std::string ToFile::getNameFile()
{
	std::ostringstream idTread;
	std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string name = "bulk" + std::to_string(time) + ".log";
	return name;
}
bool ToFile::printToStream(std::ofstream& stream)
{
	std::shared_ptr < IQueue > q = _queue.lock();
	std::vector<std::string> block = q->wait();

	stream << "bulk: ";
	std::for_each(block.cbegin(), block.cend() - 1, [&stream](const std::string& str) {
		stream << str << ",";
		});
	stream << *(block.cend() - 1) << std::endl;
	return true;
}

bool ToFile::update()
{
	std::string name = getNameFile();
	std::ofstream file(name);
	if (!file.is_open())
	{
		std::cout << "file is not open!" << std::endl;
		return false;
	}
	else
		return printToStream(file);
}

bool ToCOut::printToStream()
{
	std::shared_ptr < IQueue > q = _queue.lock();
	std::vector<std::string> block = q->wait();

	std::cout << "bulk: ";
	std::for_each(block.cbegin(), block.cend() - 1, [](const std::string& str) {
		std::cout << str << ",";
		});
	std::cout << *(block.cend() - 1) << std::endl;
	return true;
}

bool ToCOut::update()
{
	return printToStream();
}


