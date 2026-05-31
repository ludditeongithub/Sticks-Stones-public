#pragma once
#include "button.hpp"
#include <vector>
#include <string>

class DropdownMenu
{
public:
    TextButtonUI header;

    std::vector<TextButtonUI> items;

    bool expanded = false;

    int selectedIndex = -1;

    DropdownMenu(
        const TextButtonUI& headerButton, uint16_t size)
        : header(headerButton)
    {
	    items.reserve(size);
    }

    void addItem(const TextButtonUI& item)
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

    void handleEvent(SDL_Event* e)
    {
        header.handleEvent(e);

        if (e->type == SDL_MOUSEBUTTONUP)
        {
            int mx, my;
            SDL_GetMouseState(&mx, &my);

            bool headerClicked =
                mouseInside(
                    {mx, my},
                    header.topLeftCorner,
                    header.dimensions);

            if (headerClicked)
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

            item.handleEvent(e);

            if (e->type == SDL_MOUSEBUTTONUP)
            {
                int mx, my;
                SDL_GetMouseState(&mx, &my);

                bool clicked =
                    mouseInside(
                        {mx, my},
                        item.topLeftCorner,
                        item.dimensions);

                if (clicked)
                {
                    selectedIndex = static_cast<int>(i);

                    header.text = item.text;

                    expanded = false;
                }
            }
        }
    }

    const std::string& selectedText() const
    {
        return header.text;
    }
};
