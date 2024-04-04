#include "ShipBattle.h"

// ====================================
// Constructor & Destructor Section
// ====================================

ShipBattle::ShipBattle() {
    this->player = new Player(ofGetWidth() / 2, ofGetHeight() / 2);
    this->playerScore = 0;
    this->killspreeTimer = 0;
    
    font.load("Fonts/Orbitron.ttf", 20, true);
    indicatorFont.load("Fonts/Orbitron.ttf", 10, true);
    backgroundImage.load("Menu_Images/BattleArea.jpg");
    bombImage.load("CompressedImages/Bomb-min.png");
}

// ====================================
// Core Functionality Section
// ====================================


// Update Method
void ShipBattle::update() {
    // Boss spawn logic
    if (EnemyManager::isBossSpawning()) {
        displayBossWarning = true;
        SoundManager::stopSong("battle");
    } 
    else {
        displayBossWarning = false;
    }

    // Update shield status
    player->updateShield(ofGetLastFrameTime());

    // Activate shield when 'q' is pressed
    if(ofGetKeyPressed('q')) {
        player->activateShield();
    }

    // Update enemies and player
    EnemyManager::updateEnemies(player);
    this->player->processPressedKeys();
    this->player->update();
    wrapCoords(this->player->pos);

    // Update scoring and kill spree timer
    playerScore += EnemyManager::getPointsScored() * scoreMultiplier() * killSpreeMode();
    this->player->setScore(playerScore);
    killspreeTimer = EnemyManager::getKillSpreeTimer();

    // Update player projectiles
    if (!this->player->bullets.empty()) {
        updateBullets();
    }

   
    checkHP();
}
void ShipBattle::checkHP() {
    if (this->player->health <= 0) {
        if (player->getLives() > 0) {
            player->loseLife();
            player->health = 100; // Reset player health
        } else {
           this->setNextState("GameOverState");
        SoundManager::stopSong("battle");
        if(EnemyManager::getSpawningBossType() != ""){
            SoundManager::stopSong(EnemyManager::getSpawningBossType());
        }
            // Write the current score to a file
            ofstream scoreFile("currentScore.txt");
            if (scoreFile.is_open()) {
                scoreFile << playerScore;
                scoreFile.close();
            }
            this->setFinished(true);
            EnemyManager::cleanUp();
    }
    
}
}
void ShipBattle::drawLivesIndicator() const {
    // Set font color
    ofSetColor(ofColor::white);

    // Draw image
    player->getSprite().draw(10, ofGetHeight() - 100, 50, 50);

    // Draw remaining lives next to the image
    font.drawString("Lives: " + to_string(player->getLives()), 70, ofGetHeight() - 70);
}

