#include "pong.hpp"
#include "delta.hpp"

#include <memory>
#include <iostream>
#include <stdexcept>

namespace Pong {

void Pong::init() {
    std::cout << "[*] Please, choose game:\n"
                 "[*] B - Play with bot, P - Two players mode\n"
                 "[>>] ";
    std::cin >> m_type;
    m_delta.update();

    init_window();
    init_renderer();

    #ifdef _WIN32
        m_font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 32);
    #elif defined(__linux__)
        m_font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 32);
    #elif defined(__APPLE__)
        m_font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 32);
    #else
        #error("OS not supported");
    #endif

    if (!m_font) {
    m_font = TTF_OpenFont("monojet.ttf", 32);
    if (!m_font) {
        throw std::runtime_error("[!] Failed to load ANY font");
    }
}

    m_ball = std::make_unique<Ball>(WINDOW_HALF_WIDTH, WINDOW_HALF_HEIGHT, 9);
    m_paddle_left = std::make_unique<Paddle>(0, WINDOW_HALF_HEIGHT-30, 10, 60);
    m_paddle_right = std::make_unique<Paddle>(WINDOW_WIDTH-10, WINDOW_HALF_HEIGHT-30, 10, 60);
}

void Pong::init_window() {
    if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) {
        throw std::runtime_error("[!] Failed to init sdl3");
    }

    m_window = SDL_CreateWindow("Pong", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!m_window) {
        throw std::runtime_error("[!] Failed to init window");
    }
}

void Pong::init_renderer() {
    m_renderer = SDL_CreateRenderer(m_window, 0);
    if (!m_renderer) {
        throw std::runtime_error("[!] Failed to init renderer");
    }
}

void Pong::mainloop() {
    while (m_running) {
        while (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_EVENT_QUIT) {
                m_running = false;
            }
        }

        m_delta.update();
        float dt = m_delta.get_delta();

        m_ball->proccess(WINDOW_WIDTH, WINDOW_HEIGHT, m_paddle_left->get_rect(), m_paddle_right->get_rect(), dt);
        m_paddle_left->proccess(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_SCANCODE_W, SDL_SCANCODE_S, dt);
        
        if (m_type == 'P') m_paddle_right->proccess(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_SCANCODE_O, SDL_SCANCODE_L, dt);
        else { 
            m_paddle_right->set_y(m_ball->get_y()-30);
            if (m_paddle_right->get_rect().y < 0) m_paddle_right->set_y(0);
            else if (m_paddle_right->get_rect().y > WINDOW_HEIGHT-60) m_paddle_right->set_y(WINDOW_HEIGHT-60);
        }

        if (m_ball->get_x() <= 0) {
            m_ball->set(WINDOW_HALF_WIDTH, WINDOW_HALF_HEIGHT, 1); 
            ++m_score.second;
        }
        else if (m_ball->get_x() >= WINDOW_WIDTH) {
            m_ball->set(WINDOW_HALF_WIDTH, WINDOW_HALF_HEIGHT, 0); 
            ++m_score.first;
        }

        SDL_SetRenderDrawColor(
                m_renderer,
                m_background_color.r,
                m_background_color.g,
                m_background_color.b,
                m_background_color.a);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, m_foreground_color.r, m_foreground_color.g, m_foreground_color.b, m_foreground_color.a);

        SDL_FRect line = {WINDOW_HALF_WIDTH-2, 0, 4, WINDOW_HEIGHT};
        SDL_RenderFillRect(m_renderer, &line);

        render_score();

        m_ball->render(m_renderer);
        m_paddle_left->render(m_renderer);
        m_paddle_right->render(m_renderer);

        SDL_RenderPresent(m_renderer);


        SDL_Delay(1);
    }
}

void Pong::render_score() {
    render_text(100, WINDOW_HALF_WIDTH / 2 - 50, WINDOW_HALF_HEIGHT / 2, std::to_string(m_score.first).c_str(), m_foreground_color);
    render_text(100, WINDOW_HALF_WIDTH / 2 * 3, WINDOW_HALF_HEIGHT / 2, std::to_string(m_score.second).c_str(), m_foreground_color);
}

void Pong::render_text(float font_size, int x, int y, const char* text, SDL_Color color) {
    TTF_SetFontSize(m_font, font_size);
    
    size_t text_length = strlen(text);
    
    SDL_Surface* surface = TTF_RenderText_Blended(m_font, text, text_length, color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_DestroySurface(surface);
    if (!texture) return;

    SDL_PropertiesID props = SDL_GetTextureProperties(texture);
    float w = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0.0f);
    float h = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0.0f);

    SDL_FRect dst = { (float)x, (float)y, w, h };
    SDL_RenderTexture(m_renderer, texture, nullptr, &dst);

    SDL_DestroyTexture(texture);
}

void Pong::cleanup() {
    if (m_font) TTF_CloseFont(m_font);
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Pong::run() {
    init();
    mainloop();
    cleanup();
}

}
