#pragma once
#include <SFML/Graphics.hpp>

class Font { 
    public:
        Font (const Font &) = delete; 
        Font & operator = (const Font &) = delete; 
        static const sf::Font & Instance() { 
            static Font instance; 
            return instance.font;
        }

    protected:
        Font() = default; 
    private:
        sf::Font font{"assets/fonts/latin.ttf"};
};