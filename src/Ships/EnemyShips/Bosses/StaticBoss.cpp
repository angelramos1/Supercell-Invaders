#include "StaticBoss.h"

StaticBoss::StaticBoss(int xpos, int ypos, string name) : Boss(xpos,ypos,0.5,750, name) {
 
    pos.x = xpos;
    pos.y = ypos;


  
    enemyShipSprite.load("ShipModels/StaticBoss.png");
    
    enemyHitBox = new HitBox(-enemyShipSprite.getWidth() / 2 ,-enemyShipSprite.getHeight() / 2 , enemyShipSprite.getWidth(), enemyShipSprite.getHeight());
    
      shootingPoint = ofPoint(-enemyShipSprite.getWidth() / 2, -enemyShipSprite.getHeight() / 2);

    
    
 





}
    
void StaticBoss::update(const ofPoint& playerPos) {

    // Shoot bullets in a semi-circular motion
    enemyHitBox->box.setPosition(pos.x - enemyShipSprite.getWidth() / 2, pos.y - enemyShipSprite.getHeight() / 2);
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

void StaticBoss::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    // ofRotateDeg(shipOrientation);
     enemyShipSprite.draw(-enemyShipSprite.getWidth() / 2, -enemyShipSprite.getHeight() / 2);
    ofPopMatrix();
    
    // Uncomment this if you want to see the hitbox for the enemy
    if(showHitboxes){
        enemyHitBox->box.setPosition(pos.x - enemyShipSprite.getWidth() / 2, pos.y - enemyShipSprite.getHeight() / 2);
        enemyHitBox->draw();

    }
    
    showBossHealth();
}


void StaticBoss::shoot() {
    const int numBullets = 36; // Number of bullets for a complete spiral
    const float angleStep = 360.0 / numBullets; // Angle step for each bullet
    const float radiusStep = 10.0; // Step to increase the radius of the spiral

    // Calculate the center of the hitbox
    float centerX = enemyHitBox->box.getPosition().x + enemyHitBox->box.getWidth() / 2;
    float centerY = enemyHitBox->box.getPosition().y + enemyHitBox->box.getHeight() / 2;

    for (int i = 0; i < numBullets; ++i) {
        // Calculate the angle for each bullet, incorporating the shootAngleOffset
        float angle = i * angleStep + shootAngleOffset;

        // Calculate the radius of each bullet's position along the line
        float radius = i * radiusStep;

        // Calculate the x and y coordinates of the shooting point based on angle, radius, and center
        float posX = centerX + radius * cos(ofDegToRad(angle));
        float posY = centerY + radius * sin(ofDegToRad(angle));

        // Create and initialize the bullet at the calculated position
        Projectiles bullet(ofPoint(posX, posY), angle);
        bullet.setSpeed(3);
        bullet.setColors(ofColor::red, ofColor::orange); // Set desired colors
        enemyBullets.push_back(bullet);
    }

    // Increment the shootAngleOffset for the next call to shoot() to continue the spiral
    shootAngleOffset += 10.0; // Adjust this value for the desired spiral rotation speed

    // Optional: Reset shootAngleOffset to keep it within 0-360 degrees to avoid overflow
    if (shootAngleOffset >= 360.0) {
        shootAngleOffset -= 360.0;
    }

    SoundManager::playSong("bulletSound", false);
}