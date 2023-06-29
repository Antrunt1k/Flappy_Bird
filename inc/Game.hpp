#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace mt
{
    class Game
    {
    private:
        int               m_width, m_height;
        std::string       m_caption;
        sf::RenderWindow* m_window = nullptr;
        sf::Clock         timer_fps;
        sf::Texture       background_texture;
        sf::Sprite        background;
        sf::Clock         m_timer;
    public:

        void Setup  (int   m_Width, int   m_Height, const std::string& m_caption);
        void Run    (float m_Width, float m_Height);
    };
}