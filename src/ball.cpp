#include "ball.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

namespace Pong {

Ball::Ball(float x, float y, float r)
    : m_x(x), m_y(y), m_radius(r) {}

void Ball::render(SDL_Renderer* renderer) {
    for (int w = 0; w < m_radius * 2; ++w) {
        for (int h = 0; h < m_radius * 2; ++h) {
            int dx = m_radius - w;
            int dy = m_radius - h;
            if ((dx * dx + dy * dy) <= (m_radius * m_radius)) {
                SDL_RenderPoint(renderer, m_x + dx, m_y + dy);
            }
        }
    }
}

void Ball::proccess(int w, int h, SDL_FRect left_paddle, SDL_FRect right_paddle, float dt) {
    if (m_x - m_radius <= (left_paddle.x + left_paddle.w) && m_y < left_paddle.y + left_paddle.h && m_y > left_paddle.y) {
        m_current_dir_x = m_speed;
    }

    if (m_x + m_radius >= right_paddle.x && m_y < right_paddle.y + right_paddle.h && m_y > right_paddle.y) {
        m_current_dir_x = -m_speed;
    }

    if (m_y + m_radius >= h) {
        m_current_dir_y = m_speed;
    }

    if (m_y - m_radius <= 0) {
        m_current_dir_y = -m_speed;
    
    }

    m_x += m_current_dir_x * dt;
    m_y -= m_current_dir_y * dt;
}

}
