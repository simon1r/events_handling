#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size) :
        sf::RectangleShape(size),
        speed(150.f)
    {
        srand(static_cast<unsigned int>(time(nullptr)));

        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;

        setFillColor(sf::Color(r, g, b));
        setOutlineThickness(2.f);
        setOutlineColor(sf::Color::Black);
    }

    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key) {
        sf::Vector2f movement(0.f, 0.f);
        float distance = speed * elapsed.asSeconds();

        if (key == sf::Keyboard::Left) {
            movement.x -= distance;
        }
        else if (key == sf::Keyboard::Right) {
            movement.x += distance;
        }
        else if (key == sf::Keyboard::Up) {
            movement.y -= distance;
        }
        else if (key == sf::Keyboard::Down) {
            movement.y += distance;
        }

        move(movement);
    }

    bool isClicked(sf::Vector2i &mouse_position) const {
        sf::FloatRect boundingBox = getGlobalBounds();
        return boundingBox.contains(static_cast<sf::Vector2f>(mouse_position));
    }

private:
    float speed;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Rectangle");

    CustomRectangleShape rect(sf::Vector2f(100.f, 100.f));
    rect.setPosition(100.f, 100.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                rect.moveInDirection(sf::seconds(1.f / 60.f), event.key.code);
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                if (rect.isClicked(mouse_position)) {
                    int r = rand() % 256;
                    int g = rand() % 256;
                    int b = rand() % 256;

                    rect.setFillColor(sf::Color(r, g, b));
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(rect);
        window.display();
    }

    return 0;
}
