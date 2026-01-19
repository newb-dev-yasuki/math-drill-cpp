#include "lib/MathDrill.h"

// Math drill game's entry point.
int main(){
    bool running = true; // The drill's operation state.
    // Run the main menu segment at least once
    do{
        switch(MathDrill::mainMenu()){ // Using the recorded user's input for the switch statement
            case MathDrill::PLAY: { // The user decided to participate
                MathDrill newDrill; // Math drill game object.
                newDrill.play(); // Start the game
                break;
            }

            case MathDrill::LEAVE: { // User decided to leave
                MathDrill::leaveResponse(); // Display a response to the user's choice to leave
                running = !running; // Stop the game from running
                break;
            }

            default: // User made an incorrect choice
                MathDrill::incorrectOptionResponse(); // Prompt to the user that they've made an incorrect option
        }
    } while(running); // Loop the segment as long as the user hasn't left the game

    return SUCCESS; // No issues were encontered during the game's operation.
}
