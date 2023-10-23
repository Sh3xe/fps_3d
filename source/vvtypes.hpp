#pragma once

#include <cassert>
#include <cstdint>
#include <optional>
#include <memory>

template <typename T>
using Opt = std::optional<T>;

template <typename T>
using Ref = std::shared_ptr<T>;
