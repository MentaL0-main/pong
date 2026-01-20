#pragma once

#include <SDL3/SDL.h>

namespace Pong {

class Paddle {
public:
    Paddle(int x, int y, int width, int height);

    void render(SDL_Renderer* renderer);
    void proccess(int w, int h, SDL_Scancode up, SDL_Scancode down, float dt);

    [[nodiscard]] inline SDL_FRect get_rect() const {
        return m_rect;
    }

    inline void set_y(int y) {
        m_rect.y = y;
    }

private:
    float m_speed = 300.0f;
    SDL_FRect m_rect;
};

}
