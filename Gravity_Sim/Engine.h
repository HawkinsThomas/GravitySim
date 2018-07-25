#pragma once
#include <iostream>
#include "Particle.h"
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

class Engine
{

    std::vector<Particle> particles = {}; //vector of particle pointers
    
private:

    // calculate the gravitational force between two particles
    force calculate_force(Particle particle1, Particle particle2);

public:

     Engine(int number_of_particles = 10); //constructor

     void move_particles(); //calculates the attraction forces between all particles and moves them accordingly

     std::vector<Particle>& get_particles(); //returns a reference to vector of particles

     void add_particle(Particle &particle); //add a particle object to particle member vector

     Particle generate_particle();

};