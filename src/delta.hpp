#pragma once

#include <chrono>

namespace Pong {

class Delta {
public:
    Delta() : m_delta(0.0f), m_smoothedFPS(0.0f), m_lastTime(std::chrono::steady_clock::now()) {}

    void update() {
        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        m_delta = deltaTime.count();

        if (m_delta > 0.0f) {
            float currentFPS = 1.0f / m_delta;
            m_smoothedFPS = (m_smoothedFPS * 0.99f) + (currentFPS * 0.01f);
        }
    }

    [[nodiscard]] float get_delta() const { return m_delta; }
    
    [[nodiscard]] float get_fps() const { return m_smoothedFPS; }

private:
    float m_delta;
    float m_smoothedFPS;
    std::chrono::steady_clock::time_point m_lastTime;
};

}