#include "ofApp.h"


//--------------------------------------------------------------

void ofApp::setup(){
    ofSetFrameRate(60); // Set frame rate for a smoother experience
    // ofSetEscapeQuitsApp(false);// Set 'ESC' key to not quit the app

    /*
        Sound Manager Setup:
        To add songs to the game, add them to the bin/data/Sounds folder and 
        add the name of the song and the path to it using the SoundManager::loadSong function as shown below.
    */

    SoundManager::loadSong("intro", "Sounds/Great_Void_Sea_Battle.mp3");
    SoundManager::loadSong("battle", "Sounds/Clashing_Waves.mp3");
    SoundManager::loadSong("shipDestroyed", "Sounds/shipExplosion.wav");
    SoundManager::loadSong("ORT Xibalba", "Sounds/ORT_Xibalba.mp3");
    SoundManager::loadSong("Galactica Supercell ORT", "Sounds/ORT_UFO.mp3");
    SoundManager::loadSong("button", "Sounds/buttonInteract.mp3");
    SoundManager::loadSong("bulletSound", "Sounds/shootingSound.mp3");
    SoundManager::loadSong("Beam", "Sounds/Laser_Beam.mp3");

//States
    intro = new IntroState();
    battle = new ShipBattle();
    gameOver = new GameOverState();
    
    battle->displayBossWarning = false; // Setting the boss warning to false at the start to avoid a visual bug.

    currentState = intro; // Setting the starting state
    SoundManager::playSong("intro", false);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
}

//--------------------------------------------------------------

void ofApp::update(){
    currentState->update();

    // State switching
    if(currentState->hasFinished()){
        if(currentState->getNextState() == "IntroState") {
            SoundManager::playSong("intro", true);
            currentState = intro;    
        }
        
        else if(currentState->getNextState() == "BattleState"){
            SoundManager::playSong("battle", true);
            currentState = battle;
        }

        else if(currentState->getNextState() == "GameOverState") {
            SoundManager::playSong("intro", true);
            currentState = gameOver;
        }
        currentState->reset();
    }

}

//--------------------------------------------------------------

void ofApp::draw(){
    currentState->draw();
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    currentState->keyPressed(key);
}

//--------------------------------------------------------------

void ofApp::keyReleased(int key){
    currentState->keyReleased(key);
}

//--------------------------------------------------------------

void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button){
    currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------

void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------

void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------

void ofApp::mouseExited(int x, int y){

}


//--------------------------------------------------------------

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------

void ofApp::gotMessage(ofMessage msg) {

}


//-------------------- Section for added utility methods -------

