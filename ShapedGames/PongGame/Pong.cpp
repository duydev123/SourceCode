#include "Pong.h"
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
namespace Pong
{
    Player::Player() {}
    Player::Player(sf::Vector2f p, sf::Vector2f s, sf::Vector2f v, sf::Color c, sf::Keyboard::Key u, sf::Keyboard::Key d)
    {
        rec.setPosition(p);
        rec.setSize(s);
        rec.setFillColor(c);
        velocity = v;
        up = u;
        down = d;
    }
    Player::~Player() {}
    //
    void Player::Move(sf::RenderWindow &window)
    {
        if (sf::Keyboard::isKeyPressed(up) && rec.getPosition().y > 0)
        {
            rec.setPosition(rec.getPosition() - velocity);
        }
        if (sf::Keyboard::isKeyPressed(down) && rec.getPosition().y < window.getSize().y - rec.getSize().y)
        {
            rec.setPosition(rec.getPosition() + velocity);
        }
    }
    sf::RectangleShape Player::getRectangle()
    {
        return rec;
    }
    //
    Ball::Ball() {}
    Ball::Ball(sf::Vector2f p, int r, sf::Color c, sf::Vector2f v)
    {
        ball.setPosition(p);
        ball.setRadius(r);
        ball.setFillColor(c);
        velocity = v;
    }
    Ball::~Ball() {}
    //
    void Ball::Move(Player rec, Player rec1, Wall w1, Wall w2, int& state ,int w)
    {
        if (ball.getGlobalBounds().findIntersection(rec.getRectangle().getGlobalBounds()) ||
            ball.getGlobalBounds().findIntersection(rec1.getRectangle().getGlobalBounds()))
        {
            velocity.x = -velocity.x;
        }
        if (ball.getGlobalBounds().findIntersection(w1.getRectangle().getGlobalBounds()) ||
            ball.getGlobalBounds().findIntersection(w2.getRectangle().getGlobalBounds()))
        {
            velocity.y = -velocity.y;
        }
        if (ball.getPosition().x < -5 || ball.getPosition().x > w + 5){
            state = 0;
        }
        ball.setPosition(ball.getPosition() + velocity);
    }
    sf::CircleShape Ball::getBall()
    {
        return ball;
    }
    //
    Wall::Wall() {}
    Wall::Wall(sf::Vector2f p, sf::Vector2f s)
    {
        rec.setPosition(p);
        rec.setSize(s);
    }
    Wall::~Wall() {};
    //
    sf::RectangleShape Wall::getRectangle()
    {
        return rec;
    }
    //
    GameUI::GameUI() {}
    GameUI::GameUI(float w , float h) : width(w) , height(h) {}
    GameUI::~GameUI() {}
    sf::VertexArray GameUI::DrawGrid(int size , sf::Color c) {
        sf::VertexArray line(sf::PrimitiveType::Lines);
        for (int i = 0; i <= width; i += size)
        {
            sf::Vertex v1;
            v1.color = c;
            v1.position = sf::Vector2f({float(i), 0});
            line.append(v1);
            sf::Vertex v2;
            v2.color = c;
            v2.position = sf::Vector2f({float(i), height});
            line.append(v2);
        }
        for (int j = 0; j <= height; j += size)
        {
            sf::Vertex v1;
            v1.color = c;
            v1.position = sf::Vector2f(0, float(j));
            line.append(v1);

            sf::Vertex v2;
            v2.color = c;
            v2.position = sf::Vector2f(width , float(j));
            line.append(v2);
        }
        return line;
    }
    sf::RectangleShape GameUI::Drawtitle(sf::Vector2f pos , sf::Vector2f size, sf::Texture &t){
        sf::RectangleShape temp;
        temp.setPosition(pos);
        temp.setSize(size);
        temp.setTexture(&t);
        return temp;
    }
    //
    Button::Button() {}
    Button::~Button() {}
    Button::Button(sf::Vector2f bpos, sf::Vector2f bsize, sf::Texture &t ) 
    {
        board.setPosition(bpos);
        board.setSize(bsize);
        board.setTexture(&t);
        //
    }
    sf::RectangleShape Button::getBoard(){
        return board;
    }
    bool Button::onClick(sf::RenderWindow &w ,const std::optional<sf::Event> &event) {
        if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousepos = w.mapPixelToCoords({mouse->position.x, mouse->position.y});
            std::cout << mousepos.x;
            if(board.getGlobalBounds().contains(mousepos)){
                return true;
            }
        }
        return false;
    }
    //
    PongGame::PongGame(sf::RenderWindow &w) : window(w)
    {
        Init(w.getSize().x, w.getSize().y);
        GameState = 0;
    }
    PongGame::~PongGame() {}
    void PongGame::Init(float w, float h)
    {
        GameState = 1;
        srand(time(NULL));
        //
        UI = GameUI(w , h);
        //
        sf::Texture text;
        sf::Texture text1;
        sf::Texture title;
        if (text.loadFromFile("ShapedGames/PongGame/assets/Start.png") && text1.loadFromFile("ShapedGames/PongGame/assets/Quit.png") && title.loadFromFile("ShapedGames/PongGame/assets/Title.png"))
        {
            text = sf::Texture("ShapedGames/PongGame/assets/Start.png");
            text1 = sf::Texture("ShapedGames/PongGame/assets/Quit.png");
            title = sf::Texture("ShapedGames/PongGame/assets/Title.png");
            tex.push_back(text);
            tex.push_back(text1);
            tex.push_back(title);
        }
        else std::cout << "failed";
        sf::Vector2f btnSize = {320, 140};
        sf::Vector2f btnPos1 = {w/2 - 140, h/2 - 80 - 40};
        menubtn1 = Button(btnPos1 , btnSize ,   tex[0] );
        //
        sf::Vector2f btnPos2 = {w/2- 140 , h/2 + 60 };
        menubtn2 = Button(btnPos2 , btnSize , tex[1] );
        //
        sf::Vector2f tileSize = {800 , 150};
        sf::Vector2f tilePos = {w - 1350 , 150};
        tile = UI.Drawtitle(tilePos , tileSize , tex[2]);
        //
        sf::Vector2f size = {w / 64, h / 6};
        sf::Color color = sf::Color::Green;
        sf::Vector2f velocity = {0, 7};
        //
        sf::Vector2f pos1 = {0, h / 2 - size.y / 2};
        Player player1(pos1, size, velocity, color, sf::Keyboard::Key::W, sf::Keyboard::Key::S);
        //
        sf::Vector2f pos2 = {w - w / 64, h / 2 - size.y / 2};
        Player player2(pos2, size, velocity, color, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down);
        p1 = player1;
        p2 = player2;
        //
        int radius = 25;
        sf::Vector2f ballpos = {w / 2 - radius, h / 2 - radius};
        sf::Color ballcolor = sf::Color::Red;
        sf::Vector2f ballve = {float(((rand() % 2) + 1) == 0 ? 10 : -10), float(((rand() % 2) + 1) == 0 ? 10 : -10)};
        ball = Ball(ballpos, radius, ballcolor, ballve);
        //
        sf::Vector2f toppos = {0, 0};
        sf::Vector2f botpos = {0, h};
        sf::Vector2f wallsize = {w, 1};
        top = Wall(toppos, wallsize);
        bot = Wall(botpos, wallsize);
    }
    void PongGame::Draw()
    {
        //
        if(GameState == 1)
        {
            window.draw(UI.DrawGrid(60, sf::Color(167, 196, 181, 255)));
            window.draw(p1.getRectangle()); 
            window.draw(p2.getRectangle());
            window.draw(ball.getBall());
        }
        if(GameState == 0 ){
            window.draw(UI.DrawGrid(180, sf::Color(167, 196, 181, 255)));
            window.draw(menubtn1.getBoard());
            window.draw(menubtn2.getBoard());
            window.draw(tile);
        }
    }
    void PongGame::Update()
    {
        Draw();
        Render();
    }
    void PongGame::Render()
    {
        p1.Move(window);
        p2.Move(window);
        ball.Move(p1, p2, top, bot , GameState , window.getSize().x );
    }
    void PongGame::EventHandle(const std::optional<sf::Event> &e){
        if(menubtn1.onClick(window,e) && GameState == 0){
            Init(window.getSize().x , window.getSize().y);
        }
        if(menubtn2.onClick(window,e) && GameState == 0){
        }
    }
}
//