#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    const int wnd_width = 800;
    const int wnd_height = 600;

    sf::RenderWindow window(sf::VideoMode(wnd_width, wnd_height), "Fast & Furious");
    window.setFramerateLimit(60);

    sf::CircleShape circle(60.0f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(0.0f, wnd_height / 2.0f - circle.getRadius());

    float Vi = 5.0f;
    float Vfinal = 80.0f;
    float vel = Vi;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2f pos = circle.getPosition();
        pos.x += vel;

        if (pos.x > wnd_width) {
            pos.x = -circle.getRadius() * 2;
            vel += 5.0f;
            if (vel >= Vfinal) {
                window.close();
            }
        }
        circle.setPosition(pos);
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
