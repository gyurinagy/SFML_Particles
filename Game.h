#pragma once

#include <SFML/Graphics.hpp>
#include "Particle.h"

#include "vector"
#include <math.h>
#include <cstdlib>

#define GRAVITY 0.05      
#define RESISTANCE 0.001  
#define EXP_FORCE 5 

class Game
{
    sf::RenderWindow* _window;
    sf::VideoMode _videoMode;
    sf::Event _ev;

    /// OBJECTS / VARIABLES
    bool _leftBtn;
    bool _rightBtn;
    float _gravity;
    float _resistance;
    float _expForce;
    std::vector<Particle*> _particles;

    /// PRIVATE FUNCTIONS
    void generateParticles(int amount);
    void initializeVariables();
    void initWindow();
    
public:

    /// CONSTRUCTOR / DESTRUCTOR
    Game();
    virtual ~Game();

    /// FUNCTIONS
    void pollEvents();
    void updateShapes();
    void update();
    void render();
    void run();
};

extern Game* CreateGame();
