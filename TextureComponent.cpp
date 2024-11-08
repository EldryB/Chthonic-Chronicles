#include "TextureComponent.hpp"

TextureComponent::TextureComponent(sf::Sprite& _sprite, sf::Texture& texture_sheet)
    : sprite{ _sprite }, textureSheet{ texture_sheet }
{
    this->sprite.setTexture(texture_sheet, true);
}

TextureComponent::~TextureComponent()
{

}

void TextureComponent::addTexture(const std::string& key, int start_frame_x, int start_frame_y, int _width, int _height)
{
    this->textures[key] = sf::IntRect(start_frame_x * _width, start_frame_y * _height, _width, _height);
}

void TextureComponent::setTexture(const std::string& key)
{
    if (this->textures.find(key) != this->textures.end())
    {
        this->sprite.setTextureRect(textures[key]);
    }
}

void TextureComponent::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}