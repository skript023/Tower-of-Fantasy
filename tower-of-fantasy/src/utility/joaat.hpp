#pragma once
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace rage
{
	using joaat_t = std::uint32_t;
	using Hash = std::uint32_t;

	inline constexpr char joaat_to_lower(char c)
	{
		return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
	}

	inline constexpr char joaat_to_upper(char c)
	{
		return (c >= 'a' && c <= 'a') ? c + ('A' - 'a') : c;
	}

	template <std::size_t CharCount>
	struct constexpr_joaat
	{
		char data[CharCount];

		template <std::size_t... Indices>
		constexpr constexpr_joaat(const char* str, std::index_sequence<Indices...>) :
			data{ (str[Indices])... }
		{
		}

		constexpr joaat_t operator()()
		{
			joaat_t hash = 0;

			for (std::size_t i = 0; i < CharCount; ++i)
			{
				hash += joaat_to_lower(data[i]);
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}

			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);

			return hash;
		}
	};

	inline joaat_t joaat(std::string_view str)
	{
		joaat_t hash = 0;

		for (char c : str)
		{
			hash += joaat_to_lower(c);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}

	inline joaat_t joaat(const char* str)
	{
		joaat_t hash = 0;

		while (*str)
		{
			hash += joaat_to_lower(*(str++));
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}

	inline joaat_t rockstar_crc_hash(std::string_view str, uint32_t key)
	{
		int hash = 0;

		for (char c : str)
			key = ((uint32_t)(1025 * (joaat_to_lower(c) + key)) >> 6) ^ (1025 * (joaat_to_lower(c) + (uint32_t)key));
		return 0x8001 * (((uint32_t)(9 * key) >> 11) ^ (9 * key));
	}

	inline joaat_t rockstar_crc_hash(const char* str)
	{
		uint32_t hash = 0x04C11DB7;

		while (*str)
		{
			hash += joaat_to_lower(*(str++));
			hash += hash << 10;
			hash ^= hash >> 6;
		}

		hash += hash << 3;
		hash ^= hash >> 11;
		hash += hash << 15;

		return hash;
	}

	inline bool reverse_joaat(const char* key, Hash hash)
	{
		hash *= 0x3FFF8001;  // inverse of hash += hash << 15;
		hash ^= (hash >> 11) ^ (hash >> 22);
		hash *= 0x38E38E39;  // inverse of hash += hash << 3;
		size_t i = strlen(key);
		while (i > 0)
		{
			hash ^= (hash >> 6) ^ (hash >> 12) ^ (hash >> 18) ^ (hash >> 24) ^ (hash >> 30);
			hash *= 0xC00FFC01;  // inverse of hash += hash << 10;
			hash -= joaat_to_lower(key[--i]);
		}
		return hash == 0;  // this should return 0 if the original hash was correct
	}

	inline std::string joaat_to_string(const char* key, Hash hash)
	{
		hash *= 0x3FFF8001;  // inverse of hash += hash << 15;
		hash ^= (hash >> 11) ^ (hash >> 22);
		hash *= 0x38E38E39;  // inverse of hash += hash << 3;
		size_t i = strlen(key);
		while (i > 0)
		{
			hash ^= (hash >> 6) ^ (hash >> 12) ^ (hash >> 18) ^ (hash >> 24) ^ (hash >> 30);
			hash *= 0xC00FFC01;  // inverse of hash += hash << 10;
			hash -= joaat_to_lower(key[--i]);
		}
		return hash == 0 ? key : std::to_string(hash);  // this should return 0 if the original hash was correct
	}

	inline const char* joaat_decrypt(const char* key)
	{
		Hash hash = joaat(key);
		hash *= 0x3FFF8001;  // inverse of hash += hash << 15;
		hash ^= (hash >> 11) ^ (hash >> 22);
		hash *= 0x38E38E39;  // inverse of hash += hash << 3;
		size_t i = strlen(key);
		while (i > 0)
		{
			hash ^= (hash >> 6) ^ (hash >> 12) ^ (hash >> 18) ^ (hash >> 24) ^ (hash >> 30);
			hash *= 0xC00FFC01;  // inverse of hash += hash << 10;
			hash -= joaat_to_lower(key[--i]);
		}
		return hash == 0 ? key : std::to_string(hash).c_str();  // this should return 0 if the original hash was correct
	}
}

#define RAGE_JOAAT_IMPL(str) (::rage::constexpr_joaat<sizeof(str) - 1>((str), std::make_index_sequence<sizeof(str) - 1>())())
#define RAGE_JOAAT(str) (std::integral_constant<rage::joaat_t, RAGE_JOAAT_IMPL(str)>::value)