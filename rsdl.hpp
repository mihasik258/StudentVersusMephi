#ifndef __RSDL_H__
#define __RSDL_H__

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class RGB {
public:
	RGB(int r, int g, int b) {
		if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
			throw "Invalid RGB color!";
		red = r;
		green = g;
		blue = b;
	}
	int red;
	int green;
	int blue;
};

const RGB WHITE(255, 255, 255);
const RGB YELLOW(255, 255, 0);
const RGB MAGENTA(255, 0, 255);
const RGB RED(255, 0, 0);
const RGB CYAN(0, 255, 255);
const RGB GREEN(0, 255, 0);
const RGB BLUE(0, 0, 255);
const RGB BLACK(0, 0, 0);

class window {
public:
	window(int width=800, int height=400, std::string title="kaf12meowmeow");
	~window();
    void draw_texture(const std::string &filename, int x, int y, int width, int height, int angle);
	void draw_bmp(const std::string &filename, int x, int y, int width, int height);
	void draw_png(const std::string &filename, int x, int y, int width, int height);
	void draw_png(const std::string &filename, int x, int y, int width, int height, int angle);
	void draw_bg(const std::string &filename, int x=0, int y=0);
	void update_screen();
	void clear_screen() { fill_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, {0, 0, 0}); }
    void fill_rect(int x, int y, int width, int height, RGB color=WHITE);
    void draw_line(int x1, int y1, int x2, int y2, RGB color=WHITE);
    void draw_point(int x, int y, RGB color=WHITE);
    void draw_rect(int x, int y, int width, int height, RGB color=WHITE);
    void play_music(const std::string &filename, int loops);
    void stop_music();
    void pause_music();
    void resume_music();
    static constexpr int TAP_TO_START_X1 = 230;
    static constexpr int TAP_TO_START_X2 = 796;
    static constexpr int TAP_TO_START_Y1 = 520;
    static constexpr int TAP_TO_START_Y2 = 585;
    static const int WIDTH = 1050;
    static const int HEIGHT = 600;
private:
    SDL_Texture *load_texture(const std::string &filename);
	void set_color(RGB color);
	void dump_err() { std::cerr << SDL_GetError() << '\n'; }
	void init();
	void create_window(const std::string &title);     // Создание окна и рендера
	void cleanup_resources(); 
	SDL_Window* win;
	SDL_Renderer* renderer;
	std::map<std::string, SDL_Texture*> texture_cache;
	std::map<std::string, TTF_Font*> fonts_cache;
	Mix_Music* music;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
};



#endif
