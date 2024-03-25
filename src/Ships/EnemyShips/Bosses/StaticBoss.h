#pragma once
#include "Boss.h"


class StaticBoss : public Boss {
    private:
        float shootAngleOffset = 0.0; // Keep track of the shooting angle offset for the spiral pattern
        ofPoint shootingPoint;
        float radius;
        
        
    public:
        StaticBoss(int xpos,int ypos, string name);
        void update(const ofPoint& playerPos) override;
        void draw() override;
        void shoot() override;
        
};