#include "DiceAnimation.hpp"

DiceAnimation::DiceAnimation() : animationTime(2.0f), elapsedTime(0.0f), rolling(false) {}

void DiceAnimation::loadSprite(const std::string& textureFile)
{
    if (!texture.loadFromFile(textureFile))
    {
        throw std::runtime_error("Error al cargar la textura del dado");
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    sprite.setOrigin(16, 16);

    //Aqui puedo cambiar la escala
    sprite.setScale(10.0f, 10.0f);
}


void DiceAnimation::rollAnimation(int sides)
{
    finalValue = dice.roll(sides);
    rolling = true;
    elapsedTime = 0.0f;
}

void DiceAnimation::update(float deltaTime)
{
    if (!rolling)
        return;

    elapsedTime += deltaTime;

    if (elapsedTime >= animationTime)
    {
        rolling = false;
        setSpriteFace(finalValue);
    }
    else
    {
        int randomFace = dice.roll(20);
        setSpriteFace(randomFace);
    }
}

void DiceAnimation::draw(sf::RenderWindow& window)
{
    // Coloca el sprite en el centro de la ventana
    sf::Vector2u windowSize = window.getSize();
    sprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    window.draw(sprite);
}

bool DiceAnimation::isRolling() const
{
    return rolling;
}
void DiceAnimation::setSpriteFace(int value)
{
    //Manejo de la posicion del area del sprite
    int row = (value - 1) / 5;
    int column = (value - 1) % 5;
    sprite.setTextureRect(sf::IntRect(column * 32, row * 32, 32, 32));
}

//Ejemplo de uso
/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice Roll Animation");
    DiceAnimation diceAnimation;
    diceAnimation.loadSprite("spriteDice.png");

    sf::Clock clock;
    bool rolling = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G && !rolling)
            {
                diceAnimation.rollAnimation(20);
                rolling = true;
            }
        }

        float deltaTime = clock.restart().asSeconds();
        diceAnimation.update(deltaTime);

        window.clear();
        diceAnimation.draw(window);
        window.display();

        // Reinicia la variable de control después de la animación
        if (!diceAnimation.isRolling())
            rolling = false;
    }

    return 0;
}

*/