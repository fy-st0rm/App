#include "button.h"
#include "leak_detector_c.h"
#include "text.h"

Button* button_new(SDL_Renderer* renderer, SDL_Rect rect, TTF_Font* font, char* text, SDL_Color fg, SDL_Color bg, SDL_Color border)
{
	Button* button = malloc(sizeof(Button));

	button->rect = rect;
	button->text_texture = create_texture(renderer, font, text);

	button->fg = fg;
	button->bg = bg;
	button->border = border;

	return button;
}

void button_destroy(Button* button)
{
	free(button);
}

void button_render(Button* button, SDL_Renderer* renderer)
{
	// Drawing border
	SDL_Rect border_rect = { button->rect.x - 2, button->rect.y - 2, button->rect.w + 4, button->rect.h + 4};
	SDL_SetRenderDrawColor(renderer, button->border.r, button->border.g, button->border.b, button->border.a);
	SDL_RenderFillRect(renderer, &border_rect);

	// Drawing button
	SDL_SetRenderDrawColor(renderer, button->bg.r, button->bg.g, button->bg.b, button->bg.a);
	SDL_RenderFillRect(renderer, &button->rect);	
	
	// Render text
	SDL_Rect text_rect;
	SDL_QueryTexture(button->text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
	text_rect.x = (button->rect.x + (button->rect.x + button->rect.w)) / 2 - (text_rect.w / 2);
	text_rect.y = (button->rect.y + (button->rect.y + button->rect.h)) / 2 - (text_rect.h / 2);
	draw_text(renderer, text_rect.x, text_rect.y, button->text_texture, button->fg); 
}

bool button_is_clicked(Button* button, SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_Point pos;
		SDL_GetMouseState(&pos.x, &pos.y);
		if (SDL_PointInRect(&pos, &button->rect))
			return true;
	}
	return false;
}
