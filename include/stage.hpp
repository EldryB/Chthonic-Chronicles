#pragma once

#include<SFML/Graphics.hpp>

class Stage
{
public:

	Stage(float _w, float _h, sf::Sprite spr) noexcept;

	Stage(const Stage&) = delete;

	Stage& operator = (Stage&) = delete;

	void render(sf::RenderTarget& target) const noexcept;

	sf::Sprite get_sprite() noexcept;

	void setTexture(sf::Texture& tex)noexcept;

private:

	float width;
	float height;
	sf::Sprite sprite;
};

