#pragma once

#include <cstdint>
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>

/*
 * Type containing n bits in an array of m bytes
 */
template <std::uint64_t nbit>
class bitElement
{
public:
	// Default constructor
	constexpr bitElement() = default;

	// If filler == 0 => all bits to 0, otherwise all bits to 1
	constexpr bitElement(const int filler)
	{
		std::memset(data, ((filler) ? 0xFF : 0), nBytes);
	}

	// Fill data with the bits in the string
	constexpr bitElement(const std::string& bits)
	{
		if (bits.size() != nbit)
			throw std::runtime_error("The string size must match the template.");

		std::memset(data, 0, nBytes);

		int o = 7;
		std::uint64_t b = 0;
		for (std::uint64_t i = 0; i < bits.size(); ++i)
		{
			if (bits[i] == '1')
				data[b] |= (0x01 << o);
			else if (bits[i] != '0')
				throw std::runtime_error("The string must contain only '0' and '1'.");

			if (o == 0)
			{
				o = 7;
				++b;
			}
			else
			{
				--o;
			}
		}
	}

	// Set a bit
	constexpr void set(const std::uint64_t index, const int value)
	{
		if (index >= nbit)
			throw std::runtime_error("The index must be less than nbit.");

		const std::uint64_t b = index >> 3;
		const std::uint8_t off = 7 - (index & 0x07);

		if (value)
			data[b] |= (0x01 << off);
		else
			data[b] &= ~(0x01 << off);
	}

	// Get a bit
	constexpr int get(const std::uint64_t index) const
	{
		if (index >= nbit)
			throw std::runtime_error("The index must be less than nbit.");

		const std::uint64_t b = index >> 3;
		const std::uint8_t off = 7 - (index & 0x07);
		return (data[b] >> off) & 0x01;
	}

	// Get a pointer to the data
	constexpr std::uint8_t* getRawData()
	{
		return data;
	}

	// Convert the internal representation in a string of '0' and '1'
	constexpr std::string toString() const
	{
		std::string retval;

		for (std::uint64_t i = 0; i < nBytes; ++i)
			for (std::int8_t j = 7; j >= 0; --j)
				retval.push_back(((data[i] >> j) & 0x01) ? '1' : '0');

		retval.resize(nbit);
		return retval;
	}

	// Utility
	// Equivalent to std::ceil(x / 8.0)
	static constexpr std::uint64_t ceilDiv8(const std::uint64_t x)
	{
		return (x >> 3) + static_cast<bool>(x & 0x07);
	}

	// Number of bytes needed to contain nbit
	static constexpr std::uint64_t nBytes = ceilDiv8(nbit);

private:
	// Internal data
	std::uint8_t data[nBytes];
};

/*
constexpr std::uint64_t ceilDiv8(const std::uint64_t x)
{
	return (x >> 3) + static_cast<bool>(x & 0x07);
}
*/
