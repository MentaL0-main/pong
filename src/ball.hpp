#pragma once

#include <SDL3/SDL.h>

namespace Pong {

class Ball {
public:
    Ball(float x, float y, float r);

    void render(SDL_Renderer* renderer);
    void proccess(int w, int h, SDL_FRect left_paddle, SDL_FRect right_paddle, float dt);

    void set(float x, float y, bool side) {
        m_x = x;
        m_y = y;

        if (side) m_current_dir_x = m_speed; else m_current_dir_x = m_speed;
        if (!side) m_current_dir_x = m_speed; else m_current_dir_x = -m_speed;
    }

    [[nodiscard]] inline float get_y() const {
    	return m_y;
    }
    
    [[nodiscard]] inline float get_x() const {
        return m_x;
    }

    inline void up_speed() {
        m_speed += 0.1f;
    };

private:
    float m_x, m_y;
    float m_radius;
    float m_speed = 300.0f;
    float m_current_dir_x = -m_speed;
    float m_current_dir_y = m_speed;
};

}
