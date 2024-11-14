    #pragma once

    #include "Jobs.hpp"
    #include "MenuState.hpp"

    class JobMenuState :
        public State
    {
    public:
        JobMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p);

        virtual ~JobMenuState();
    
        void updateInput(const float& _dt);

        void updateButtons();

        void update(const float& _dt);

        void renderButtons(sf::RenderTarget* target = nullptr);

        void render(sf::RenderTarget* target = nullptr);

    private:
        std::vector<Button*> addButtons;
        std::vector<Button*> substractButtons;
        std::vector<Button*> collectButtons;
        std::unordered_map<std::string, Button*> buttons;
        Jobs* jobs;
        Resources* resources;
        Player* player;

        std::vector<sf::Text> jobAmount;
        std::vector<sf::Text> resourceAmount;
        sf::Sprite backgroundTooltip;

        int availableVillagers;

        void initVariables();
    
        void initTextures();

        void initBackground();
    
        void initFonts();
    
        void initKeybinds();

        void initButtons();

        void initJobList();

        void initResourceList();

        std::string getTooltipMessage(JobTypes _jobs);
    };

