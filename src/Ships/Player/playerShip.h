#pragma once

#include "ofMain.h"
#include "Projectile.h"
#include "HitBox.h"

using namespace std;

class Player{ 

    private:
        ofImage shipSprite;                 // Sprite for the ship   

        int score;                          // Score of the player

    // === Attributes related to movement ===
        float maxSpeed = 5;         // Maximum speed of the player
        float speed;                // Current speed of the player
        ofVec2f velocity;           
        float accelerationAmount;   // Amount of acceleration
        bool isMoving = false;      // Flag to track if a movement key is being held
        float damping = 0.95;       // Damping factor for slowing down

       // === Attributes related to shooting ===
        float lastShotTime;                // Last time a shot was fired
        float shotCooldown;                // Cooldown between shots

    // === Attributes related to rotation ===
        float rotationSpeed = 2.5;         // Speed of rotation


    public: 

       // === Public attributes ===
        int health;                         // Needed in public for ease of use and direct access
        int shipOrientation;                // Orientation of the ship
        unordered_map<int, bool> keyMap;    // A Map is used to handle the keys pressed
        vector<Projectiles> bullets;        // List of bullets
        ofPoint pos;                        // Position of the player
        HitBox hitBox;                      // Hitbox for the player
        bool showHitbox = false;

    // === Constructors ===
        Player();                                      // Default Constructor
        Player(int Xposition, int Yposition);         // Parametrized Constructor for the playerShip
    
        int getScore(); 
        void setScore(int score); 
  
    // Main method to draw the playerShip
        void draw(); 
        ofImage getSprite(){return shipSprite;}
    /*
        Main method to update the playerShip. It handles the movement indirectly by calling processPressedKeys(), and updates the position.
        This is the brain of the class.
    */
        void update();

    /*
        Method to generate the projectiles. It creates a projectile object 
        and places it into the bullets vector.  
    */
        void shoot(); 

    /*
        Useful method in case you want to modify the shot cooldown.
    */
        void setShotCooldown(float shotCooldown);

    /*
        method used for bullet removal.
    */
        void removeMarkedBullets();
 
    // === Input handling ===
        void addPressedKey(int key);         // Function to add a pressed key to the keyMap
        void processPressedKeys();          //Function that will process if the value of the keys inside the Map are being pressed 
        void removePressedKey(int key);      // Function to remove a pressed key from the keyMap 
        void movement(char keyPressed);     // Function that will handle the movement for the ship

};