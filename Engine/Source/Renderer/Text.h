#pragma once
#include "Renderer.h"
#include "Font.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include <string>


class Renderer;
struct Color;


class Text {
public:
	
	Text() = default;
	Text(res_t<Font> font) : m_font{font} {}
	~Text();

	void SetFont(res_t<Font> font) { m_font = font; }

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, int x, int y);
	
private:
	res_t<Font> m_font{ nullptr };
	SDL_Texture* m_texture{ nullptr };
};
