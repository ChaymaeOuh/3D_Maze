#include "../headers/header.h"

/**
 * shade_walls - Sets the color of walls based on orientation
 * @color_ref: Pointer to color data structure
 * @orientation: Side in which the ray is hitting. (1) up/down
 * (2) left/right
 * Return: nothing
 */
void shade_walls(SDL_Color *color_ref, int orientation)
{
	SDL_Color up_down = {112, 112, 112, 255};
	SDL_Color left_right = {96, 96, 96, 150};

	if (orientation == ORIENT_UP_DOWN)
		*color_ref = up_down;
	else
		*color_ref = left_right;
}

/**
 * textured_roof - Draws roof from a bmp file
 * @sdl: data structure of sdl_instance
 * @map: data structure of map_t containing 2D map information
 * Return: nothing
 */
void textured_roof(sdl_instance *sdl, map_t *map)
{
	SDL_Rect sky_dome = {0, 0, SCREEN_WIDTH, (SCREEN_HEIGHT >> 1)};
	SDL_Surface *surface;

	if (!sdl->roof)
	{
		surface = SDL_LoadBMP("images/roof.bmp");
		if (!surface)
		{
			printf("Error: %s", SDL_GetError());
			free_map(map);
			window_close(sdl);
			exit(EXIT_FAILURE);
		}
		sdl->roof = SDL_CreateTextureFromSurface(sdl->renderer, surface);
		SDL_FreeSurface(surface);
	}
	SDL_RenderCopy(sdl->renderer, sdl->roof, NULL, &sky_dome);
}

/**
 * texture_walls - draws walls
 * @sdl: sdl_instance
 * @line_height: Height of the wall to draw
 * @column: current column on screen to draw texture
 * @y_pos: The y coordinate to start at @column
 * @alpha: controls darkening of some pixels for orientation
 * Return: nothing
 */
void texture_walls(sdl_instance *sdl, double line_height, int column,
		int y_pos, uint8_t alpha)
{
	SDL_Rect dest = {0, 0, 1, 64};
	SDL_Rect src_rect = {(column % 64), 0, 1, 64};
	int result;
	SDL_Surface *dest_surface = SDL_CreateRGBSurfaceWithFormat(0, 1,
			64, 32, SDL_GetWindowPixelFormat(sdl->window));
	SDL_Rect rend_rect = {column, y_pos, 1, (line_height)};

	if (!sdl->wall_surface)
	{
		sdl->wall_surface = SDL_LoadBMP("images/wall.bmp");
		if (!sdl->wall_surface)
		{
			printf("Error: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}
	SDL_UnlockSurface(dest_surface);
	result = SDL_BlitSurface(sdl->wall_surface, &src_rect, dest_surface, &dest);
	SDL_LockSurface(dest_surface);
	if (result < 0)
	{
		printf("Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if (!sdl->wall_texture)
	{
		sdl->wall_texture = SDL_CreateTextureFromSurface(sdl->renderer,
				dest_surface);
		if (!sdl->wall_texture)
		{
			printf("Error: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}
	SDL_UpdateTexture(sdl->wall_texture, NULL, dest_surface->pixels,
			dest_surface->pitch);
	SDL_SetTextureColorMod(sdl->wall_texture, alpha, alpha, alpha);
	SDL_RenderCopy(sdl->renderer, sdl->wall_texture, NULL, &rend_rect);
	SDL_FreeSurface(dest_surface);
}

/**
 * render_thread - A thread to handle rendering
 * @td: void pointer to thread_data 
 * Return: integer for the thread status
 */
int render_thread(void *td)
{
	thread_data *data = td;
	Uint64 start, end;
	double elapsedMs;

	while (!(*data->quit))
	{
		start = SDL_GetPerformanceCounter();

		/* Perform rendering */
		textured_roof(data->sdl, data->map);
		untextured_floor(data->sdl);
		raycast(data->sdl, data->player, data->map, data->map_active);
		weapon_gun(data->sdl, data->map);
		if (*data->map_active)
		{
			draw_2d_map(data->sdl, data->map);
			draw_player(data->sdl, data->player);
		}
		send_frame(data->sdl);

		/* Cap to 60fps */
		end = SDL_GetPerformanceCounter();
		elapsedMs = (end - start) / SDL_GetPerformanceCounter() * 1000;
		SDL_Delay(floor(16.666 - elapsedMs));
	}
	return (0);
}

/**
 * weapon_gun - Draws gun image
 * @sdl: sdl_instance
 * @map: map_t for 2D map information
 *
 * Return: nothing
 */
void weapon_gun(sdl_instance *sdl, map_t *map)
{
	SDL_Rect weapon = {700, 450, 700, 450};
	SDL_Surface *surface;

	if (!sdl->weapon)
	{
		surface = SDL_LoadBMP("images/gun.bmp");
		if (!surface)
		{
			printf("Error: %s", SDL_GetError());
			free_map(map);
			window_close(sdl);
			exit(EXIT_FAILURE);
		}
		sdl->weapon = SDL_CreateTextureFromSurface(sdl->renderer, surface);
		SDL_FreeSurface(surface);
	}
	SDL_RenderCopy(sdl->renderer, sdl->weapon, NULL, &weapon);
}