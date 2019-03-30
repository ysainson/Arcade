/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** NcursesRenderer
*/

#pragma once

#include <curses.h>
#include <ncurses.h>
#include <stdexcept>
#include "../../../core/include/IRenderer.hpp"
#include "ASprite.hpp"

class NcursesRenderer : public IRenderer {
	public:
		NcursesRenderer();
		~NcursesRenderer();

	    void drawRectangle(const Rect &rect, const Color &color, bool fill = true);
	    void drawText(const std::string &text, uint8_t fontSize, const Vector &pos, const Color &color);
        void drawSprite(const ASprite *sprite);

	    void display();
	    void clear();

        WINDOW *_window = nullptr;

	protected:
        short nbWin = 0;
	private:
};
