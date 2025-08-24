#include "Pong.h"
#include <cstdlib>
//
Player::Player() {}
Player::Player(sf::Vector2f p, sf::Vector2f s, sf::Vector2f v, sf::Color c, sf::Keyboard::Key u , sf::Keyboard::Key d){
    rec.setPosition(p);
    rec.setSize(s);
    rec.setFillColor(c);
    velocity = v;
    up = u;
    down = d;
}
Player::~Player() {}
//
void Player::Move() {
    if(sf::Keyboard::isKeyPressed(up)){
        rec.setPosition(rec.getPosition() + velocity);
    }
    if (sf::Keyboard::isKeyPressed(down))
    {
        rec.setPosition(rec.getPosition() - velocity);
    }
}
sf::RectangleShape Player::getRectangle() {
    return rec;
}
//
Ball::Ball() {}
Ball::Ball(sf::Vector2f p, int r, sf::Color c, sf::Vector2f v) {
    ball.setPosition(p);
    ball.setRadius(r);
    ball.setFillColor(c);
    velocity = v;
}
Ball::~Ball() {}
//
void Ball::Move(Player rec, Player rec1 , Wall w1 , Wall w2 ) {
    if(ball.getGlobalBounds().findIntersection(rec.getRectangle().getGlobalBounds()) ||
        ball.getGlobalBounds().findIntersection(rec1.getRectangle().getGlobalBounds())){
            velocity.x = -velocity.x;
    }
    if(ball.getGlobalBounds().findIntersection(w1.getRectangle().getGlobalBounds())||
        ball.getGlobalBounds().findIntersection(w2.getRectangle().getGlobalBounds())){
            velocity.y = -velocity.y;
        }
    ball.setPosition(ball.getPosition() + velocity);
}
sf::CircleShape Ball::getBall(){
    return ball;
}
//
Wall::Wall() {}
Wall::Wall(sf::Vector2f p, sf::Vector2f s) {
    rec.setPosition(p);
    rec.setSize(s);
}
Wall::~Wall() {};
//
sf::RectangleShape Wall::getRectangle(){
    return rec;
}
PongGame::PongGame() {}
PongGame::PongGame(sf::RenderWindow &window) {
    Init(window.getSize().x , window.getSize().y);
}
PongGame::~PongGame() {}
void PongGame::Init(float w , float h) {
    srand(time(NULL));
    sf::Vector2f size = {w/64 , h/6};
    sf::Color color = sf::Color::Green;
    sf::Vector2f velocity = { 0 , 7 };
    //
    sf::Vector2f pos1 = { 0 , h/2 - size.y };
    Player player1(pos1 , size , velocity , color , sf::Keyboard::Key::W , sf::Keyboard::Key::S);
    //
    sf::Vector2f pos2 = {w - w/64 , h/6};
    Player player2(pos2 , size , velocity , color , sf::Keyboard::Key::Up , sf::Keyboard::Key::Down);
    p1 = player1;
    p2 = player2;
    //
    sf::Vector2f ballpos = {w/2 - ball.getBall().getRadius() , h/2 - ball.getBall().getRadius()};
    sf::Color ballcolor = sf::Color::Red;
    sf::Vector2f ballve = {float(((rand() % 2) + 1) == 0 ? 10 :-10), float(((rand() % 2) + 1) == 0 ? 10 :-10)};
    int radius = 15;
    ball = Ball(ballpos , radius , ballcolor , ballve);
    //
    sf::Vector2f toppos = {0 , 0};
    sf::Vector2f botpos = {0 , h};
    sf::Vector2f wallsize = {w , 1};
    top = Wall(toppos , wallsize);
    bot = Wall(botpos , wallsize);
}
void PongGame::Draw(sf::RenderWindow & window){
    window.draw(p1.getRectangle());
    window.draw(p2.getRectangle());
    window.draw(ball.getBall());
}
void PongGame::Update(sf::RenderWindow&window){
    Draw(window);
}