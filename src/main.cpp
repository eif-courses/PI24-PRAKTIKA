#include <SFML/Graphics.hpp>

#include <iostream>

int main() {

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::Texture catTexture("textures/cat.png");

    sf::Sprite cat(catTexture);


   // cat.set



    sf::Clock clock; // starts the clock
    float secondCounter = 0.0f;
    int currentTimer = 0;

    sf::Font font;
    if (!font.openFromFile(
        "fonts/PlayfulTime-BLBB8.ttf")) {
        return -1;
        // error...
    }


    sf::Text text(font); // a font is required to make a text object

    // set the string to display
    // set the character size
    text.setCharacterSize(100); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        secondCounter += deltaTime.asSeconds();

        // Check if a second has passed
        if (secondCounter >= 1.0f) {
            std::cout << "One second has passed!" << std::endl;

            // Alternatively, if you want to print the total elapsed seconds:
            // std::cout << "Total seconds: " << totalTimeCounter << std::endl;

            // Reset the counter, keeping the remainder
            secondCounter -= 1.0f; // This maintains precision better than setting to 0

            currentTimer++;

            text.setString(std::to_string(currentTimer));


            //std::cout << currentTimer << std::endl;
        }

        bool catPeekLeft = false;

        while (const std::optional event = window.pollEvent()) {
            float amount = 50;
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                // left key is pressed: move our character

                if (!catPeekLeft) {
                    auto currX = cat.getPosition().x;
                    cat.setPosition({currX + 360,0});
                    cat.setScale({-1.0f, 1.0f});
                    catPeekLeft = true;
                }else {
                    cat.move({-1.f * amount, 0.f});
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                // left key is pressed: move our character
                if (catPeekLeft) {
                    auto currX = cat.getPosition().x;
                    cat.setPosition({currX - 360,0});
                    cat.setScale({1.0f, 1.0f});
                    catPeekLeft = false;
                }else {
                    cat.move({1.f * amount, 0.f});
                }

                //cat.setPosition()

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                // left key is pressed: move our character
                cat.move({0.f, -1.f * amount});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                // left key is pressed: move our character
                cat.move({0.f, 1.f * amount});
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window
                sf::Mouse::setPosition(localPosition, window);

                cat.setPosition({(float) localPosition.x - amount, (float) localPosition.y - amount});
            }
        }

        window.clear();

        window.draw(text);
        window.draw(cat);

        window.display();
    }
}
