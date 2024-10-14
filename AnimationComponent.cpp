#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent(sf::Sprite& _sprite, sf::Texture& texture_sheet)
	: sprite{_sprite}, textureSheet{texture_sheet}
{

}

AnimationComponent::~AnimationComponent()
{

}

void AnimationComponent::addAnimation(const std::string key)
{

}

void AnimationComponent::play(const std::string key, const float& _dt)
{
	this->animations[key].play(_dt);
}
