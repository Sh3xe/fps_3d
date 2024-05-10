#pragma once

#include "defines.hpp"
#include "primitives.hpp"
#include "../graphics/window.hpp"
#include "../graphics/renderer2d.hpp"

#include <string>
#include <map>
#include <vector>

namespace ui
{
	class Menu
	{
	public:
		class Tab
		{
		public:
			friend class Menu;

			~Tab();

			void add_widget(Widget* widget);

		private:
			struct Element
			{
				Element(Widget* widget);

				Widget* widget;
				Renderer2D::StyledRectangle rect;
				bool hover{ false };
				bool selected{ false };
				float time_since_click{ 0.0f };
			};

			void update_elements();

			std::vector<Element> m_elements;
			bool m_require_update{ true };
		};

		Menu(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		~Menu();

		void update(float s_dt, const Window& window);

		void render(const Renderer2D& renderer);

		void add_tab(const std::string& title);
		
		Tab& operator[](const std::string& title);

	private:
		std::map<std::string,Tab> m_tabs;
		uint32_t x, y, width, height;
	};
}