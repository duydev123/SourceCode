#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <functional>
#include <optional>

// class người chơi
namespace Pong
{
    class Button{
        //
        private:
            sf::RectangleShape board;
            //
        public:
        Button();
        Button(sf::Vector2f bpos , sf::Vector2f bsize, sf::Texture &t);
        ~Button();
        sf::RectangleShape getBoard();
        bool onClick(sf::RenderWindow &w, const std::optional<sf::Event> &event);
    };  
    class Player
    {
        //
    private:
        sf::RectangleShape rec;
        //
        sf::Vector2f velocity;
        //
        sf::Keyboard::Key up;
        sf::Keyboard::Key down;

    public:
        //
        Player();
        Player(sf::Vector2f p, sf::Vector2f s, sf::Vector2f v, sf::Color c, sf::Keyboard::Key u, sf::Keyboard::Key d);
        ~Player();
        //
        void Move(sf::RenderWindow &window);
        sf::RectangleShape getRectangle();
    };
    // Tường
    class Wall
    {
        //
    private:
        sf::RectangleShape rec;
        //
    public:
        Wall();
        Wall(sf::Vector2f p, sf::Vector2f s);
        ~Wall();
        //
        sf::RectangleShape getRectangle();
    };
    // Quả bóng
    class Ball
    {
        //
    private:
        sf::CircleShape ball;
        sf::Vector2f velocity;
        //
    public:
        Ball();
        Ball(sf::Vector2f p, int r, sf::Color c, sf::Vector2f v);
        ~Ball();
        //
        void Move(Player rec, Player rec1, Wall w1, Wall w2 , int& state , int w);
        sf::CircleShape getBall();
    };
    //
    class GameUI
    {
        //
        private:
        float width;
        float height;
        public:
        GameUI();
        GameUI(float w, float h);
        ~GameUI();
        sf::VertexArray DrawGrid(int size , sf::Color c);
        sf::RectangleShape Drawtitle(sf::Vector2f pos , sf::Vector2f size , sf::Texture &t);
    };
    // Tên Game và quản lý game
    class PongGame
    {
        // biến
    private:
        Player p1;
        Player p2;
        Ball ball;
        Wall top;
        Wall bot;
        std::vector<sf::Texture> tex;
        // button 
        Button menubtn1;
        Button menubtn2;
        //
        sf::RenderWindow &window;
        
        GameUI UI;
        //
        int GameState;
        sf::RectangleShape tile;

    public:
        void Init(float w, float h);
        PongGame(sf::RenderWindow &w);
        ~PongGame();
        void Update();
        // Hàm để để những thứ cần vẽ lên màn hình
        void Draw();
        //
        void Render();
        //
        //
        void EventHandle(const std::optional<sf::Event> &e);
    };
}