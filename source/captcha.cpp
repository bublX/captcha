#include "captcha.h"
#include "font.h"

std::array<sf::Text, 5> generate_captcha(const sf::View & view)
{
    const sf::Font & font = Font::Instance(); 
    std::array<sf::Text, 5> captcha = {sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font)};

    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    float l_border = center.x - size.x / 2;
    float between_letters = size.x / 6;
    float pos = l_border + between_letters;

    for (size_t i = 0; i != 5; ++i)
    {
        char letter = 'A' + rand() % 26; 
        captcha[i].setString(letter); 
        captcha[i].setCharacterSize(70 + rand() % 30);
        sf::Color color (rand() % 256, rand() % 256, rand() % 256);
        captcha[i].setFillColor(color);
        sf::FloatRect box = captcha[i].getLocalBounds();
        captcha[i].setOrigin(sf::Vector2f(box.size) / 2.f);
        captcha[i].setRotation(sf::degrees((rand() % 31)) * ((rand() % 2) * 2 - 1));
        float x_pos = pos + i * between_letters;
        float y_pos = center.y;
        captcha[i].setPosition(sf::Vector2f(x_pos, y_pos));
    }
    return captcha;
}