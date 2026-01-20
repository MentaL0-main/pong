#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>

#include "ball.hpp"
#include "paddle.hpp"

namespace Pong {

class Pong {
public:
    void run();

    static constexpr unsigned int WINDOW_WIDTH = 1200;
    static constexpr unsigned int WINDOW_HEIGHT = 900;
    static constexpr unsigned int WINDOW_HALF_WIDTH = WINDOW_WIDTH / 2;
    static constexpr unsigned int WINDOW_HALF_HEIGHT = WINDOW_HEIGHT / 2;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    SDL_Event m_event;

    SDL_Color m_background_color = {0, 0, 0, 255};
    SDL_Color m_foreground_color = {255, 255, 255, 255};

    bool m_running = true;
    
    char m_type;

    std::unique_ptr<Ball> m_ball;
    std::unique_ptr<Paddle> m_paddle_left;
    std::unique_ptr<Paddle> m_paddle_right;

    std::pair<int, int> m_score = {0, 0};

    TTF_Font* m_font = nullptr;

    void init();
    void mainloop();
    void cleanup();

    void init_window();
    void init_renderer();
    void init_font();

    void render_score();
    void render_text(float font_size, int x, int y, const char* text,
                     SDL_Color color);
};

}
