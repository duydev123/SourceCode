#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../ShapedGames/PongGame/Pong.h"
#include <iostream>
//
int main(){
    // tạo window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Multi Game", sf::State::Fullscreen);
    // game tạm thời
    Pong::PongGame game(window);
    // vòng lập chính 
    while(window.isOpen()){
        window.setFramerateLimit(60);
        // event cơ bản của sfml
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            game.EventHandle(event);
        }
        window.clear(sf::Color::White);
        game.Update();
        // hàm update của gam đã đóng gói
        // cái luôn cần thiết để chạy
        window.display();
    }
}