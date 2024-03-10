#include "GameOverState.h"
//Use maps instead of a vector
GameOverState::GameOverState(){
    titleImage.load("Menu_Images/introWallpaper.jpg");
    titleFont.load("Fonts/Orbitron.ttf", 50);
    textFont.load("Fonts/Orbitron.ttf", 30);

    Button* PlayButton = new Button(ofGetWidth()/2 - 100, ofGetHeight() * 3/4, 200, 50, "", "Play Again");

    buttons.push_back(PlayButton);
 
}

void GameOverState::update() {
    if(buttons[0]->wasPressed()){           // This is the "Play" button
        SoundManager::stopSong("intro");
        this->setNextState("IntroState");
        this->setFinished(true);
    }

    //Logic to display the final scores
    pullHighScore(); // Ensure we have the latest high score
    pullCurrentScore(); // Read the current score
    if (currScore > HighScore) {
        HighScore = currScore;
        highScoreAchieved = true;
        writeHighScore();
    }
    
   for(Button* button : buttons) {
        button->update();
    }

}


void GameOverState::draw(){
    ofSetBackgroundColor(ofColor::black);
    titleImage.draw((ofGetWidth() - titleImage.getWidth())/2, (ofGetHeight() - titleImage.getHeight())/2);
    
    // Display the scores
    titleFont.drawString("GAME OVER", ofGetWidth()/4 + 75, 100);

    textFont.drawString("High Score: ", ofGetWidth()/4 - 200, ofGetHeight()/4 + 120);
    textFont.drawString(to_string(HighScore), ofGetWidth() * 3/4, ofGetHeight()/4 + 120);

    textFont.drawString("Current Score: ", ofGetWidth()/4 - 200, ofGetHeight()/4 + 160);
    textFont.drawString(to_string(currScore), ofGetWidth() * 3/4, ofGetHeight()/4 + 160);

    // New high score message
    if (highScoreAchieved) {
        textFont.drawString("New High Score!", ofGetWidth()/2 - 175, 160);
    }

    //Draws All of the Buttons 
    for(Button* button : buttons){
        button->draw();
    }



}


void GameOverState::keyPressed(int key){

}

void GameOverState::mousePressed(int x, int y, int button){
    for (Button* button : buttons){
        button->setPressed(x, y);
    }
}




void GameOverState::keyReleased(int key){
    
}

void GameOverState::reset(){
    highScoreAchieved = false;
    setFinished(false);
    setNextState("");
}

