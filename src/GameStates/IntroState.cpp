#include "IntroState.h"
//Use maps instead of a vector
IntroState::IntroState(){
    titleImage.load("Menu_Images/introWallpaper.jpg");
    font.load("Fonts/Orbitron.ttf", 50);

    Button* PlayButton = new Button(ofGetWidth()/2 - 100, ofGetHeight()/2, 200, 50, "", "Play");
    Button* PlayButton2 = new Button(ofGetWidth()/2 - 100, ofGetHeight()/2 + 100, 200, 50, "", "Hey There!");

    buttons.push_back(PlayButton);
    buttons.push_back(PlayButton2);
}

void IntroState::update() {
    if(buttons[0]->wasPressed()){           // This is the "Play" button
        SoundManager::stopSong("intro");
        this->setNextState("BattleState");
        this->setFinished(true);
    }

   for(Button* button : buttons) {
        button->update();
    }

}


void IntroState::draw(){
    ofSetBackgroundColor(ofColor::black);
    titleImage.draw((ofGetWidth() - titleImage.getWidth())/2, (ofGetHeight() - titleImage.getHeight())/2);
    font.drawString("Supercell Invaders", ofGetWidth()/4 - 50, ofGetHeight()/4 + 100);

    //Draws All of the Buttons 
        for(Button* button : buttons){
            button->draw();
        }


}


void IntroState::keyPressed(int key){

}

void IntroState::mousePressed(int x, int y, int button){
    for (Button* button : buttons){
        button->setPressed(x, y);
    }
}




void IntroState::keyReleased(int key){
    
}

void IntroState::reset(){
    setFinished(false);
    setNextState("");
}

