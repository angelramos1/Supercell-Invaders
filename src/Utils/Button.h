#pragma once
#include "ofMain.h"
#include "SoundManager.h"

/*
    Note from author:
        This is the Button class. It is used to create buttons for the game. 
        after creating the buttons, use them in the states as you see fit.
*/

class Button {

    private:
        int xPos = 10;
        int yPos = 0;
        int width;
        int height;
        string imagePath;       // In case you want an image for the button.
        string textToDisplay;
        ofTrueTypeFont font; 
        bool pressed;


    public:
        Button(int xPos, int yPos, int width, int height, string imagePath, string text);
        ~Button();

        void update();
        void draw();

        void setPressed(int mouseX, int mouseY);    
        bool wasPressed();

};

