#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>

class TextureComponent
{
public:
    TextureComponent(sf::Sprite& _sprite, sf::Texture& texture_sheet);
    virtual ~TextureComponent();

    void addTexture(const std::string& key, int start_frame_x, int start_frame_y, int _width, int _height);
    void setTexture(const std::string& key);
    void render(sf::RenderTarget* target);

private:
    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    std::unordered_map<std::string, sf::IntRect> textures;
};

