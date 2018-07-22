// Gravity_Sim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    //sf::CircleShape shape(50.f);
    //shape.setFillColor(sf::Color::Red);

    Particle particle_0{ 1000, 10,10, 0.01f, 0.01f };
    Particle particle_1{ 500000, 500, 500, 0, 0 };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        particle_0.attract(particle_1);
        particle_1.attract(particle_0);
        particle_0.move();
        particle_1.move();
        window.draw(particle_0.get_shape());
        window.draw(particle_1.get_shape());
        window.display();
    }

    return 0;
}