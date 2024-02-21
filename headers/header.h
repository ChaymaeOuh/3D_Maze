#ifndef HEADER_H
#define HEADER_H

#include <C:\SDL2\include\SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Constants */

#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900
#define MAP_MARGIN 20
#define PLAYER_WIDTH 10
#define ORIENT_UP_DOWN 1
#define ORIENT_LEFT_RIGHT 2
#define GRID_SIZE 16
#define WINDOW_TITLE "The Mystic Maze: Discover the Secrets Within"
#define FOV 60
#define RADIAN(x) (x * (M_PI / 180.0))
#define ROTATION_MAGNITUDE 1
#define MOVE_SPEED 2
#define MAX_DRAW_DISTANCE 1024
#define REND_COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255)
#define REND_COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255)
#define REND_COLOR_YELLOW(x) SDL_SetRenderDrawColor(x, 255, 255, 0, 255)
#define REND_COLOR_GREEN(x) SDL_SetRenderDrawColor(x, 0, 255, 0, 255)
#define REND_COLOR_BLUE(x) SDL_SetRenderDrawColor(x, 0, 0, 255, 255)
#define REND_COLOR(x, r, g, b, a) SDL_SetRenderDrawColor(x, r, g, b, a)


/* structures */

/**
 * struct sdl_instance - SDL global variables
 *
 * @window: SDL window
 * @renderer: SDL renderer
 * @roof: pointer to roof texture
 * @wall_surface: pointer to sdl wall surface
 * @wall_texture: pointer to sdl wall texture
 * @weapon: pointer to sdl weapon texture
 */
typedef struct sdl_instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *roof;
	SDL_Surface *wall_surface;
	SDL_Texture *wall_texture;
	SDL_Texture *weapon;
} sdl_instance;

/**
 * struct player - the player information
 * @locale: Contains information of player displayed as a SDL rectangle
 * @view_angle: Players current angle viewing from
 */
typedef struct player
{
	SDL_Rect locale;
	float view_angle;
} player;

/**
 * struct map - map information
 * @arr: multidimension array of integer characters
 * @rows: number of rows in the array
 * @columns: number of columns in the array
 */
typedef struct map
{
	char **arr;
	int rows;
	int columns;
} map_t;

/**
 * struct line - represents a line
 * @p1: start of line. Contains it's x and y coordinates
 * @p2: end of line. Contains it's x and y coordinates
 */
typedef struct line
{
	SDL_Point p1;
	SDL_Point p2;
} line;

/**
 * struct thread_data - used data during multi-threading
 * @sdl: structure of sdl_instance
 * @map: structure of map_t
 * @player: structure of player
 * @map_active: pointer to boolean for checking map status
 * @quit: pointer to integer for program state
 */
typedef struct thread_data
{
	sdl_instance *sdl;
	map_t *map;
	struct player *player;
	SDL_bool *map_active;
	int *quit;
} thread_data;


/* texture */

void textured_roof(sdl_instance *sdl, map_t *map);
void shade_walls(SDL_Color *color_ref, int orientation);
void texture_walls(sdl_instance *sdl, double line_height,
		int column, int y_pos, uint8_t alpha);
void weapon_gun(sdl_instance *sdl, map_t *map);
int render_thread(void *td);


/* raycast */

void raycast(sdl_instance *sdl, player *player,  map_t *map,
		SDL_bool *map_active);
SDL_Point check_ray_intersections(SDL_Point *center, double ray_rotation_angle,
		map_t map, double *ray_len, int *orientation);
void draw_3D_walls(sdl_instance *sdl, double ray_length, int index,
		SDL_Color wall_color);
double remove_fish_eye_effect(player *player, double ray_length,
		double ray_view_angle);

void untextured_roof(sdl_instance *sdl);
void untextured_floor(sdl_instance *sdl);
int check_intersect_orientation(SDL_Rect wall, SDL_Point *pointA,
		SDL_Point *pointB);
int lines_intersect(line *line1, line *line2, SDL_Point *hitp);


/* player */

void draw_player(sdl_instance *sdl, player *player);
void rotate_player(player *player, SDL_Point *mouse);
SDL_Point move_player(player *player);
void player_collision_detection(player *player, map_t *map);
int quadrant_of_angle(int angle, int *resulting_angle);
void slide_on_wall(player *player);


/* parser */

FILE *open_file(char *filename);
map_t read_file(FILE *fp);
int count_rows(FILE *fp);
void close_file(FILE *fp);
map_t handle_file(char *filename);
char *get_row(char *line);
void validate_line_data(int max_line_count, char *line, FILE *fp,
		int line_number);
int in_array(char needle, char *haystack, unsigned int haystack_size);
char *concat(const char *s1, const char *s2);
void free_map(map_t *map);


/* window */

void window_init(char *name, sdl_instance *sdl);
void window_close(sdl_instance *sdl);
void create_renderer(sdl_instance *sdl);
void print_sdl_error(void);

void game_event_loop(sdl_instance *sdl, map_t *map);
void poll_events(int *quit, SDL_Event *e, player *player, SDL_Point *mouse,
		SDL_bool *map_active);

void draw_2d_map(sdl_instance *sdl, map_t *map);
void send_frame(sdl_instance *sdl);


SDL_Point rotate_point(const SDL_Point *point, float cx, float cy, float deg,
		float ray_size);

#endif /* HEADER_H */