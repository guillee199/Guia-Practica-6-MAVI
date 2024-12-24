#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    const int wnd_width = 800;
    const int wnd_height = 600;

    sf::RenderWindow window(sf::VideoMode(wnd_width, wnd_height), "Space");
    window.setFramerateLimit(60);

    sf::CircleShape circle(60.0f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(wnd_width / 2.5f, wnd_height / 2.5f);

    sf::Vector2f position = circle.getPosition();
    sf::Vector2f velocidad(0.0f, 0.0f);
    sf::Vector2f acceleration(0.0f, 0.0f);
    const float maxSpeed = 5.0f;
    const float accelRate = 0.2f;
    const float friction = 0.1f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        acceleration = sf::Vector2f(0.0f, 0.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            acceleration.x = -accelRate;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            acceleration.x = accelRate;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            acceleration.y = -accelRate;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            acceleration.y = accelRate;
        }

        velocidad += acceleration;

        if (acceleration.x == 0) {
            if (velocidad.x > 0) {
                velocidad.x -= friction;
                if (velocidad.x < 0) velocidad.x = 0;
            }
            else if (velocidad.x < 0) {
                velocidad.x += friction;
                if (velocidad.x > 0) velocidad.x = 0;
            }
        }
        if (acceleration.y == 0) {
            if (velocidad.y > 0) {
                velocidad.y -= friction;
                if (velocidad.y < 0) velocidad.y = 0;
            }
            else if (velocidad.y < 0) {
                velocidad.y += friction;
                if (velocidad.y > 0) velocidad.y = 0;
            }
        }

        if (velocidad.x > maxSpeed) velocidad.x = maxSpeed;
        if (velocidad.x < -maxSpeed) velocidad.x = -maxSpeed;
        if (velocidad.y > maxSpeed) velocidad.y = maxSpeed;
        if (velocidad.y < -maxSpeed) velocidad.y = -maxSpeed;

        position += velocidad;

        if (position.x < 0) position.x = 0;
        if (position.x > wnd_width - circle.getRadius() * 2) position.x = wnd_width - circle.getRadius() * 2;
        if (position.y < 0) position.y = 0;
        if (position.y > wnd_height - circle.getRadius() * 2) position.y = wnd_height - circle.getRadius() * 2;

        circle.setPosition(position);
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}