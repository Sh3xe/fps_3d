#pragma once

#include "graphics/renderer2d.hpp"
#include <glm/glm.hpp>

#include <string>
#include <functional>

namespace ui
{
	struct Widget
	{
	};

	struct Button: public Widget
	{
		Button(const std::string &content, const std::function<void()> &callback):
			content(content), callback(callback)
		{}

		std::string content;
		std::function<void()> callback;
	};

	struct Text : public Widget
	{
		enum class Type
		{
			NORMAL,
			TITLE
		};

		Text(const std::string &content, Type type = Type::NORMAL):
			content(content), type(type)
		{}

		std::string content;
		Type type;
	};

	struct Input : public Widget
	{
		Input(const std::string& placeholder = "") :
			placeholder(placeholder)
		{}

		std::string content{ "" };
		std::string placeholder;
	};

	struct Separator : public Widget
	{
	};

	struct Slider : public Widget
	{
		Slider(float min = 0.0f, float max = 1.0f, float default_value = 0.0f) :
			min_value(min), max_value(max), current_value(default_value)
		{}

		float min_value, max_value, current_value;
	};
}