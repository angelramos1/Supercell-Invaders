#pragma once 
#include "ofMain.h"
#include "Button.h"
#include "SoundManager.h"

class State{ 

    protected:
        string nextState;
        bool finished = false;

    public:
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void reset() = 0;
        virtual void keyPressed(int key) = 0;
		virtual void keyReleased(int key) = 0;
        virtual void mousePressed(int mouseX, int mouseY, int button) = 0;

        bool hasFinished() { return finished; }
        void setFinished(bool finished) { this-> finished = finished; }
        void setNextState(string nextState) { this->nextState = nextState; }        
        string getNextState(){ return this->nextState; }

};  