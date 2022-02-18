#include "Game.h"

//private functions
void Game::initVariables()
{
	this->window = nullptr;


}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Galactic Space Shooter", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}
void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Textures/bullet.png");

}
void Game::initGUI()
{
    //load font
    if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf")) 
        std::cout << "Error::Game Failed::Font not loaded";	
    //init font text
    this->pointtext.setPosition(700.f, 20.f);
    this->pointtext.setFont(this->font);
    this->pointtext.setCharacterSize(25);
    this->pointtext.setFillColor(sf::Color::Yellow);
    this->pointtext.setString("Points:");
	        
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(100);
    this->gameOverText.setFillColor(sf::Color::Magenta);
    this->gameOverText.setString("Game Over");
    this->gameOverText.setPosition(this->window->getSize().x/2.f -this->gameOverText.getGlobalBounds().width/2.f, this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
	//MAKE windows resizable 
    //healthbar
    this->playerHpBar.setSize(sf::Vector2f(200.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 205));
}
void Game::initSystems()
{
    this->points = 0;
}
void Game::initWorld()
{
    if (!this->worldBackgroungTex.loadFromFile("Textures/bg2.jpg")) {
        std::cout << "error :background 2 texture not loaded";
   }; 
    this->worldBackground.setTexture(this -> worldBackgroungTex);
    if (!this->worldBackgroungTex2.loadFromFile("Textures/bg1.jpg")) {
        std::cout << "error :background 1 texture not loaded";
   };
}
void Game::initShip()
{
    this->ship = new Ship();
    
}
void Game::initStones()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}
//constructors destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initTextures();
    this->initWorld();
    this->initGUI();
    this->initShip();
    this->initStones();
    this->initSystems();
}

Game::~Game()
{
	delete this->window;
	delete this->ship;
	//delete textures
	for (auto& i : this->textures)
{
		delete i.second;
}
	// delete bullets
	for (auto* i : this->bullets) {
		delete i;
	}
	//delete stones
	for (auto* i : this->stones) {
	    delete i;
	}
}

//function

void Game::run()
{
    while (this->window->isOpen()) {
        this->updatePollEvents();
        if (this->ship->getHp() > 0){
        this->update();
        }
             
        this->render();
    }
}

void Game::updatePollEvents(){
    sf::Event ev;
    while (this->window->pollEvent(ev))
    {
        switch (ev.Event::type)
        {

        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape) {
                this->window->close();
            }
            break;
        }
    }

}

void Game::updateInput()
{
    //Move Ship
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->ship->move(-1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->ship->move(1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->ship->move(0.f, -1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->ship->move(0.f, 1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->ship->canAttack())
    {
        this->bullets.push_back(new Bullet(this->textures["BULLET"], this->ship->getpos().x + this->ship->getBounds().width / 2.f, this->ship->getpos().y, 0.f, -1.f, 5.f));
    }
}

void Game::updateGUI()
{
    std::stringstream ss;
    ss << "points:"<<this->points;
    this->pointtext.setString(ss.str());
    
    //update hpbar
    
    float percent= static_cast<float>( this->ship->getHp())/this->ship->getHpMax();
    this->playerHpBar.setSize(sf::Vector2f(200*percent,this->playerHpBar.getSize().y));

}

void Game::updateBullets()
{
    unsigned counter = 0;
    for (auto* bullet : this->bullets) {
        bullet->update();
        //bullet going top of screen
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {   //delete the bullets
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
            --counter;
        }
        ++counter;

    }
}

void Game::updateEnemies()
{   //spawning
    this->spawnTimer += 0.2f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->stones.push_back(new Stone(rand() % this->window->getSize().x - 20.f, -100.f));
        this->spawnTimer = 0.f;
    }
    //update
    unsigned counter = 0;
    for (auto* stone : this->stones) {
        stone->update();
        //bullet culling (top of screen)
        if (stone->getBounds().top  > this->window->getSize().y)
        {   //delete the stone
            delete this->stones.at(counter);
            this->stones.erase(this->stones.begin() + counter);
            --counter;
        }
        //stone ship collision
        else if (stone->getBounds().intersects(this->ship->getBounds())) {
            this->ship->loosehp(this->stones.at(counter)->getDamage());
            delete this->stones.at(counter);
            this->stones.erase(this->stones.begin() + counter);
            
        }
        ++counter;

    }
}

void Game::updateCombat()
{
    for (int i = 0; i < this->stones.size(); ++i)
    {
        bool enemy_deleted = false;
        for (size_t k = 0; k < bullets.size() && enemy_deleted==false ; k++) {
            if (this->bullets[k]->getBounds().intersects(this->stones[i]->getBounds())) {
                this->points += this->stones[i]->getPoints();

                delete this->stones[i];
                this->stones.erase(this->stones.begin() + i);

                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);
                enemy_deleted = true;
            }
        }
 
    }
}

void Game::updateWorld()
{
     if(this->points >= 100) {
        this->worldBackground.setTexture(this->worldBackgroungTex2);
    }
}

void Game::updateCollision()
{
    if (this->ship->getBounds().left < 0.f) {
        this->ship->setPosition(0.f, this->ship->getBounds().top);
    }  
    else if (this->ship->getBounds().left+ this->ship->getBounds().width >= this->window->getSize().x ){
        this->ship->setPosition(this->window->getSize().x- this->ship->getBounds().width, this->ship->getBounds().top);
    } 

    if (this->ship->getBounds().top + this->ship->getBounds().height >= this->window->getSize().y) {
        this->ship->setPosition(this->ship->getBounds().left, this->window->getSize().y- this->ship->getBounds().height);
    }  
    else if (this->ship->getBounds().top < 0.f) {
        this->ship->setPosition(this->ship->getBounds().left,0.f);
    }
}

void Game::update(){
    this->updateInput();
    this->updateBullets();
    this->ship->update();
    this->updateCollision();
    this->updateEnemies();
    this->updateCombat();
    this->updateWorld();
    this->updateGUI();
 
}

void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}

void Game::renderGUI()
{
    this->window->draw(this->pointtext);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}

void Game::render()
{  
    /*
    render the game objects*/
    this->window->clear(sf::Color(0,0,0,255));
    //draw game objects
    //draw background
    this->renderWorld();
    this->ship->render(*this->window);
    for (auto *bullet: this->bullets) {
        bullet->render(this->window);
    } for (auto *enemy: this->stones) {
        enemy->render(this->window);
    }
    this->renderGUI();
    //game over screen
    if (this->ship->getHp() <= 0) {
        this->window->draw(this->gameOverText);
    }
    this->window->display();
}

