#include "SoundManager.h"

// Definition of the static member variable
std::unordered_map<std::string, ofSoundPlayer> SoundManager::sounds;


void SoundManager::loadSong(const std::string& songName, std::string songPath) {
    ofSoundPlayer sound;

    if(sound.load(songPath)) {
        sounds[songName] = sound;
    }
    else{
        ofLogError("SoundManager", "Could not load song: " + songPath);
    }
}

void SoundManager::playSong(const std::string &name, bool loop) {
    auto it = sounds.find(name);
        if (it != sounds.end()) {
            it->second.setLoop(loop);
            it->second.play();
        } 
        else {
            ofLogError("SoundManager") << "Sound not found: " << name;
        }
}

void SoundManager::stopSong(const std::string &name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.stop();
    }
}

void SoundManager::setVolume(const std::string &name, double volume) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.setVolume(volume);
    }
}