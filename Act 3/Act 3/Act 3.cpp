#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    const int wnd_width = 800;
    const int wnd_height = 600;

    sf::RenderWindow window(sf::VideoMode(wnd_width, wnd_height), "Bounce");
    window.setFramerateLimit(60);

    sf::CircleShape ball(60.0f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(wnd_width / 2.0f, 2.0f);

    const float gravity = 0.5f;
    float velocityY = 0.0f;
    const float bounceFactor = 1.0f;
    const float constantBounceSpeed = 10.0f;
    bool usePercentageBounce = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        velocityY += gravity;
        sf::Vector2f position = ball.getPosition();
        position.y += velocityY;

        if (position.y > wnd_height - ball.getRadius() * 2) {
            position.y = wnd_height - ball.getRadius() * 2;

            if (usePercentageBounce) {
                velocityY = -velocityY * bounceFactor;
            }
            else {
                velocityY = -constantBounceSpeed;
            }

            if (std::abs(velocityY) < 1.0f) {
                velocityY = 0.0f;
            }
        }
        ball.setPosition(position);

        window.clear(sf::Color::Black);
        window.draw(ball); 
        window.display();
    }

    return 0;
}