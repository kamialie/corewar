#include "visual.h"

/*
 * nibble is 4 bits!
*/
char	get_nibble(unsigned char nibble)
{
	if (nibble < 10)
		return (48 + nibble);
	else if (nibble == 10)
		return ('a');
	else if (nibble == 11)
		return ('b');
	else if (nibble == 12)
		return ('c');
	else if (nibble == 13)
		return ('d');
	else if (nibble == 14)
		return ('e');
	else
		return ('f');
}

/*
** render single byte:
** divide byte into nibbles, get the corresponding base 16 symbols, form a string
** render text using TTF, set coordinates, copy to window surface, free orginal surface created by TTF
*/
void	draw_byte(unsigned char byte, t_render *render_info, SDL_Surface *surface)
{
	char cell[3];
	SDL_Surface	*text_surface;

	cell[0] = get_nibble((byte & 0xf0) >> 4);
	cell[1] = get_nibble(byte & 0xf);
	cell[2] = '\0';
	text_surface = TTF_RenderText_Shaded(render_info->font, cell, render_info->font_color, render_info->back_color);
	SDL_BlitSurface(text_surface, NULL, surface, &render_info->rect);
	SDL_FreeSurface(text_surface);
}

void		set_render_color(int type, int player, t_render *render_info, SDL_Color *colors)
{
	if (type == EMPTY)
	{
		render_info->font_color = colors[WHITE];
		render_info->back_color = colors[BLACK];
	}
	else if (type == CURSOR)
	{
		render_info->font_color = colors[WHITE];
		render_info->back_color = colors[player + BACK_COLOR];
	}
	else
	{
		render_info->font_color = colors[player + FONT_COLOR];
		render_info->back_color = colors[BLACK];
	}
}

void		set_render_location(int location, t_render *render_info)
{
	render_info->rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (location % 64);
	render_info->rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (location / 64);
}

t_render	create_render_info(TTF_Font *font)
{
	t_render	render_info;
	
	render_info.font = font;
	render_info.rect.w = NIBBLE_WIDTH;
	render_info.rect.h = NIBBLE_HEIGHT;
	return (render_info);
}
