#pragma once
#include "Projectile.h"

class HitBox {

    public:
        ofRectangle box; //will serve as the skeleton for the hitbox 

        HitBox(){} //Useless constructor, just use the other constructors
        
        HitBox(ofPoint pos, float width, float height){
            this->box = ofRectangle(pos, width, height);
        }

        HitBox (float px, float py, float width, float height){
            this->box = ofRectangle(px, py, width, height);
        }

    //Method to draw the hitboxes in case you may want to test with them
        void draw(){
            ofNoFill();
            ofDrawRectangle(box);
            ofFill();
        }

    /*
        Method to check if a collision occurs with a projectile.
        Phase 2; perhaps we should have another one that checks
        if we're colliding with another hitbox aka another enemy/boss no?
     */ 
        bool isHit(Projectiles& bullet){
            return box.inside(bullet.position.x, bullet.position.y);          
        }
};