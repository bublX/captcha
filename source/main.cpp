#include <SFML/Graphics.hpp>
#include "font.h"
#include "captcha.h"

bool compare(const sf::Text & user_input, const std::array<sf::Text, 5> & captcha)
{
    std::string str;
    std::string user_str = user_input.getString();
    for (char & letter : user_str)
        if (letter >= 'a' && letter <= 'z')
            letter -= 'a' - 'A';
    for (const auto & letter : captcha)
        str += letter.getString();
    return str == user_str;
}

int main()
{
    std::srand(std::time(nullptr));
    sf::RenderWindow window{ sf::VideoMode({ 400,300 }), "Captcha" };
    sf::View view(sf::FloatRect({0, 0}, {400, 300}));
    sf::Text user_input{Font::Instance()};
    std::string str;
    user_input.setFillColor(sf::Color::Red);
    std::array<sf::Text, 5> captcha = generate_captcha(view);
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event -> is<sf::Event::Closed>()) 
            {
                captcha = generate_captcha(view);
                str.clear();
                user_input.setString(str);
            }
            else if (auto resize_event = event -> getIf<sf::Event::Resized>())
            {
                view.setSize(sf::Vector2f(resize_event -> size));
                view.setCenter(sf::Vector2f(resize_event -> size) / 2.f);
                window.setView(view);
                captcha = generate_captcha(view);
                str.clear();
                user_input.setString(str);
            }
            else if (auto ptr_event = event -> getIf<sf::Event::TextEntered>()) 
            {
                if ((ptr_event -> unicode <= 'Z' && ptr_event -> unicode >= 'A') || (ptr_event -> unicode <= 'z' && ptr_event -> unicode >= 'a'))
                {
                    str += static_cast<char>(ptr_event -> unicode);
                    user_input.setString(str);
                }
            }
            else if (auto ptr_event = event -> getIf<sf::Event::KeyPressed>()) {
                if (ptr_event -> code == sf::Keyboard::Key::Enter)
                {
                    if (compare(user_input, captcha))
                        window.close();
                    else
                    {
                        captcha = generate_captcha(view);
                        str.clear();
                        user_input.setString(str);
                    }
                }
                if (ptr_event -> code == sf::Keyboard::Key::Backspace && !str.empty())
                {
                    str.pop_back();
                    user_input.setString(str);
                }
            }
        }
        window.clear();
        for (const auto & letter : captcha)
            window.draw(letter);
        user_input.setPosition(sf::Vector2f(10, 10));
        window.draw(user_input); 
        window.display();
    }
}
