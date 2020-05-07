#include "Game.h"

Game* CreateGame() { return new Game(); }

void Game::generateParticles(int amount)
{
    for (int i = 0; i < amount; i++) {
        _particles.push_back(new Particle({ (float)(rand() % _window->getSize().x),(float)(rand() % _window->getSize().y) }));
    }
}

/// ****************** PRIVATE FUNCTIONS ******************
void Game::initializeVariables() {
    generateParticles(500);
}


void Game::initWindow() {
    
    _window = new sf::RenderWindow();
    _window->create(_videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    _window->setFramerateLimit(90);
}



/// ****************** CONSTRUCTOR / DESTRUCTOR ******************
Game::Game(): 
    _window(nullptr), _videoMode(1080, 720),_leftBtn(false), _gravity((float)GRAVITY), _resistance((float)RESISTANCE), _expForce((float)EXP_FORCE)
{
    initWindow();
    initializeVariables();
}

Game::~Game()
{
    for (auto a : _particles)
        delete a;
    delete _window;
}

/// ****************** FUNCTIONS ******************


void Game::pollEvents() {
    while (_window->pollEvent(_ev)) {
        switch (_ev.type) {

        case sf::Event::Closed:
            _window->close();
            break;
        case sf::Event::KeyPressed:
            if (_ev.key.code == sf::Keyboard::Escape)
                _window->close();
            if (_ev.key.code == sf::Keyboard::Space)
                generateParticles(500);
            break;
        case sf::Event::MouseButtonPressed:
            /*if (_ev.mouseButton.button == sf::Mouse::Left) 
                _leftBtn = true;*/
            if (_ev.mouseButton.button == sf::Mouse::Right)
                _rightBtn = true;
            break;
        case sf::Event::MouseButtonReleased:
            _leftBtn = false;
            break;

        }

    }
}
void Game::updateShapes() {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        _leftBtn = true;

    if (_leftBtn) {
        _gravity = (float)(10 * GRAVITY);
        _resistance = (float)(10 * RESISTANCE);
//        _leftBtn = false;
    }else {
        _gravity = (float)GRAVITY;
        _resistance = (float)RESISTANCE;
    }

    if (_rightBtn) {
        for (auto a : _particles)
            a->explode(sf::Mouse::getPosition(*_window), _expForce);
        _rightBtn = false;
    }
    for (auto a : _particles)
        a->step(sf::Mouse::getPosition(*_window), _gravity, _resistance);
}

void Game::update() {
    pollEvents();
    updateShapes();
}


void Game::render() {

    _window->clear();
    for(auto a:_particles)
        a->drawTo(*_window);
    _window->display();
}

void Game::run() {
    while (_window->isOpen()) {

        update();
        render();

    }
}
