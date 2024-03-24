#pragma once
#include "enemy.h"

class NewEnemy : public EnemyShip {

    public:
        NewEnemy(int xpos, int ypos);
        void update(const ofPoint& playerPos) override;
        void draw() override;
        void shoot() override;
};
