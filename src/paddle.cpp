#include "paddle.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

namespace Pong {

Paddle::Paddle(int x, int y, int width, int height) {
    m_rect = {(float)x, (float)y, (float)width, (float)height};
}

void Paddle::render(SDL_Renderer* renderer) {
    SDL_RenderFillRect(renderer, &m_rect);
}

void Paddle::proccess(int w, int h, SDL_Scancode up, SDL_Scancode down) {
    const bool* state = SDL_GetKeyboardState(NULL);

    if (state[up] && m_rect.y > 0) {
        m_rect.y -= m_speed;
    }

    if (state[down] && m_rect.y + m_rect.h < h) {
        m_rect.y += m_speed;
    }
}

}
