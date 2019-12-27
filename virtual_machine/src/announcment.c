#include "sdl.h"
#include "op.h"

void	form_squares(t_sdl *sdl)
{

void	update_arena(t_sdl *sdl)
{
	int			index;
	int			end_of_row;
	int			row;
	t_render	*render_info;
	SDL_Surface	*surface;

	index = 0;
	set_nibble_for_render(index, EMPTY, 0, sdl);
	render_info = sdl->render_info;
	surface = sdl->surface;
	row = i / 64;
	end_of_row = (row + 1) * 64;
	while (index < MEM_SIZE)
	{
		while (index < end_of_row)
		{
			render_info->font_color = sdl->colors[sdl->replica[index] + FONT_COLOR];
			draw_byte(sdl->arena[index++], render_info, surface);
			render_info->rect.x += NIBBLE_WIDTH;
		}
		render_info->rect.y += NIBBLE_HEIGHT;
		render_info->rect.x = NIBBLE_X_SHIFT;
		end_of_row = (++row + 1) * 64;
		index = end_of_row - 64;
	}
}
