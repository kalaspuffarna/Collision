#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

using namespace sf;

bool collision(CircleShape const & c1, CircleShape const & c2 )
{
    return static_cast<int>(std::sqrt(std::pow(static_cast<int>(c1.getPosition().x - c2.getPosition().x), 2) + std::pow(static_cast<int>(c1.getPosition().y - c2.getPosition().y), 2))) <= c1.getRadius() * 2;
}


int main()
{
    RenderWindow window(sf::VideoMode(500, 500), "Collision", sf::Style::Titlebar | sf::Style::Close);
    double r{50};
    CircleShape pl(r);
    CircleShape npc(r);
    pl.setOrigin(r,r);
    npc.setOrigin(r,r);

    pl.setPosition(100, 200);
    npc.setPosition(200, 200);
    std::vector<std::pair<Keyboard::Key, Vector2i>> v
    {
        {Keyboard::Right, {1,0}},
        {Keyboard::Left, {-1,0}},
        {Keyboard::Up, {0,-1}},        
        {Keyboard::Down, {0,1}}
    };

    
    while(window.isOpen())
    {
        if(Keyboard::isKeyPressed(Keyboard::Escape))window.close();
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            npc.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
        }
        for(auto dir : v)
        {
            if(collision(pl, npc))
            {
                for(auto i : v)
                {
                     if(Keyboard::isKeyPressed(i.first))pl.move(i.second.x * -10, i.second.y * -10);
                }
                continue;
            }
            if(Keyboard::isKeyPressed(dir.first))pl.move(dir.second.x, dir.second.y);
        }
        window.clear();

        window.draw(pl);
        window.draw(npc);

        window.display();
        sleep(seconds(0.004));

    }
    

    return 0;
}