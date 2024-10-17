#pragma once

#include <iostream>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AnimationComponent
{
public:
	AnimationComponent(sf::Sprite& _sprite, sf::Texture& texture_sheet);

	virtual ~AnimationComponent();

	void addAnimation(const std::string key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int _width, int _height);

	void play(const std::string key, const float& _dt);

private:
	class Animation
	{
	public:
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& _sprite, sf::Texture& texture_sheet,
			float animation_timer,
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int _width, int _height)
			: sprite{ _sprite }, textureSheet{ texture_sheet },
			animationTimer{ animation_timer }, width{ _width }, height{ _height }
		{
			this->timer = 0.f;
			this->startRect = sf::IntRect(start_frame_x * _width, start_frame_y * _height, _width, _height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * _width, frames_y * _height, _width, _height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		void play(const float& _dt)
		{
			this->timer += 50.f * _dt;
			if (this->timer >= this->animationTimer)
			{
				this->timer = 0.f;

				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else
				{
					this->currentRect.left = this->startRect.left;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
		}

		void reset()
		{
			this->timer = 0.f;
			this->currentRect = this->startRect;
		}

	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::unordered_map<std::string, Animation*> animations;


};


