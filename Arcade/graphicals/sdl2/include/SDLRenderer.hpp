/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** SDLRenderer
*/

#ifndef NCURSES_RENDERER_HPP_
#define NCURSES_RENDERER_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

#include "IRenderer.hpp"
#include "SDLSprite.hpp"
#include "Color.hpp"

class SDLRenderer : public IRenderer {
public:
	SDLRenderer();
	~SDLRenderer();

	void drawRectangle(const Rect &rect, const Color &color, bool fill = true);
	void drawText(const std::string &text, uint8_t fontSize, const Vector &pos, const Color &color);
	void drawSprite(const ASprite *sprite);

	void display();
	void clear();

	SDL_Window *_window = nullptr;
    std::pair<int, int> _size;
    SDL_Renderer *_renderer;
    TTF_Font *_font;
};

#endif /* !NCURSES_RENDERER_HPP_ */