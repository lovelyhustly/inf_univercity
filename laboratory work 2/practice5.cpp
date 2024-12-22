#include <SFML/Graphics.hpp>
#include <windows.h>
#include <functional>
#include <cmath>
#include <locale.h>

// ������� ��� ��������� ������� y = f(x)
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
    //�������� ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "Console app to display graphs");
    setlocale(LC_ALL, "Russian");
    // ���������� ��� �������� ���������������� �����
    sf::CircleShape userPoint(5); // ������ 5 ���������
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false; // ����������  ��� �������� ������������� ���������������� �����

    // 1 _ �������� ������
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    // 2 _ ����� ��� ����������� ��������� �����
    // ������ ������ 20, ��������� ������ (10,10), ���� �����. ����� ������� � ���������� coordinatesText
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

    // ��� X � Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300); // ������ ��� X
    xAxis[0].color = sf::Color::White; // ���� ���
    xAxis[1].position = sf::Vector2f(750, 300); // ����� ��� X
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);

    yAxis[0].position = sf::Vector2f(400, 50); // ������ ��� Y
    yAxis[0].color = sf::Color::White; // ���� ���
    yAxis[1].position = sf::Vector2f(400, 550); // ����� ��� Y
    yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // �������� ����� �����
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // ��������� ������� �����
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // �������������� �������� ��������� � "��������������"
                    float mathX = (mousePos.x - 400) / 20.0f; // ������� 30 �� X
                    float mathY = -(mousePos.y - 300) / 20.0f; // ������� 100 �� Y

                    // ��������� ����� ����������������� �����
                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true; // �������� ��� ����� ����������

                    // ���������� ������ � ������������
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

        // 3 _ ��������� ���� ���������
        window.draw(xAxis);
        window.draw(yAxis);

        // 4 _  ��������� ������� y = -x
        drawGraph(window, [](float x) { return -x; }, -10, 10, 20.0f, 20.0f, sf::Color::Red);
        //5 _ ��������� ������� x = -3
        drawVerticalLine(window, -3, 20, 2, sf::Color::Blue);
        // 6 _ ����������� ���������������� ����� 
        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText); //  ����� ���������
            window.draw(numberZone);
        }

        window.display();
    }

    return 0;
}
