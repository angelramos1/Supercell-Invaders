#include "State.h"

class IntroState : public State{
    private:
        ofImage titleImage;
        vector<Button*> buttons;
        ofTrueTypeFont font;
        
    public:
        IntroState();
        void update();
        void draw();
        void reset();
        void keyPressed(int key);
        void keyReleased(int key);
        void mousePressed(int x, int y, int button);

        ~IntroState(){ }

};