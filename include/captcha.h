#pragma once
#include <SFML/Graphics.hpp>
#include <array>

std::array<sf::Text, 5> generate_captcha(const sf::View& view);