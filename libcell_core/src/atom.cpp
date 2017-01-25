
#include <cstring>
#include "cell/atom.hpp"

namespace cell {

atom_value atom_from_string(const std::string& x)
{
	if (x.size() > 10)
	{
		return atom("");
	}
	char buf[11];
	memcpy(buf, x.c_str(), x.size());
	buf[x.size()] = '\0';
	return atom(buf);
}

std::string to_string(const atom_value& what)
{
	auto x = static_cast<uint64_t>(what);
	std::string result;
	result.reserve(11);

	bool read_chars = ((x & 0xF000000000000000) >> 60) == 0xF;
	uint64_t mask = 0x0FC0000000000000;
	for (int bitshift = 54; bitshift >= 0; bitshift -= 6, mask >>= 6)
	{
		if (read_chars)
		{
			result += detail::decoding_table[(x & mask) >> bitshift];
		}
		else if (((x & mask) >> bitshift) == 0xF)
		{
			read_chars = true;
		}
	}
	return result;
}



} // namespace cell

