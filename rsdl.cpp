#include <iostream>
#include <sstream>
#include "rsdl.hpp"

void window::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
        throw std::runtime_error("SDL Initialization failed: " + std::string(SDL_GetError()));

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        throw std::runtime_error("IMG_Init failed: PNG support not enabled");

    if (TTF_Init() == -1)
        throw std::runtime_error("TTF_Init failed: " + std::string(TTF_GetError()));
}

window::window(int width, int height, std::string title):WINDOW_WIDTH(width),WINDOW_HEIGHT(height){
    init();
    SDL_CreateWindowAndRenderer(width,height,0,&win,&renderer);
	if (win == NULL || renderer == NULL)
		throw std::string("Window could not be created! SDL_Error: ") + SDL_GetError();
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetWindowTitle(win, title.c_str());    fill_rect(0,0,width,height,WHITE);
    update_screen();
}

window::~window() {
    cleanup_resources();
}
void window::create_window(const std::string &title) {
    win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!win)
        throw std::runtime_error("SDL_CreateWindow failed: " + std::string(SDL_GetError()));

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        throw std::runtime_error("SDL_CreateRenderer failed: " + std::string(SDL_GetError()));

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}
void window::cleanup_resources() {
    for (auto &entry : texture_cache)
        SDL_DestroyTexture(entry.second);
    texture_cache.clear();

    for (auto &entry : fonts_cache)
        TTF_CloseFont(entry.second);
    fonts_cache.clear();

    if (music) {
        Mix_FreeMusic(music);
        Mix_CloseAudio();
    }

    if (renderer) SDL_DestroyRenderer(renderer);
    if (win) SDL_DestroyWindow(win);

    if (TTF_WasInit()) TTF_Quit();
    if (IMG_Init(0)) IMG_Quit();
    SDL_Quit();
}


void window::set_color(RGB color){
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
}
void window::draw_bmp(const std::string &filename, int x, int y, int width, int height) {
    draw_texture(filename, x, y, width, height, 0);
}

void window::draw_png(const std::string &filename, int x, int y, int width, int height) {
    draw_texture(filename, x, y, width, height, 0);
}
void window::draw_png(const std::string &filename, int x, int y, int width, int height, int angle) {
    draw_texture(filename, x, y, width, height, angle);
}

void window::draw_bg(const std::string &filename, int x, int y){
	SDL_Texture* res = texture_cache[filename];
	if (res == NULL){
		res = IMG_LoadTexture(renderer, filename.c_str());
		texture_cache[filename]=res;
	}
    SDL_Rect src = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_Rect dst = {x, y, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, res, &dst, &src);
}



void window::update_screen(){
	SDL_RenderPresent(renderer);
}

void window::fill_rect(int x, int y, int width, int height, RGB color) {
    set_color(color);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

void window::draw_line(int x1, int y1, int x2, int y2, RGB color){
    set_color(color);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void window::draw_point(int x, int y, RGB color){
    set_color(color);
    SDL_RenderDrawPoint(renderer, x, y);
}

void window::draw_rect(int x, int y, int width, int height, RGB color) {
    draw_line(x, y, x + width, y, color);
    draw_line(x, y, x, y + height, color);
    draw_line(x + width, y, x + width, y + height, color);
    draw_line(x, y + height, x + width, y + height, color);
}
void window::play_music(const std::string &filename, int loops) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        throw std::runtime_error("SDL_mixer could not initialize: " + std::string(Mix_GetError()));

    music = Mix_LoadMUS(filename.c_str());
    if (!music)
        throw std::runtime_error("Failed to load music: " + std::string(Mix_GetError()));

    if (Mix_PlayMusic(music, loops) == -1)
        throw std::runtime_error("Failed to play music: " + std::string(Mix_GetError()));
}

void window::stop_music() {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = nullptr;
    Mix_CloseAudio();
}

void window::pause_music() {
    if (Mix_PlayingMusic()) Mix_PauseMusic();
}

void window::resume_music() {
    if (Mix_PausedMusic()) Mix_ResumeMusic();
}
void window::draw_texture(const std::string &filename, int x, int y, int width, int height, int angle = 0) {
    SDL_Texture *texture = load_texture(filename); // Унифицированная функция загрузки
    SDL_Rect dest = {x, y, width, height};
    if (angle == 0) {
        SDL_RenderCopy(renderer, texture, nullptr, &dest);
    } else {
        SDL_RenderCopyEx(renderer, texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
    }
}
SDL_Texture *window::load_texture(const std::string &filename) {
    auto it = texture_cache.find(filename);
    if (it != texture_cache.end()) return it->second;

    SDL_Texture *texture = nullptr;
    if (filename.ends_with(".bmp")) {
        SDL_Surface *surface = SDL_LoadBMP(filename.c_str());
        if (!surface) throw std::runtime_error("Failed to load BMP: " + filename);

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    } else if (filename.ends_with(".png")) {
        texture = IMG_LoadTexture(renderer, filename.c_str());
    }

    if (!texture) throw std::runtime_error("Failed to load texture: " + filename);

    texture_cache[filename] = texture;
    return texture;
}

