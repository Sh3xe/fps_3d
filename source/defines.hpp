#pragma once

#include "core/logger.hpp"

#include <cassert>
#include <cstdint>
#include <optional>
#include <memory>

struct Color
{
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
		r(r), g(g), b(b), a(a)
	{
	}
	Color() = default;

	uint8_t r = 0, g = 0, b = 0, a = 0;
};

template <typename T>
using Opt = std::optional<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using Unq = std::unique_ptr<T>;
