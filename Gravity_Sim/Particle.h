#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>


struct force {
    float forceX;
    float forceY;
};

class Particle
{
    // member vars
    uint64_t mass;
    float positionX;
    float positionY;
    float velocityX;
    float velocityY;
    float accelerationX = 0; //default acceleration to 0
    float accelerationY = 0;
    float forceX = 0; //default forces to zero
    float forceY = 0;
    sf::CircleShape shape;

private:


    //set the radius of the particle so it is proportional to the mass
    void set_radius()
    {
        const double pi = 3.14159;
        float radius = sqrt(mass * 0.75 / pi) / 200;
        shape.setRadius(radius);
    }

    void set_color(sf::Color color)
    {
        shape.setFillColor(color);
    }

    void set_shape_position()
    {
        shape.setPosition(positionX - shape.getRadius(), positionY - shape.getRadius());
    }

    
public:

    // default constructor takes no paramters
    Particle();

    //constructor with args
    Particle(uint64_t u_mass, float u_positionX, float u_positionY, float u_velocityX = 0.f, float u_velocityY = 0.f, sf::Color u_color = sf::Color::Green); //declare default parameters in header file

    // get mass of particle
    int get_mass();

    // get x position of particle
    float get_positionX();


    // get y position of particle
    float get_positionY();

    // set shape position for drawing
    void set_position(float x, float y);

    //get shape object
    sf::CircleShape get_shape();

    // use this to reset the force to 0
    void set_force(force new_force) 
    {
        forceX = new_force.forceX;
        forceY = new_force.forceY;
    }

    // use this to sum all forces on a particle
    void add_force(force attraction_force)
    {
        forceX += attraction_force.forceX;
        forceY += attraction_force.forceY;
    }
    void accelerate();

    void move(); 

    void set_radius(float radius);
};