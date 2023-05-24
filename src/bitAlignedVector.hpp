#pragma once

#include <cstdint>
#include <string>
#include <vector>

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

private:
	std::uint8_t* data;
	std::uint64_t size;
	std::uint64_t capacity;
};