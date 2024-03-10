#include "State.h"

class GameOverState : public State{
    private:
        ofImage titleImage;
        vector<Button*> buttons;
        ofTrueTypeFont titleFont;
        ofTrueTypeFont textFont;
        
    public:
        GameOverState();
        void update();
        void draw();
        void reset();
        void keyPressed(int key);
        void keyReleased(int key);
        void mousePressed(int x, int y, int button);

        ~GameOverState(){ }

        //Added logic for the scoring system
        int currScore = 0;
        int HighScore = 0;
        bool highScoreAchieved = false;



        //Added logic for highscore

        void pullHighScore(){
            ifstream highScoreFile("highscore.txt");
            if (highScoreFile.is_open()) {
                highScoreFile >> HighScore;
                highScoreFile.close();
            } 
            else {
                HighScore = 0; // Default to 0 if file doesn't exist
            }
        }

        void writeHighScore() {
            ofstream highScoreFile("highscore.txt");
            if (highScoreFile.is_open()) {
                highScoreFile << HighScore;
                highScoreFile.close();
            }
        }

        void pullCurrentScore() {
            ifstream scoreFile("currentScore.txt");
            if (scoreFile.is_open()) {
                scoreFile >> currScore;
                scoreFile.close();
            }
            //We will delete the file after reading to avoid stale data. This is 
            remove("currentScore.txt");
        }



};