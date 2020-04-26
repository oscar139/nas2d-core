// ==================================================================================
// = NAS2D
// = Copyright © 2008 - 2019 New Age Software
// ==================================================================================
// = NAS2D is distributed under the terms of the zlib license. You are free to copy,
// = modify and distribute the software under the terms of the zlib license.
// =
// = Acknowledgment of your use of NAS2D is appreciated but is not required.
// ==================================================================================
#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace NAS2D
{
	template<typename T>
	std::string stringFrom(T value)
	{
		if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>) {
			return value;
		} else if constexpr (std::is_same_v<T, bool>) {
			return value ? "true" : "false";
		} else {
			return std::to_string(value);
		}
	}

	template<typename T>
	T stringTo(const std::string& value) {
		if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>) {
			return value;
		} else if constexpr (std::is_same_v<T, bool>) {
			return
				value == "true" ? true :
				value == "false" ? false :
				throw std::invalid_argument("Value must be 'true' or 'false': " + std::string{value});
		} else if constexpr (std::is_same_v<T, long double>) {
			return std::stold(value);
		} else if constexpr (std::is_same_v<T, double>) {
			return std::stod(value);
		} else if constexpr (std::is_same_v<T, float>) {
			return std::stof(value);
		} else if constexpr (std::is_same_v<T, long long>) {
			return std::stoll(value);
		} else if constexpr (std::is_same_v<T, long>) {
			return std::stol(value);
		} else if constexpr (std::is_same_v<T, int>) {
			return std::stoi(value);
		} else if constexpr (std::is_same_v<T, unsigned long long>) {
			return std::stoull(value);
		} else if constexpr (std::is_same_v<T, unsigned long>) {
			return std::stoul(value);
		} else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
			const auto integerValue = std::stoi(value);
			if constexpr (
				std::numeric_limits<int>::max() > std::numeric_limits<T>::max() ||
				std::numeric_limits<int>::min() < std::numeric_limits<T>::min()
			) {
				if (integerValue > std::numeric_limits<T>::max() || integerValue < std::numeric_limits<T>::min()) {
					throw std::out_of_range("Value out of range: " + value);
				}
			}
			return static_cast<T>(integerValue);
		} else if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>) {
			const auto integerValue = std::stoul(value);
			if constexpr (std::numeric_limits<unsigned long>::max() > std::numeric_limits<T>::max()) {
				if (integerValue > std::numeric_limits<T>::max()) {
					throw std::out_of_range("Value out of range: " + value);
				}
			}
			return static_cast<T>(integerValue);
		} else {
			static_assert(true, "Unsupported type");
		}
	}

	std::string toLowercase(std::string str);
	std::string toUppercase(std::string str);
	std::vector<std::string> split(const std::string& str, char delim = ',');
	std::pair<std::string, std::string> splitOnFirst(const std::string& str, char delim);
	std::pair<std::string, std::string> splitOnLast(const std::string& str, char delim);
	std::string join(const std::vector<std::string>& strs);
	std::string join(const std::vector<std::string>& strs, char delim);
	std::string trimWhitespace(std::string_view string);
	bool startsWith(std::string_view string, std::string_view start) noexcept;
	bool endsWith(std::string_view string, std::string_view end) noexcept;
	bool startsWith(std::string_view string, char start) noexcept;
	bool endsWith(std::string_view string, char end) noexcept;

	/**
 * \typedef StringList
 * \brief	A list of std::string's.
 *
 * The StringList is provided primarily as a convenience typedef
 * but is also used by some of NAS2D's functions.
 */
	using StringList = std::vector<std::string>;

} // namespace NAS2D

