#include <sstream>
#include <string>
#include <iomanip>

std::string ColorToString(std::uint32_t num)
{
	int r = (int)((num >> 16) & 0xff);
	int g = (int)((num >> 8) & 0xff);
	int b = (int)((num >> 0) & 0xff);

	std::stringstream ss;
	ss << std::right << std::setfill('0') << std::setw(2) << std::hex << r;
	ss << std::right << std::setfill('0') << std::setw(2) << std::hex << g;
	ss << std::right << std::setfill('0') << std::setw(2) << std::hex << b;
	return ss.str();
}

