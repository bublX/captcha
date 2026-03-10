#pragma once
#include <SFML/Graphics.hpp>
#include <array>
// объявление функции, для хорошей организации проекта
std::array<sf::Text, 5> generate_captcha(const sf::View & view);