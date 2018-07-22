#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>


class Particle
{
    // member vars
    int mass;
    float positionX;
    float positionY;
    float velocityX;
    float velocityY;
    float accelerationX = 0; //default acceleration to 0
    float accelerationY = 0;
    sf::CircleShape shape;

private:


    //set the radius of the particle so it is proportional to the mass
    void set_radius()
    {
        const double pi = 3.14159;
        float radius = sqrt(mass * 0.75 / pi) / 5;
        shape.setRadius(radius);
    }

    void set_color(sf::Color color)
    {
        shape.setFillColor(color);
    }

    void set_shape_position()
    {
        shape.setPosition(positionX, positionY);
    }

    void accelerate(float force_x, float force_y);
public:

    // default constructor takes no paramters
    Particle();

    //constructor with args
    Particle(int u_mass, float u_positionX, float u_positionY, float u_velocityX = 0.f, float u_velocityY = 0.f, sf::Color u_color = sf::Color::Green); //declare default parameters in header file

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

    void attract(Particle othershape);

    void move(); 
};