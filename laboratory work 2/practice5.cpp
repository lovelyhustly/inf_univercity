#include <SFML/Graphics.hpp>
#include <windows.h>
#include <functional>
#include <cmath>
#include <locale.h>

// Функция для отрисовки графика y = f(x)
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);
    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x);
        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }
    window.draw(graph);
}


void drawVerticalLine(sf::RenderWindow& window, float x, float scaleX, float thickness = 2.f, sf::Color color = sf::Color::Blue) {
    sf::Vector2u windowSize = window.getSize();
    float y_top = 0;
    float y_bottom = static_cast<float>(windowSize.y);
    float screenX = 400 + x * scaleX;

    sf::RectangleShape line;
    line.setPosition(screenX, y_top);
    line.setSize(sf::Vector2f(thickness, y_bottom));
    line.setFillColor(color);

    window.draw(line);
}

int main() {
    //Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Console app to display graphs");
    setlocale(LC_ALL, "Russian");
    // Переменная для хранения пользовательской точки
    sf::CircleShape userPoint(5); // Радиус 5 пикслелей
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false; // Переменная  для проверки существования пользовательской точки

    // 1 _ Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    // 2 _ Текст для отображения координат точки
    // Размер текста 20, положение текста (10,10), цвет белый. Текст храните в переменной coordinatesText
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);
    sf::Text numberZone;
    numberZone.setFont(font);
    numberZone.setCharacterSize(20);
    numberZone.setFillColor(sf::Color::White);
    numberZone.setPosition(10, 100);

    // Оси X и Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300); // Начало оси X
    xAxis[0].color = sf::Color::White; // Цвет оси
    xAxis[1].position = sf::Vector2f(750, 300); // Конец оси X
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);

    yAxis[0].position = sf::Vector2f(400, 50); // Начало оси Y
    yAxis[0].color = sf::Color::White; // Цвет оси
    yAxis[1].position = sf::Vector2f(400, 550); // Конец оси Y
    yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Проверка клика мышью
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Получение позиции клика
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Преобразование экранных координат в "математические"
                    float mathX = (mousePos.x - 400) / 20.0f; // Масштаб 30 по X
                    float mathY = -(mousePos.y - 300) / 20.0f; // Масштаб 100 по Y

                    // Установка новой пользовательсокой точки
                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true; // Помечаем что точка существует

                    // Обновление текста с координатами
                    std::string coordString = "x = " + std::to_string(mathX) + ", y = " + std::to_string(mathY);
                    coordinatesText.setString(coordString);

                    if (mathX >= -10 && mathX <= -3) {
                        if (mathY >= -10 && mathY <= 10)
                        {
                            numberZone.setString("Zone 2");
                        }
                        else if (mathY <= -10) {
                            numberZone.setString("Zone 3");
                        }
                    }
                    else if (mathX >= -3 && mathX <= 10) {
                        if (mathY >= -10 && mathY <= 10)
                        {
                            numberZone.setString("Zone 1");
                        }
                        else if (mathY <= -10) {
                            numberZone.setString("Zone 4");
                        }
                    }
                    else {
                        numberZone.setString("");
                    }
                }
            }
        }


        window.clear(sf::Color::Black);

        // 3 _ Отрисовка осей координат
        window.draw(xAxis);
        window.draw(yAxis);

        // 4 _  Отрисовка графика y = -x
        drawGraph(window, [](float x) { return -x; }, -10, 10, 20.0f, 20.0f, sf::Color::Red);
        //5 _ Отрисовка графика x = -3
        drawVerticalLine(window, -3, 20, 2, sf::Color::Blue);
        // 6 _ Отображение пользовательской точки 
        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText); //  текст координат
            window.draw(numberZone);
        }

        window.display();
    }

    return 0;
}
