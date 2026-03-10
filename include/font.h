#pragma once
#include <SFML/Graphics.hpp>
// Создаем Singleton класс Font, который сделан по образцу Скотта Мейерса
class Font { 
    public:
    // в нем удален конструктор копирования
        Font (const Font &) = delete; 
    // оператор присваивания 
        Font & operator = (const Font &) = delete; 
    // метод Instance возвращает константную ссылку на загруженный шрифт согласно заданию
        static const sf::Font & Instance() { 
            static Font instance; 
            return instance.font;
        }
    protected:
    // дефолтный конструктор находится в защищенном поле
        Font() = default; 
    private:
    // в ресурсах класса хранится скачанный шрифт
        sf::Font font{"assets/fonts/latin.ttf"};
};