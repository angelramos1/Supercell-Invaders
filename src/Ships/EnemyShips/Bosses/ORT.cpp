#include "ORT.h"

ORT::ORT(int xpos, int ypos, string name) : Boss(xpos, ypos,0.5, 750, name) {
    enemyShipSprite.load("CompressedImages/ORT_Xibalba-min.png");
    enemyHitBox = new HitBox(pos.x, pos.y - 30, enemyShipSprite.getWidth() * 0.05, enemyShipSprite.getHeight() * 0.075);
    
    shootingPoint = ofPoint(pos.x + enemyHitBox->box.getWidth(), pos.y + enemyHitBox->box.getHeight() / 2);
    
    
    switchPosIndex = 0;
    switchPosTimer = 0;

    possiblePositions = {
        ofPoint(0, 0),
        ofPoint(ofGetWidth() * 1/4, ofGetHeight() * 1/4),
        ofPoint(ofGetWidth() * 1/4, ofGetHeight() * 3/4),
        ofPoint(ofGetWidth() * 3/4, ofGetHeight() * 1/4),
        ofPoint(ofGetWidth() * 3/4, ofGetHeight() * 3/4)
    };



}
    
void ORT::update(const ofPoint& playerPos) {
    // pos.x += speed;
    enemyHitBox->box.setPosition(pos.x + 10, pos.y - 30);   // Update the hitbox to follow the boss
    shootingPoint = ofPoint(pos.x + enemyHitBox->box.getWidth(), pos.y + enemyHitBox->box.getHeight() / 2);   // Update the shooting point


    // Update the switch position
    switchPosTimer++;
    if (switchPosTimer % 100 == 0) {
        switchPosIndex++;
        pos = possiblePositions[switchPosIndex % possiblePositions.size()];
    }




    // Check if ORT is out of the screen, reset position if necessary
    // if (pos.x > ofGetWidth()) {
    //     pos.x = 0;
    // }

    // Shoot bullets in a semi-circular motion
    if (shotTimer % 50  == 0) { // Adjust the value for the frequency of shooting
        shoot();
    }

    if(enemyBullets.size() > 0) {
        // Update bullets
        for (Projectiles& bullet : enemyBullets) {
            bullet.update();
        }
    }

    // Increment shot timer
    shotTimer++;

}

void ORT::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    // ofRotateDeg(shipOrientation);
    enemyShipSprite.draw(-32, -32, 200, 200);
    ofPopMatrix();
    
    // Uncomment this if you want to see the hitbox for the enemy
    if(showHitboxes){
        enemyHitBox->draw();
    }
    
    showBossHealth();
}


void ORT::shoot() {
    const int numBullets = 36; // Increase the number of bullets for a smoother spiral
    const float angleStep = 360.0 / numBullets; // Ensure a full circle is covered

    for (int i = 0; i < numBullets; ++i) {
        // Calculate the angle for each bullet, incorporating the shootAngleOffset
        float angle = i * angleStep + shootAngleOffset;

        // Create and initialize the bullet at the boss's position with the given angle
        // Note: The angle is directly used in the Projectiles constructor
        Projectiles bullet(shootingPoint, angle);
        bullet.setSpeed(3);
        bullet.setColors(ofColor::red, ofColor::orange); // Set desired colors
        enemyBullets.push_back(bullet);
    }   

    // Increment the shootAngleOffset for the next call to shoot() to continue the spiral
    shootAngleOffset += 10.0; // Adjust this value for the desired spiral rotation speed

    // Optional: Reset shootAngleOffset to keep it within 0-360 degrees to avoid overflow
    if(shootAngleOffset >= 360.0) {
        shootAngleOffset -= 360.0;
    }

    SoundManager::playSong("bulletSound", false);
}