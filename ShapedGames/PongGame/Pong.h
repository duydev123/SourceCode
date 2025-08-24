#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// class người chơi
class Player{
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
    Player(sf::Vector2f p , sf::Vector2f s , sf::Vector2f v , sf::Color c , sf::Keyboard::Key u , sf::Keyboard::Key d);
    ~Player();
    //
    void Move();
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
class Ball{
    //
    private:
    sf::CircleShape ball;
    sf::Vector2f velocity;
    //
    public:
    Ball();
    Ball(sf::Vector2f p , int r , sf::Color c ,sf::Vector2f v);
    ~Ball();
    //
    void Move(Player rec, Player rec1, Wall w1 , Wall w2 );
    sf::CircleShape getBall();
};
// Tên Game và quản lý game
class PongGame{
    // biến
    private:
    Player p1;
    Player p2;
    Ball ball;
    Wall top;
    Wall bot;    
    public:
    void Init( float w , float h );
    PongGame();
    PongGame(sf::RenderWindow& window);
    ~PongGame();
    // Mọi game đều phải có cấu trúc như này . update sé được override 1 hàm thuần ảo Igame 
    void Update(sf::RenderWindow &window);
    // Hàm để để những thứ cần vẽ lên màn hình
    void Draw(sf::RenderWindow& window);
};