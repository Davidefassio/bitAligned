#pragma once

#include <cstdint>
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>

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
 * A vector in which every element has nbit and is bit aligned so no bit is wasted
 */
/*
Public interface:
	Constructor
		default
		from std::vector<bitElement<nbit>>
		from std::vector<std::string>
		from count, bitElement<nbit>
		from count, std::string
		copy
		move

	Destructor

	Operator=
		Copy
		Move

	toVector
		() -> std::vector<bitElement<nbit>>
		() -> std::vector<std::string>

	at
		std::uint64_t -> bitElement<nbit>
		std::uint64_t -> std::string

	operator[]
		std::uint64_t -> bitElement<nbit>
		std::uint64_t -> std::string

	data: () -> std::uint8_t*

	empty: () -> bool
	size: () -> std::uint64_t
	reserve: std::uint64_t -> void
	capacity: () -> std::uint64_t
	shrink_to_fit: () -> void

	clear: () -> void
	insert: 
		(std::uint64_t, bitElement<nbit>) -> void
		(std::uint64_t, std::string) -> void
	erase: (std::uint64_t) -> void
	push_back: 
		bitElement<nbit> -> void
		std::string -> void
	pop_back: () -> void
	resize: (std::uint64_t) -> void


Private implementation:
	data: pointer to the raw data
	size: number of elements in the array
	capacity: max number of element that can be stored in the vector before needing a reallocation
*/
template <std::uint64_t nbit>
class bitAlignedVector
{
public:
	// Default constructor
	bitAlignedVector() : data(nullptr), size(0), capacity(0)
	{
	}

	// Constrcutor from std::vector<bitElement<nbit>>
	bitAlignedVector(const std::vector<bitElement<nbit>>& vec)
	{
		std::uint64_t
		data = new std::uint8_t[]
	}

private:
	std::uint8_t* data;
	std::uint64_t size;
	std::uint64_t capacity;
};