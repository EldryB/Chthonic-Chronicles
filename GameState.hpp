#pragma once

#include "State.hpp"
#include "Animation.hpp"
class GameState :
    public State
{
public:
    GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states);
    virtual ~GameState();

    void updateInput(const float& _dt);
    void update(const float& _dt);
    void render(sf::RenderTarget* target = nullptr);

private:
    Entity player;
    Main_Animation animationEntity;
    int currentFrame;
    float timeSinceLastUpdate;
    float timeBetweenUpdates;

    void initKeybinds();
    void initTextures();
    void initBackground();
    void initCharacterFrames();
    void limitMainBackground(sf::Sprite& spr);
    float pos_x(sf::Sprite& spr);
    float pos_y(sf::Sprite& spr);
    void set_x(float _x, sf::Sprite& sprite);
    void set_y(float _y, sf::Sprite& sprite);
};

