#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>

const int width = 800;
const int height = 600;
const float ballSize = 20.0f;
const float targetSize = 40.0f;
const float playerSize = 20.0f;
const float gravity = 9.81f;

struct Ball {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float acceleration;
};

struct Target {
    sf::RectangleShape shape;
    sf::Vector2f velocity;
};

int random(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int main() {

    sf::RenderWindow window(sf::VideoMode(width, height), "Wild physics");
    window.setFramerateLimit(60);


    std::vector<Ball> balls;
    for (int i = 0; i < 5; ++i) {
        Ball ball;
        ball.shape.setRadius(ballSize / 2);
        ball.shape.setFillColor(sf::Color::Green);
        ball.shape.setPosition(random(0, width - ballSize), -ballSize);
        ball.velocity = sf::Vector2f(0, 100.0f); // Velocidad inicial hacia abajo
        ball.acceleration = gravity;
        balls.push_back(ball);
    }

    std::vector<Target> targets;
    for (int i = 0; i < 3; ++i) {
        Target target;
        target.shape.setSize(sf::Vector2f(targetSize, targetSize));
        target.shape.setFillColor(sf::Color::Yellow);
        target.shape.setPosition(0, random(0, height - targetSize));
        target.velocity = sf::Vector2f(200.0f, 0.0f); // Velocidad inicial hacia la derecha
        targets.push_back(target);
    }

    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("./assets/Perfect DOS VGA 437.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
        return 1;
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Puntuación: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    for (auto it = balls.begin(); it != balls.end(); ++it) {
                        if (it->shape.getGlobalBounds().contains(mousePos)) {
                            it = balls.erase(it);
                            score++;
                            scoreText.setString("Puntuación: " + std::to_string(score));
                            break;
                        }
                    }

                    for (auto it = targets.begin(); it != targets.end(); ++it) {
                        if (it->shape.getGlobalBounds().contains(mousePos)) {
                            it = targets.erase(it); 
                            score++;
                            scoreText.setString("Puntuación: " + std::to_string(score));
                            break; 
                        }
                    }
                }
            }
        }

        sf::Time deltaTime = clock.restart();

        for (auto& ball : balls) {
            ball.velocity.y += ball.acceleration * deltaTime.asSeconds();
            ball.shape.move(ball.velocity * deltaTime.asSeconds());

            if (ball.shape.getPosition().y + ballSize > height) {
                ball.velocity.y *= -1;
                ball.shape.setPosition(ball.shape.getPosition().x, height - ballSize);
            }
            if (ball.shape.getPosition().x + ballSize > width || ball.shape.getPosition().x < 0) {
                ball.velocity.x *= -1;
            }
        }

        for (auto& target : targets) {
            target.shape.move(target.velocity * deltaTime.asSeconds());

            if (target.shape.getPosition().x + targetSize > width || target.shape.getPosition().x < 0) {
                target.velocity.x *= -1;
            }
        }

        window.clear(sf::Color::Black);
        for (const auto& ball : balls) {
            window.draw(ball.shape);
        }
        for (const auto& target : targets) {
            window.draw(target.shape);
        }
        window.draw(scoreText);
        window.display();
    }

    return 0;
}
