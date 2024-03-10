#pragma once 
#include "enemy.h"


/*
    Note from author: Please do not copy this code. I am not a fan of it.
    

*/

class Boss : public EnemyShip {
    
    protected:
        int BossHealth;
        string bossName;
        ofTrueTypeFont font;
        bool moveLeft;
        bool moveRight;


    public:
        Boss(int xpos, int ypos, double speed, int health, string name) : EnemyShip(xpos, ypos, speed, health, 10000) {
            bossName = name;
            BossHealth = health;
            amIBoss = true;
            font.load("Fonts/Orbitron.ttf", 20);
        }


        virtual void update(const ofPoint& playerPos) = 0;
        virtual void draw() = 0;
        virtual void shoot() = 0;
 
        string getName() { return this->bossName; }

 
    void showBossHealth() {
        // Draw the boss name above the health bar
        font.drawString(getName(), ofGetWidth() / 4, ofGetHeight() * 3/4 - 20);

        // Outline for health bar
        ofNoFill();
        ofDrawRectangle(ofGetWidth() / 4, ofGetHeight() * 3/4, ofGetWidth() / 2, 20); // Health bar background

        // Calculate the current health as a percentage of total health
        float healthPercentage = static_cast<float>(health) / static_cast<float>(BossHealth);

        // Calculate the width of the health bar based on current health percentage
        int redBarWidth = static_cast<int>(ofGetWidth() / 2 * healthPercentage);

        // Draw the health bar
        ofFill();
        ofSetColor(ofColor::red);
        ofDrawRectangle(ofGetWidth() / 4, ofGetHeight() * 3/4, redBarWidth, 20); // Health bar filled based on current health
        ofSetColor(ofColor::white); // Reset color to white for subsequent drawing operations
    }

};