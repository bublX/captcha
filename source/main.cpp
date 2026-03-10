#include <SFML/Graphics.hpp>
#include "font.h"
#include "captcha.h"

// Постарался организовать проект так, чтобы он был разбит по логичным блокам и все не лежало в одном файле

// создаем функцию сравнения ввода юзера и каптчи
bool compare(const sf::Text & user_input, const std::array<sf::Text, 5> & captcha)
{
    // завели две вспомогательные строки для облегчения сравнения
    std::string str;
    std::string user_str = user_input.getString();
    // модифицируем маленькие буквы в большие при надобности
    for (char & letter : user_str)
        if (letter >= 'a' && letter <= 'z')
            letter -= 'a' - 'A';
    // каптчу копируем в строку
    for (const auto & letter : captcha)
        str += letter.getString();
    // возвращаем результат сравнения
    return str == user_str;
}

int main()
{
    // выставили сид
    std::srand(std::time(nullptr));
    // создали окно
    sf::RenderWindow window{ sf::VideoMode({ 400,300 }), "Captcha" };
    // определили видимую область
    sf::View view(sf::FloatRect({0, 0}, {400, 300}));
    // задали текст пользователя
    sf::Text user_input{Font::Instance()};
    std::string str;
    // установили цвет
    user_input.setFillColor(sf::Color::Red);
    // сгенерировали каптчу
    std::array<sf::Text, 5> captcha = generate_captcha(view);
    // обработка событий
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            // для закрытия
            if (event -> is<sf::Event::Closed>()) 
            {
                // обнулили юзерский ввод, пересоздали каптчу
                captcha = generate_captcha(view);
                str.clear();
                user_input.setString(str);
            }
            // для изменения размера
            else if (auto resize_event = event -> getIf<sf::Event::Resized>())
            {
                // обработали перемещение окна
                view.setSize(sf::Vector2f(resize_event -> size));
                view.setCenter(sf::Vector2f(resize_event -> size) / 2.f);
                window.setView(view);
                // обнулили юзерский ввод, пересоздали каптчу
                captcha = generate_captcha(view);
                str.clear();
                user_input.setString(str);
            }
            // для ввода текста
            else if (auto ptr_event = event -> getIf<sf::Event::TextEntered>()) 
            {
                // обработка попадания в диапазон
                if ((ptr_event -> unicode <= 'Z' && ptr_event -> unicode >= 'A') || (ptr_event -> unicode <= 'z' && ptr_event -> unicode >= 'a'))
                {
                    // добавляем в строку юзера
                    str += static_cast<char>(ptr_event -> unicode);
                    user_input.setString(str);
                }
            }
            // обрабатываем определенные кнопки
            else if (auto ptr_event = event -> getIf<sf::Event::KeyPressed>()) {
                // для Enter
                if (ptr_event -> code == sf::Keyboard::Key::Enter)
                {
                    // совпало -> закрыли
                    if (compare(user_input, captcha))
                        window.close();
                    // не совпало -> обнулили юзерский ввод, пересоздали каптчу
                    else
                    {
                        captcha = generate_captcha(view);
                        str.clear();
                        user_input.setString(str);
                    }
                }
                // обработали Backspace, не забываем проверку на пустоту строки
                if (ptr_event -> code == sf::Keyboard::Key::Backspace && !str.empty())
                {
                    // удалили последний элемент
                    str.pop_back();
                    user_input.setString(str);
                }
            }
        }
        // вывод каптчи и юзерской строки
        window.clear();
        for (const auto & letter : captcha)
            window.draw(letter);
        // установка положения юзерской строчки
        user_input.setPosition(sf::Vector2f(10, 10));
        window.draw(user_input); 
        window.display();
    }
}
