#include "stdafx.h"
#include "Engine.h"
#include <math.h>
#include <cstdlib>
#include <algorithm>



Engine::Engine(int number_of_particles)
    : particles{}
{
    for (int i = 0; i < number_of_particles; i++)
    {
        particles.push_back(generate_particle());
    }
}


force Engine::calculate_force(Particle particle1, Particle particle2)
{
    
    
    const int gravity_constant = 500000; //made up gravitational constant
    float delta_x = particle1.get_positionX() - particle2.get_positionX(); // calculate the horizontal distance
    float delta_y = particle1.get_positionY() - particle2.get_positionY(); // calculate the vertical distance
    float radians = atan2((delta_y), delta_x); //calculate the angle between particles in radians 
    radians = fmod(radians, (2 * M_PI));

    float distance = (sqrt(pow(delta_x, 2) + pow(delta_y, 2))); //calcualte the absolute distance between particles
    if (distance * 1.2 < particle1.get_shape().getRadius() + particle2.get_shape().getRadius())
    {
        
        force attraction_force{ 0, 0 };
        return attraction_force;

    }
    float forceX = gravity_constant * (cos(radians)) / pow(distance, 2); //force of attraction from other particle on *this on x axis
    float forceY = gravity_constant * (sin(radians)) / pow(distance, 2); //force of attraction from other particle on *this on y axis
    force attraction_force{ forceX, forceY };
    return attraction_force;
    //other_particle.accelerate(-1 * forceX, -1 * forceY); //equal and opposite force applied to other particle
    

}
//Generate a new particle object
Particle Engine::generate_particle()
{
    Particle particle { static_cast <uint64_t> (rand() % 500 * 1500), static_cast <float> (fmod(rand(), 1900)), static_cast <float> (fmod(rand(), 1000)), (static_cast <float> (fmod(rand(), 1000)) / 10000) - 0.05f, (static_cast <float> (fmod(rand(), 1000)) / 10000) - 0.05f };
    return particle;
}

void Engine::move_particles()
{
    force zero_force = force{ 0, 0 }; //zero net force variable used to zero out each particle before recalculating
    for (auto &particle : particles)
    {
        particle.set_force(zero_force); //zero out the force on each particle
    }

    int i = 1;

    for (auto &particle : particles)
    {
        for (int j = 0; j < particles.size() - i; ++j)
        {
           force new_force = calculate_force(particle, particles[j + i]);
           if (new_force.forceX == zero_force.forceX)
           {
               particles[j + i].absorb(particle);
           }
           else
           {
               force opposite_force{ new_force.forceX * -1,new_force.forceY * -1 };
               particle.add_force(opposite_force); //add calculated force to particle 1
               particles[j + i].add_force(new_force); // add the opposite of calculated force to particle 2
           }
           
        }

        ++i;
    }



    for (int k = 0 ; k < particles.size(); k++)
    {
        if (particles[k].get_delete_flag() == true)
        {
            particles.erase(particles.begin() + k);
        }
        else
        {
            particles[k].accelerate();
            particles[k].move();
        }
        
        
    }
}

std::vector<Particle>& Engine::get_particles()
{
    return particles;
}

void Engine::add_particle(Particle &particle)
{
    particles.push_back(particle);
}