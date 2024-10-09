#include "GameState.hpp"

void GameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

void GameState::initCharacterFrames()
{
	this->texture.loadFromFile("assets/textures/right1.png");
	this->animationEntity.RightAnimation.push_back(texture);
	this->texture.loadFromFile("assets/textures/right2.png");
	this->animationEntity.RightAnimation.push_back(texture);
	this->animationEntity.RightAnimation.push_back(texture);
	this->texture.loadFromFile("assets/textures/right3.png");
	this->animationEntity.RightAnimation.push_back(texture);

	this->texture.loadFromFile("assets/textures/left1.png");
	this->animationEntity.LeftAnimation.push_back(texture);
	this->texture.loadFromFile("assets/textures/left2.png");
	this->animationEntity.LeftAnimation.push_back(texture);
	this->animationEntity.LeftAnimation.push_back(texture);
	this->texture.loadFromFile("assets/textures/left3.png");
	this->animationEntity.LeftAnimation.push_back(texture);

	this->texture.loadFromFile("assets/textures/front1.png");
	this->animationEntity.FrontAnimation.push_back(texture);
	this->texture.loadFromFile("assets/textures/front2.png");
	this->animationEntity.FrontAnimation.push_back(texture);
	this->animationEntity.FrontAnimation.push_back(texture);
	this->texture.loadFromFile("assets/textures/front3.png");
	this->animationEntity.FrontAnimation.push_back(texture);

	this->texture.loadFromFile("assets/textures/back1.png");
	this->animationEntity.BackAnimation.push_back(texture);
	this->texture.loadFromFile("assets/textures/back2.png");
	this->animationEntity.BackAnimation.push_back(texture);
	this->animationEntity.BackAnimation.push_back(texture);
	this->texture.loadFromFile("assets/textures/back3.png");
	this->animationEntity.BackAnimation.push_back(texture);


	
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys)
	: State(_window, _supportedKeys)
{
	this->initCharacterFrames();
	this->initKeybinds();

	this->currentFrame = 0;
	this->timeSinceLastUpdate = 0.0f;
	this->timeBetweenUpdates = 0.08f;
	

	this->texture.loadFromFile("assets/textures/mainStage.png");
	this->textures["mainStage"] = this->texture;
	this->background.setTexture(this->textures["mainStage"]);
}

GameState::~GameState()
{

}

void GameState::endState()
{
	std::cout << "Ending GameState!" << "\n";
}

void GameState::updateInput(const float& _dt)
{
	this->checkForQuit();
	timeSinceLastUpdate += _dt;

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")))
	{
		this->player.move(_dt, -1.f, 0.f);
		this->player.animation(timeSinceLastUpdate,timeBetweenUpdates, animationEntity.LeftAnimation, currentFrame);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")))
	{
		this->player.move(_dt, 1.f, 0.f);
		this->player.animation(timeSinceLastUpdate, timeBetweenUpdates, animationEntity.RightAnimation, currentFrame);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")))
	{
		this->player.move(_dt, 0.f, -1.f);
		this->player.animation(timeSinceLastUpdate, timeBetweenUpdates, animationEntity.BackAnimation, currentFrame);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")))
	{
		this->player.move(_dt, 0.f, 1.f);
		this->player.animation(timeSinceLastUpdate, timeBetweenUpdates, animationEntity.FrontAnimation, currentFrame);
	}
}

void GameState::update(const float& _dt)
{
	this->updateMousePositions();
	this->updateInput(_dt);

	this->player.update(_dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->player.render(target);
}
