#pragma once

#include "core/logger.hpp"

#include <cassert>
#include <cstdint>
#include <optional>
#include <memory>

/*
using u64 = uint64_t;
using i64 = int64_t;

using u32 = uint32_t;
using i32 = int32_t;

using u16 = uint16_t;
using i16 = int16_t;

using u8 = uint8_t;
using i8 = int8_t;
*/

template <typename T>
using Opt = std::optional<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using Unq = std::unique_ptr<T>;
