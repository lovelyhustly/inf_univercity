#include <SFML/Graphics.hpp>

int main() {
    const int windowWidth = 500;
    const int windowHeight = 500;
    const int cellSize = 50;
    const int n= 10;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Colored Cells");

    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(1.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                float x = j * cellSize;
                float y = i * cellSize;
                cell.setPosition(x, y);
                if (i+j>=n+1 and (i+j)%2!=0) {
                    cell.setFillColor(sf::Color::Green);
                }
                else {
                    cell.setFillColor(sf::Color::White);
                }
                window.draw(cell);
            }
        }
        window.display();
    }

    return 0;
}