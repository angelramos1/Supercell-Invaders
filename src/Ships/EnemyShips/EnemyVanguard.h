#pragma once
#include "enemy.h"

class EnemyVanguard : public EnemyShip {

    public:
        EnemyVanguard(int xpos, int ypos);
        void update(const ofPoint& playerPos) override;
        void draw() override;
        void shoot() override;
};
