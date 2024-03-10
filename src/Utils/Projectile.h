#pragma once 
#include "ofMain.h"
#include "SoundManager.h"

/*
    Note from author:
        This is the projectile class. It basically makes the projectile. If you wonder why it doesn't use the hitbox class, well...
        it's because i didn't think it through well enough. But fear not, because the hitbox class uses the projectile class when checking collisions.
*/

class Projectiles {
    
    private:
        ofColor color1, color2;     // The primary and secondary colors of the projectile
        float width;                // The width of the projectile
        float height;               // The height of the projectile
        int speed;                  // The speed at which the projectile moves
        float angle;                // The angle of the projectile's trajectory
        int damage;                 // The damage the projectile can inflict
        ofImage img;                // The image of the new projectile
        
    public:
        ofPoint position;           // The current position of the projectile
        bool markedForDeletion;     // Flag to mark the projectile for deletion
        
        
        // Constructors
        Projectiles(ofPoint p, float angle);            // Constructor to initialize a projectile with position and angle
        Projectiles(ofPoint p, float angle, int dmg);   // Overloaded constructor to also set damage

        // Getter and Setter Methods
        int getDamage() { return damage; }              // Returns the damage of the projectile
        void setSpeed(int s) { speed = s; }             // Sets the speed of the projectile
        void setColors(ofColor c1, ofColor c2);         // Sets the colors of the projectile

        // Action Methods
        void update();                                  // Updates the projectile's position based on its speed and angle
        void draw();                                    // Draws the projectile on the screen
        void markForDeletion();                         // Marks the projectile for deletion
        bool bulletIsOutOfBounds();                     // Checks if the projectile is out of the screen bounds
};