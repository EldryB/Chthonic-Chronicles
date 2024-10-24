#include "JobMenuState.hpp"

JobMenuState::JobMenuState(Jobs& jobs, Resources& resources, sf::Font& font)
    : jobs(jobs), resources(resources), font(font)
{
    title.setFont(font);
    title.setString("Settlement Management");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::Black);
    title.setPosition(100, 20);

    villagersAvailable.setFont(font);
    villagersAvailable.setCharacterSize(24);
    villagersAvailable.setFillColor(sf::Color::Black);
    villagersAvailable.setPosition(100, 80);

    // Inicializa las listas de trabajos y recursos
    updateJobList();
    updateResourceList();

    // Botón para recolección de recursos
    collectButton.setSize(sf::Vector2f(150, 50));
    collectButton.setPosition(800, 550);
    collectButton.setFillColor(sf::Color(192, 192, 192));

    // Botón para desbloquear trabajos
    unlockButton.setSize(sf::Vector2f(150, 50));
    unlockButton.setPosition(100, 550);
    unlockButton.setFillColor(sf::Color(192, 192, 192));
}

void JobMenuState::updateJobList()
{
    jobTexts.clear();
    addButtons.clear();
    subtractButtons.clear();

    for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
    {
        // Texto para los trabajos
        sf::Text jobText;
        jobText.setFont(font);
        jobText.setString(jobs.getJobName(static_cast<JobTypes>(i)));
        jobText.setCharacterSize(20);
        jobText.setFillColor(sf::Color::Black);
        jobText.setPosition(100, 120 + i * 40);
        jobTexts.push_back(jobText);

        // Botón de restar aldeanos
        sf::RectangleShape subtractButton;
        subtractButton.setSize(sf::Vector2f(30, 30));
        subtractButton.setPosition(300, 120 + i * 40);
        subtractButton.setFillColor(sf::Color(192, 192, 192));
        subtractButtons.push_back(subtractButton);

        // Botón de sumar aldeanos
        sf::RectangleShape addButton;
        addButton.setSize(sf::Vector2f(30, 30));
        addButton.setPosition(400, 120 + i * 40);
        addButton.setFillColor(sf::Color(192, 192, 192));
        addButtons.push_back(addButton);
    }
}

void JobMenuState::updateResourceList()
{
    resourceTexts.clear();
    amountTexts.clear();

    for (int i = 0; i < static_cast<int>(ResourceTypes::count); ++i)
    {
        // Texto para los recursos
        sf::Text resourceText;
        resourceText.setFont(font);
        resourceText.setString(resources.getResourceName(static_cast<ResourceTypes>(i)));
        resourceText.setCharacterSize(20);
        resourceText.setFillColor(sf::Color::Black);
        resourceText.setPosition(500, 120 + i * 40);
        resourceTexts.push_back(resourceText);

        // Texto para la cantidad de recursos
        sf::Text amountText;
        amountText.setFont(font);
        amountText.setString(std::to_string(resources.getResourceAmount(static_cast<ResourceTypes>(i))));
        amountText.setCharacterSize(20);
        amountText.setFillColor(sf::Color::Black);
        amountText.setPosition(650, 120 + i * 40);
        amountTexts.push_back(amountText);
    }
}

void JobMenuState::handleInput(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        handleMouseClick(mousePos);
    }
}

void JobMenuState::handleMouseClick(sf::Vector2i mousePos)
{
    // Interactuar con los botones de aldeanos
    for (int i = 0; i < addButtons.size(); ++i)
    {
        if (addButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            jobs.assignVillagers(static_cast<JobTypes>(i));
            updateJobList();
        }
        else if (subtractButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            jobs.removeVillagers(static_cast<JobTypes>(i));
            updateJobList();
        }
    }

    // Interacción con el botón de recolectar recursos
    if (collectButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        jobs.collectResources(resources);
        updateResourceList();
    }

    // Interacción con el botón de desbloquear trabajos
    if (unlockButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
        {
            if (jobs.getJobAmount(static_cast<JobTypes>(i)) == -1)
            {
                jobs.unlockJob(static_cast<JobTypes>(i));
                updateJobList();
                break;
            }
        }
    }
}

void JobMenuState::update()
{
    // Actualizar lógica si es necesario
}

void JobMenuState::render(sf::RenderWindow& window)
{
    window.draw(title);
    window.draw(villagersAvailable);

    // Dibujar trabajos y aldeanos
    for (const auto& jobText : jobTexts)
    {
        window.draw(jobText);
    }

    for (const auto& subtractButton : subtractButtons)
    {
        window.draw(subtractButton);
    }

    for (const auto& addButton : addButtons)
    {
        window.draw(addButton);
    }

    // Dibujar recursos
    for (const auto& resourceText : resourceTexts)
    {
        window.draw(resourceText);
    }

    for (const auto& amountText : amountTexts)
    {
        window.draw(amountText);
    }

    // Dibujar botones
    window.draw(collectButton);
    window.draw(unlockButton);
}
