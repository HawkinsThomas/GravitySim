// Gravity_Sim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "Engine.h"
#include <iostream>

int main()
{
    Engine engine{100};
    //Particle sun{ 15000000000000000000, 500, 500, 0, 0, sf::Color::Yellow };
    //sun.set_radius(10);
    //Particle &sun_ref = sun;
    //engine.add_particle(sun_ref);

    sf::RenderWindow window = { sf::VideoMode(1900, 1000), "Grav Sim!" }; // graphics window

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(); //delete all objects on canvas
        
        engine.move_particles();

        for (auto particle : engine.get_particles())
        {
            window.draw(particle.get_shape());
        }
        //std::cout << engine.get_particles().size() << "\n";
        window.display();
    }

    return 0;
}