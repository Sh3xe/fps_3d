#pragma once

#include <string>
#include <functional>

struct UIButton
{
	std::string content;
	std::function<void()> callback;
};

struct UIText
{
	enum class Type 
	{
		NORMAL,
		TITLE
	};
	
	std::string content;
	Type type;
};

struct UIInput
{
	std::string content;
	bool is_selected;
};