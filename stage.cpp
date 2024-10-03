#include <settings.hpp>
#include <char.hpp>
#include <animation.hpp>
#include <stage.hpp>

Stage::Stage(float _w, float _h, sf::Sprite spr) noexcept
	: width{ _w }, height{ _h }, sprite{ spr }
{
	//empty
}

void Stage::render(sf::RenderTarget& target) const noexcept
{
	target.draw(sprite);
}

void Stage::setTexture(sf::Texture& tex) noexcept
{
	sprite.setTexture(tex);
}

sf::Sprite Stage::get_sprite() noexcept
{
	return sprite;
}
