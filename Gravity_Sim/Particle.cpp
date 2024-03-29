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

void Particle::set_radius(float radius)
{
    shape.setRadius(radius);
}
void Particle::accelerate()
{
    accelerationX =  forceX / mass;
    accelerationY =  forceY / mass;
    //std::cout << accelerationX << "\n";
    //std::cout << accelerationY << "\n";
}


void Particle::move()
{
    velocityX += accelerationX; // assume time of 1 second
    velocityY += accelerationY;

    positionX += velocityX;
    positionY += velocityY;

    //if ((positionX > 1920) or (positionX < 0))
    //{
    //    velocityX *= -0.60;
    //    if (positionX > 1920) { positionX = 1919; }
    //    else { positionX = 1; }
    //}
    //
    //if ((positionY > 1000) or (positionY < 0))
    //{
    //    velocityY *= -0.60;
    //    if (positionY > 1000) { positionY = 999; }
    //    else { positionY = 1; }
    //}
    //
    set_position(positionX, positionY); //updates particle object and shape as well
}
//get shape object
sf::CircleShape Particle::get_shape()
{
    return shape;
}

void Particle::absorb(Particle &particle)
{
    //99.9% of kinetic energy is conserverd in collision
    velocityX = 0.999 * ((mass * velocityX) + (particle.get_mass() * particle.velocityX)) / (mass + particle.get_mass()); //calculate new x velocity from inelastic colision
    velocityY = 0.999 * ((mass * velocityY) + (particle.mass * particle.velocityY)) / (mass + particle.mass); //calculate new y velocity from inelastic colision
    
    if (mass < particle.get_mass())
    {
        set_position(particle.get_positionX(), particle.get_positionY());

    
    }
    mass += particle.get_mass(); //add masses together
    set_radius();   // set the new radius
    collision_count += 1;
    collision_count += particle.collision_count;

    
    if (collision_count == 1)
    {
        set_color(sf::Color::Magenta);
    }
    else if (collision_count <= 10)
    {
        set_color(sf::Color::Blue);
    }
    else if (collision_count <= 50 )
    {
        set_color(sf::Color::Red);
    }
    else if (collision_count <= 100)
    {
        set_color(sf::Color::Green);
    }
    else
    {
        set_color(sf::Color::Yellow);
    }
    particle.set_delete_flag();
}