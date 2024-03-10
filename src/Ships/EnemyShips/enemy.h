#pragma once

#include "ofMain.h"
#include "Projectile.h"
#include <vector>
#include "HitBox.h"


class EnemyShip {
    
    protected:
        ofPoint pos = ofPoint(0, 0);
        float speed = 5.0000;
        int health;
        float damping;
        ofVec2f movement;
        int shipOrientation;
        float rotationSpeed;
        int shotTimer;

        int score; 
        bool amIBoss;

        HitBox* enemyHitBox;
        vector<Projectiles> enemyBullets;
        ofImage enemyShipSprite;

        bool dead;

    public:
        //  For debugging purposes. I added a boolean to toggle the hitboxes for all enemies
        bool showHitboxes = false;

        //Main Constructor for the EnemyShip class.
        EnemyShip(int xpos, int ypos, float _speed, int health, int score) {
            pos.x = xpos;
            pos.y = ypos;
            speed = _speed;
            this->health = health;
            this->score = score;
            damping = 0.95;
            shipOrientation = 0;
            rotationSpeed = 1.0;
            shotTimer = 1; //Starts at 1 instead of 0 to avoid the ship shooting as soon as the ship spawns
            this->dead = false;
        }

        // Pure virtual method to be implemented by the individual enemy classes
        virtual void update(const ofPoint& playerPos) = 0;
        virtual void draw() = 0;
        virtual void shoot() = 0;


        // Getters
        bool isBoss() { return amIBoss; }
        ofPoint& getPos() { return pos; }
        HitBox* getHitBox() { return enemyHitBox; }
        vector<Projectiles>& getBullets() { return enemyBullets; }
        int getPoints() { return score; }

        //Other methods:
        virtual void takeDamage(int dmg) {
            if(health - dmg <= 0) {
                health = 0;
                dead = true;
                return;
            }
            health -= dmg;
        }

        
        bool isDead() { return dead; }

        void removeMarkedBullets(){
            enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(),
                                [](const Projectiles& p) { return p.markedForDeletion; }),
                enemyBullets.end());
        }
    




    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~EnemyShip() {}

};