//====== Draw Method ====== 
void ShipBattle::draw() {
    ofSetBackgroundColor(ofColor::black);
    backgroundImage.draw(0, 0, ofGetWidth(), ofGetHeight());

    indicatorFont.drawString("BOMB", ofGetWidth() - 150, 25);
    if(player->hasBomb) {
        float scaledWidth = 50; 
        float scaledHeight = 50; 

        // Calculate position to keep the icon aligned as desired
        // Adjusting for the new size to keep it in the top right corner
        float iconX = ofGetWidth() - 124 - scaledWidth / 2;
        float iconY = 56 - scaledHeight / 2;

        // Draw the scaled bomb icon
        bombImage.draw(iconX, iconY, scaledWidth, scaledHeight);
    }

    // Draw shield if active
    if(player->isShieldActive()) {
        ofSetColor(0, 0, 255, 127); // Semi-transparent blue for the shield
        ofDrawCircle(player->pos, 40); // Assuming a radius of 40 for the visual representation
    }


    // Draw the score
    ofSetColor(ofColor::white);
    font.drawString("SCORE " + to_string(playerScore), ofGetWidth() / 2 - 50, 50);

    // Draw enemies and player
    EnemyManager::drawEnemies();
    player->draw();
    draw_bullets();
    
    // Draw boss warning if needed
    if (displayBossWarning) {
        // Semi-transparent red screen tint
        ofSetColor(255, 0, 0, 128);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        // Warning text
        ofSetColor(255);
        font.drawString("BOSS APPROACHING!", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
    }

    // Draw UI elements
    healthBar(player->health, 100);
    killSpreeTimer(this->killspreeTimer, 150);
    drawShieldBar(player->getShieldCapacity(), 100);
    
    //Draw a mini box for the bomb. Make sure to draw the bomb inside this box.
        ofNoFill();
        ofDrawRectangle(ofGetWidth() - 150, 30, 50, 50);
        ofFill();
    
    drawLivesIndicator();
}

// ====================================
// Input Handling Section
// ====================================

void ShipBattle::keyPressed(int key) {
    player->addPressedKey(key);
    
    //DEBUG KEYS - Press these keys to ease the debugging with the game
    if(key == 'k') {
        EnemyManager::toggleHitBoxes = !EnemyManager::toggleHitBoxes; 
        player->showHitbox = !player->showHitbox;
    }
    if(key == 'o')  player->health = 100;
    if(key == 'p')  playerScore += 10000;

    if(key == 'e' && player->hasBomb) {
        player->useBomb();
        EnemyManager::applyBombEffect(); // Apply bomb effect through EnemyManager
    } 
}

void ShipBattle::keyReleased(int key) {
    key = tolower(key);
    this->player->removePressedKey(key);
}

void ShipBattle::mousePressed(int x, int y, int button) {
    // Implementation for mousePressed event in case you want to do something with this
}

// ====================================
// Helper Methods Section
// ====================================

void ShipBattle::wrapCoords(ofPoint &currentPos) {
    // Screen wrapping logic for player ship
    if (currentPos.x < 0.0) currentPos.x = ofGetWidth() - 10;
    if (currentPos.x >= ofGetWidth()) currentPos.x = 10;
    if (currentPos.y < 0.0) currentPos.y = ofGetHeight() - 10;
    if (currentPos.y >= ofGetHeight()) currentPos.y = 10;
}

void ShipBattle::draw_bullets() {
    // Draw all player bullets
    for (auto &bullet : this->player->bullets) {
        bullet.draw();
    }
}

void ShipBattle::updateBullets() {
    // Update logic for player bullets
    for (auto &bullet : this->player->bullets) {
        bullet.update();
    }
}

// ====================================
// UI and Feedback Methods Section
// ====================================
void ShipBattle::healthBar(int currHealth, int maxHealth) {
    indicatorFont.drawString("HEALTH", 10, 30);
    ofNoFill();
    ofDrawRectangle(10, 40, maxHealth *2, 20);
    ofFill();
    ofSetColor(ofColor::green);
    ofDrawRectangle(10, 40, currHealth *2, 20);
    ofSetColor(ofColor::white);
}

void ShipBattle::killSpreeTimer(int currTimer, int maxTimer) {
    indicatorFont.drawString("KILL SPREE", 10, 80);
    ofNoFill();
    ofDrawRectangle(10, 90, maxTimer, 10);
    ofFill();
    ofSetColor(ofColor::red);
    ofDrawRectangle(10, 90, currTimer, 10);
    ofSetColor(ofColor::white);
}

void ShipBattle::drawShieldBar(float currentShield, float maxShield) {
    float barWidth = 200; 
    float barHeight = 20; 
    float posX = 10; 
    float posY = 140; 

    // Draw "FORCE SHIELD" label
    ofSetColor(255); // White color for text
    ofDrawBitmapString("FORCE SHIELD", posX, posY - 10); // Positioning text above the bar

    // Draw the border of the shield bar
    ofSetColor(100, 100, 100); // Gray color for the border
    ofNoFill(); // Do not fill the rectangle, just draw the border
    ofDrawRectangle(posX, posY, barWidth, barHeight);
    ofFill(); // Re-enable filling for subsequent drawings

    // Calculate the width of the current shield level
    float shieldWidth = (currentShield / maxShield) * barWidth;

    // Draw the current shield level
    ofSetColor(0, 0, 255); // Blue for the shield level
    ofDrawRectangle(posX + 1, posY + 1, shieldWidth - 2, barHeight - 2);

    // Reset color for other drawings
    ofSetColor(255, 255, 255);
}

// ====================================
// Game Mechanics Methods Section
// ====================================

double ShipBattle::killSpreeMode() {
    // Logic for kill spree mode bonus
    return this->killspreeTimer > 0 ? 1.5 : 1.0;
}

double ShipBattle::scoreMultiplier() {
    // Logic for score multiplier based on current score
    if (playerScore >= 350) return 3.5;
    else if (playerScore >= 200) return 2.5;
    else if (playerScore >= 100) return 1.5;
    else return 1.0; // Default multiplier
}

void ShipBattle::reset(){
    setFinished(false);
    EnemyManager::staticBossDead = false;
    setNextState("");
}


                                        
