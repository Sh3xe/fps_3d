#pragma once

#include "core/logger.hpp"

#include <cassert>
#include <cstdint>
#include <optional>
#include <memory>

struct Color
{
	uint8_t r, g, b, a;
};

template <typename T>
using Opt = std::optional<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using Unq = std::unique_ptr<T>;
