#include "NewEnemy.h"


NewEnemy::NewEnemy(int xpos, int ypos) : EnemyShip(xpos, ypos, 6, 10, 100) {
    amIBoss = false;
    enemyShipSprite.load("CompressedImages/newEnemy-min.png"); 
    enemyShipSprite.rotate90(2);
    enemyHitBox = new HitBox(pos, enemyShipSprite.getWidth() * 0.1, enemyShipSprite.getHeight() * 0.1);
    speed = 0.820;
    health = 11;
}

void NewEnemy::update(const ofPoint& playerPos) {
    // Calculate the angle to the player
        ofVec2f toPlayer = playerPos - pos;
        float angleToPlayer = ofRadToDeg(-atan2(toPlayer.x, toPlayer.y));

    // Update ship's orientation
        shipOrientation = angleToPlayer;

    // Move towards the player
        pos += toPlayer.getNormalized() * speed;
        enemyHitBox->box.setPosition(pos.x - 15, pos.y - 10);

    this->shotTimer++;
    // Check if the ship should shoot
        if (shotTimer % 50 == 0) {
            shoot();
            shotTimer = 0; //resets the timer
        }
}

void NewEnemy::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotateDeg(shipOrientation);
    enemyShipSprite.draw(-32, -32, 60, 60);
    ofPopMatrix();
    
    if(showHitboxes){
        enemyHitBox->draw();
    }
}

void NewEnemy::shoot() {
    // Create a new projectile and add it to the list of bullets
    Projectiles p = Projectiles(pos, shipOrientation + 90);
    Projectiles p1 = Projectiles(pos, shipOrientation + 93);
    p.setColors(ofColor::yellow, ofColor::purple);
    p1.setColors(ofColor::blue, ofColor::green);
    enemyBullets.push_back(p);
    enemyBullets.push_back(p1);
    SoundManager::playSong("bulletSound", false);
}
