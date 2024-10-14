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

	void addAnimation(const std::string key);
	
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
		
		Animation(sf::Sprite& _sprite, sf::Texture& texture_sheet, float animation_timer, int start_x, int start_y, int end_x, int end_y, int _width, int _height)
			: sprite{_sprite}, textureSheet{texture_sheet}, animationTimer{animation_timer}, width{_width}, height{_height}
		{
			this->startRect = sf::IntRect(start_x, start_y, _width, _height);
			this->currentRect = startRect;
			this->startRect = sf::IntRect(end_x, end_y, _width, _height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		void play(const float& _dt)
		{
			this->timer = 10.f * _dt;
			if (this->timer >= this->animationTimer)
			{
				this->timer = 0.f;

				if (this->currentRect != endRect)
				{
					this->currentRect.left = this->width;
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

	std::unordered_map<std::string, Animation> animations;

	
};

