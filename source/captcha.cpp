#include "captcha.h"
#include "font.h"

std::array<sf::Text, 5> generate_captcha(const sf::View & view)
{
    // пользуемся порождающим классом для создания шрифта
    const sf::Font & font = Font::Instance();
    // создаем каптчу, при этом учитывая то, что она не может быть создана по дефолту в виду отсутствия конструктора по умолчанию
    // из-за этого пользуемся инициализацией списком
    std::array<sf::Text, 5> captcha = {sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font)};
    // получаем координаты центра и размер видимой области
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();
    // вычисляем координату левой границы
    float l_border = center.x - size.x / 2;
    // находим необходимое расстояния между буквами, понимая, что 5 букв образуют 6 промежутков
    float between_letters = size.x / 6;
    // вычисляем позицию для первой буквы
    float pos = l_border + between_letters;
    // циклом пробегаемся по каждой букве и обрабатываем ее
    for (size_t i = 0; i != 5; ++i)
    {
        // генерируем букву
        char letter = 'A' + rand() % 26; 
        // присваиваем букву нашей каптче в ее ячейку
        captcha[i].setString(letter); 
        // выбираем рандомный размер буквы
        captcha[i].setCharacterSize(70 + rand() % 30);
        // генерируем цвет для буквы 
        sf::Color color (rand() % 256, rand() % 256, rand() % 256);
        // устанавливаем цвет букве
        captcha[i].setFillColor(color);
        sf::FloatRect box = captcha[i].getLocalBounds();
        // получаем хитбокс нашей буквы
        captcha[i].setOrigin(sf::Vector2f(box.size) / 2.f);
        // генерируем поворот буквы
        captcha[i].setRotation(sf::degrees((rand() % 31)) * ((rand() % 2) * 2 - 1));
        // задаем позиции нашей букве
        float x_pos = pos + i * between_letters;
        float y_pos = center.y;
        // присваиваем полученную позицию конкретной букве
        captcha[i].setPosition(sf::Vector2f(x_pos, y_pos));
    }
    // возвращаем :)
    return captcha;
}