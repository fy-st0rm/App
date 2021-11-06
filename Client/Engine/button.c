#include "button.h"
#include "leak_detector_c.h"
#include "text.h"

Button* button_new(SDL_Renderer* renderer, SDL_Rect rect, TTF_Font* font, char* text, SDL_Color fg, SDL_Color bg, SDL_Color border)
{
	Button* button = malloc(sizeof(Button));

	button->rect = rect;

	button->text = calloc(sizeof(text), sizeof(char));
	strcpy(button->text, text);
	button->text_texture = create_texture(renderer, font, text);
	
	// Checking if the text is wider than the button
	SDL_Rect text_rect;
	SDL_QueryTexture(button->text_texture, NULL, NULL, &text_rect.w, NULL);

	// If yes
	if (text_rect.w > rect.w)
	{
		SDL_Texture* char_texture = create_texture(renderer, font, "A");
		int char_w;
		SDL_QueryTexture(char_texture, NULL, NULL, &char_w, NULL);

		// Calculating no of characters that can be fitted in the button
		int no_of_char = rect.w / char_w;
		char new_text[no_of_char];
		memcpy(new_text, text, no_of_char);

		SDL_DestroyTexture(char_texture);
		SDL_DestroyTexture(button->text_texture);
		
		// Regenrating the new texture
		button->text_texture = create_texture(renderer, font, new_text);
	}

	button->fg = fg;
	button->bg = bg;
	button->border = border;
	button->active = false;

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

bool button_active(Button* button,int offset_x, int offset_y)
{	
	// Calculating active status of the button
	SDL_Point pos;
	SDL_GetMouseState(&pos.x, &pos.y);

	SDL_Rect rect = { button->rect.x + offset_x, button->rect.y + offset_y, button->rect.w, button->rect.h };

	if (SDL_PointInRect(&pos, &rect))
		button->active = true;
	else
		button->active = false;
	return button->active;
}

bool button_is_clicked(Button* button, SDL_Event event, int offset_x, int offset_y)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (button_active(button, offset_x, offset_y))
			return true;
	}
	return false;
}

void button_change_fg(Button* button, SDL_Color fg)
{
	if ((button->fg.r != fg.r) && (button->fg.g != fg.g) && (button->fg.b != fg.b))
		button->fg = fg;
}

void button_change_text(Button* button, SDL_Renderer* renderer, TTF_Font* font, char* text)
{
	SDL_DestroyTexture(button->text_texture);
	button->text_texture = create_texture(renderer, font, text);
}

void button_change_rect(Button* button, SDL_Renderer* renderer, TTF_Font* font, SDL_Rect rect)
{
	if ((button->rect.x != rect.x) || (button->rect.y != rect.y) || (button->rect.w != rect.w) || (button->rect.h != rect.h))
	{
		button->rect = rect;	
		
		// Checking if the text is wider than the button
		SDL_Rect text_rect;
		SDL_QueryTexture(button->text_texture, NULL, NULL, &text_rect.w, NULL);

		// If yes
		if (text_rect.w > rect.w)
		{
			SDL_Texture* char_texture = create_texture(renderer, font, "A");
			int char_w;
			SDL_QueryTexture(char_texture, NULL, NULL, &char_w, NULL);

			// Calculating no of characters that can be fitted in the button
			int no_of_char = rect.w / char_w;
			char new_text[no_of_char];
			memcpy(new_text, button->text, no_of_char);

			SDL_DestroyTexture(char_texture);
			SDL_DestroyTexture(button->text_texture);
			// Regenrating the new texture
			button->text_texture = create_texture(renderer, font, new_text);
		}
	}
}
