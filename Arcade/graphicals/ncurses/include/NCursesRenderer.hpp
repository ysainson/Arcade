/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** NcursesRenderer
*/

#ifndef NCURSES_RENDERER_HPP_
#define NCURSES_RENDERER_HPP_

#include <curses.h>
#include <ncurses.h>
#include <stdexcept>

#include "IRenderer.hpp"
#include "ASprite.hpp"

class NCursesRenderer : public IRenderer {
public:
	NCursesRenderer();
	~NCursesRenderer();

	void drawRectangle(const Rect &rect, const Color &color, bool fill = true);
	void drawText(const std::string &text, uint8_t fontSize, const Vector &pos, const Color &color);
	void drawSprite(const ASprite *sprite);

	void display();
	void clear();

private:
	void _colorInitialization(const Color &color, bool fill = false);
	
	WINDOW *_window = nullptr;
	const uint8_t _w = 80;
	const uint8_t _h = 40;
	short _colorReference = 0;
};

#endif /* !NCURSES_RENDERER_HPP_ */