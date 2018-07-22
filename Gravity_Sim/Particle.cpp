#include "stdafx.h"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Particle.h"
#include <iostream>


// default constructor takes no paramters
Particle::Particle() : mass{ 0 }, positionX{ 0 }, positionY{ 0 }, velocityX{ 0 }, velocityY{ 0 }
{
}

//constructor with args
Particle::Particle(int u_mass, float u_positionX, float u_positionY, float u_velocityX, float u_velocityY, sf::Color u_color)
: mass {u_mass}, 
positionX { u_positionX }, 
positionY { u_positionY }, 
velocityX { u_velocityX }, 
velocityY { u_velocityY }  //memeber initialization list
{
    set_radius();
    set_color(u_color);
    set_position(positionX, positionY);
}

// get mass of particle
int Particle::get_mass()
{
    return mass; 
}

// get x position of particle
float Particle::get_positionX()
{
    return positionX;
}

// get y position of particle
float Particle::get_positionY()
{
    return positionY; 
}
        // set shape position for drawing
void Particle::set_position(float x, float y)
{
    positionX = x;
    positionY = y;
    set_shape_position();
}
void Particle::accelerate(float force_x, float force_y)
{
    accelerationX += force_x / mass;
    accelerationY += force_y / mass;
}

void Particle::attract(Particle other_particle)
{
    const int gravity_constant = 5; //made up gravitational constant
    float delta_x = positionX - other_particle.get_positionX(); // calculate the horizontal distance
    float delta_y = positionX - other_particle.get_positionY(); // calculate the vertical distance
    float radians = atan2((-1 * delta_y), delta_x); //calculate the angle between particles in radians 
    radians = fmod(radians, (2 * M_PI));
    std::cout << radians << "\n"; 
    float distance = (sqrt(pow(delta_x, 2) + pow(delta_y, 2))); //calcualte the absolute distance between particles
    float forceX = -1 * gravity_constant * (cos(radians)) / pow(distance, 2); //force of attraction from other particle on *this on x axis
    float forceY = gravity_constant * (sin(radians)) / pow(distance, 2); //force of attraction from other particle on *this on y axis

    accelerate(forceX, forceY); 
    //other_particle.accelerate(-1 * forceX, -1 * forceY); //equal and opposite force applied to other particle
}

void Particle::move()
{
    velocityX += accelerationX; // assume time of 1 second
    velocityY += accelerationY;

    positionX += velocityX;
    positionY += velocityY;

    set_position(positionX, positionY); //updates particle object and shape as well
}
        //get shape object
sf::CircleShape Particle::get_shape()
{
    return shape;
}