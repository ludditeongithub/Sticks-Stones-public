#pragma once
#include <ui/components/button.hpp>
#include <vector>
#include <string>

class DropdownMenu
{
public:
    TextButtonUI header;
  
    std::vector<TextButtonUI> items;

    bool expanded = false;

    int selected_index = -1;

    DropdownMenu(
        const TextButtonUI& header_button, uint16_t size)
        : header(header_button)
    {
	    items.reserve(size);
    }

    void add_item(const TextButtonUI& item)
    {
        items.push_back(item);
    }

    void render(SDL_Rect* viewport)
    {
        header.render(viewport);

        if (!expanded)
            return;

        for (auto& item : items)
        {
            item.render(viewport);
        }
    }

    void handle_event(SDL_Event* e)
    {
        header.handle_event(e);

        if (e->type == SDL_MOUSEBUTTONUP)
        {
            int mx, my;
            SDL_GetMouseState(&mx, &my);

            bool header_clicked =
                mouse_inside(
                    {mx, my},
                    header.top_left_corner,
                    header.dimensions);

            if (header_clicked)
            {
                expanded = !expanded;
                return;
            }
        }

        if (!expanded)
            return;

        for (size_t i = 0; i < items.size(); ++i)
        {
            TextButtonUI& item = items[i];

            item.handle_event(e);

            if (e->type == SDL_MOUSEBUTTONUP)
            {
                int mx, my;
                SDL_GetMouseState(&mx, &my);

                bool clicked =
                    mouse_inside(
                        {mx, my},
                        item.top_left_corner,
                        item.dimensions);

                if (clicked)
                {
                    selected_index = static_cast<int>(i);

                    header.text = item.text;

                    expanded = false;
                }
            }
        }
    }

    const std::string& selected_text() const
    {
        return header.text;
    }
};
