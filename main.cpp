#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
int main()
{
    // Create a window with a specific resolution and default 32-bit color depth
    sf::VideoMode mode(800, 600);  // 800x600 resolution
    sf::RenderWindow window(mode, "SFML Window");

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}