#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../ShapedGames/PongGame/Pong.h"
//
int main(){
    // tạo window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Multi Game", sf::State::Fullscreen);
    // game tạm thời
    PongGame game(window);
    // vòng lập chính 
    while(window.isOpen()){
        // event cơ bản của sfml
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // màu nền
        window.clear(sf::Color::White);
        // hàm update của gam đã đóng gói
        game.Update(window);
        // cái luôn cần thiết để chạy
        window.display();
    }
}