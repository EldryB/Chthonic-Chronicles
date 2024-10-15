#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent(sf::Sprite& _sprite, sf::Texture& texture_sheet)
	: sprite{ _sprite }, textureSheet{ texture_sheet }
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& it : this->animations)
	{
		delete it.second;
	}
}

void AnimationComponent::addAnimation(const std::string key,
	float animation_timer, int start_frame_x,
	int start_frame_y, int frames_x, int frames_y, int _width, int _height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, _width, _height);
}

void AnimationComponent::play(const std::string key, const float& _dt)
{
	this->animations[key]->play(_dt);
}
