#pragma once
#include <display/ui/components/button.hpp>
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
        : header(header_button);

    void add_item(const TextButtonUI& item);

    void render(SDL_Rect* viewport);

    void handle_event(SDL_Event* e);

    const std::string& selected_text() const;
};
