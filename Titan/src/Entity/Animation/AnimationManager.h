#pragma once

#include <SFML/Graphics.hpp>

#include "tinyxml.h"
#include "Animation.h"

class AnimationManager
{

public:
    AnimationManager();
    ~AnimationManager();

    sf::String currentAnim;
    std::map<sf::String, Animation> animList;

    void loadFromXML(std::string fileName, sf::Texture &t);
    void set(sf::String name);
    void draw(sf::RenderWindow &window, float x = 0, float y = 0);
    void flip(bool b = 1);
    void tick(float time);
    void pause();
    void play();
    void play(sf::String name);
    bool isPlaying();
    float getHeight();
    float getWidth();
};