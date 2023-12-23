#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "Tools/Logger.h"
#include "Engine/glm/glm.hpp"
using namespace glm;

template<typename T, typename ... Args>
constexpr std::shared_ptr<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}