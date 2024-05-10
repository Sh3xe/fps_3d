#include "menu.hpp"

namespace ui
{
	Menu::Menu(uint32_t x, uint32_t y, uint32_t width, uint32_t height):
		x(x), y(y), width(width), height(height)
	{
	}

	Menu::~Menu()
	{
	}

	void Menu::update(float s_dt, const Window& window)
	{
	}

	void Menu::render(const Renderer2D& renderer)
	{
	}

	void Menu::add_tab(const std::string& title)
	{
		m_tabs.insert(std::make_pair(title, Tab()));
	}

	Menu::Tab& Menu::operator[](const std::string& title)
	{
		auto it = m_tabs.find(title);
		assert(it != m_tabs.end());
		return it->second;
	}

	Menu::Tab::~Tab()
	{
		for (auto& el : m_elements)
		{
			delete el.widget;
		}
	}

	void Menu::Tab::add_widget(Widget* widget)
	{
		Element element{ widget };

		m_elements.push_back(element);
		m_require_update = true;
	}

	void Menu::Tab::update_elements()
	{
		for (auto& el : m_elements)
		{

		}
	}

	Menu::Tab::Element::Element(Widget* widget):
		widget(widget)
	{
	}
}