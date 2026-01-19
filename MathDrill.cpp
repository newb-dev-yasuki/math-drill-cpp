#include "lib/MathDrill.h"

// Default constructor to setup the drill game.
MathDrill::MathDrill(){
    srand(time(NULL)); // Seed the random number generator
    // Load the prompts and responses to display during the drill
    loadDrillPrompts("data/question_prompts.txt");
    loadRightAnsResponses("data/correct_responses.txt");
    loadTryAgainResponses("data/try_again_responses.txt");
}

// Method to return the user's choice upon displaying the main 
// menu.
char MathDrill::mainMenu(){
    system("cls"); // Clear everything from the console

    char choice; // The user's choice to participate in the drill.
    // Print out the main menu
    std::cout << "MATH DRILL!" << '\n'
              << '\n';
    std::cout << "K: Play!" << '\n'
              << "L: Leave..." << '\n'
              << '\n';
    std::cout << "Your choice: "; // Prompt for the user's choice
    std::cin >> choice; // Read in the choice
    std::cout << '\n';
    std::cin.ignore(buffered_input::max(), '\n'); // Clear the input buffer until a new line character is found

    return toupper(choice); // Return an uppercase version of the choice
}

// Outputs a response for when the user decides to leave the game.
void MathDrill::leaveResponse(){
    std::cout << "You chose to quit... Come test your brain again sometime soon!" << '\n';
    system("pause"); // Pause the program to not immediately quit after displaying the response
}

// Outputs a response for when the user chose a wrong option instead of selecting from the given
// options.
void MathDrill::incorrectOptionResponse(){
    std::cout << "Please select one of the displayed options above." << '\n';
    system("pause"); // Pause the program to not clear the console after displaying the response
}

// Outputs a response for when the user's input is beyond the specified bounds to allow the answer
void MathDrill::outOfBoundsResponse(){
    std::cerr << "Please enter an integer in the given range." << '\n';
    system("pause");
}

// Display the user's results after the drill and feedback to the results
void MathDrill::drillResultsAndFeedback(int points){
	// Calculate the integer percentage of correctly answered questions from the points
	int percentage = (points * 100) / questions;
	// Print out the results first: the points gained and the percentage
	std::cout << '\n'
             << "You got " << points << " out of " << questions
             << " questions correct "
             << "(" << percentage << "%)." << '\n'
			 << '\n';
	 
	 // Give feedback based on the range the percentage falls under
	 if(percentage > 90 && percentage <= 100)
            std::cout << "Outstanding work! You nailed it with exceptional accuracy. Keep it up!" << '\n';
	 else if(percentage > 80)
            std::cout << "Great job! You're performing at a high level—just a little more and you'll be perfect!" << '\n';
	 else if(percentage > 70)
            std::cout << "Well done! You’re making strong progress. Focus on improving a few areas to reach the next level!" << '\n';
	 else if(percentage > 60)
            std::cout << "Nice effort! You're doing well, and with a bit more practice, you can boost your score even further." << '\n';
	 else if(percentage > 50)
            std::cout << "Good attempt! You're on the right track. Review the tricky parts, and you'll improve quickly!" << '\n';
	 else if(percentage > 40)
            std::cout << "You're getting there! Take your time with the questions and keep practicing—you're closer than you think." << '\n';
	 else if(percentage > 30)
            std::cout << "Not bad, but there's room for improvement. Focus on understanding the concepts, and you'll see better results." << '\n';
	 else if(percentage > 20)
            std::cout << "This was a tough one, but don’t give up! Review the basics carefully, and you'll get the hang of it." << '\n';
	 else if(percentage > 10)
            std::cout << "It seems this was challenging for you, but that’s okay! Take it step by step and keep practicing." << '\n';
	 else
			std::cout << "Don’t worry about the score—this is a starting point. Focus on learning from your mistakes, and you’ll improve over time." << '\n';
		
	system("pause"); // Give the user a chance to read the feedback for their results
}

// Prompts the user for a valid difficulty level, then sets bounds for the number of questions
// to be answered and the range of the values of the operands used in the drill.
void MathDrill::selectDifficulty(){
    difficulty = '\0'; // Initializing the difficulty level to be chosen by the user.
    while(!Util::withinBounds(difficulty, MathDrill::CHILD_FRIENDLY, MathDrill::EXPERT)){ // Run until a valid option is chosen
        system("cls"); // Clear everything from the console
        // Prompt the user to enter a difficulty level
        std::cout << "Select difficulty:" << '\n'
                  << "G: Child-friendly (no negative answers required; no multiplication by zero)" << '\n'
                  << "H: Easy (no negative answers required)" << '\n'
                  << "J: Medium" << '\n'
                  << "K: Hard" << '\n'
                  << "L: Expert" << '\n'
                  << '\n';
        std::cout << "Your input: ";
        std::cin >> difficulty; // Read the chosen option
        std::cout << '\n';
        std::cin.ignore(buffered_input::max(), '\n'); // Clear the input buffer until a new line character is found

        difficulty = toupper(difficulty); // Capitalize the recorded characrer. No, I don't mean make money out of it...
        switch(difficulty){ // Using the recorded user's input for the switch statement
            // Set the ranges for the number of questions to answer, and the minimum and maximum numbers
            // for the operands corresponding to each difficulty level
            case MathDrill::CHILD_FRIENDLY:
                min_questions = 5; max_questions = 10;
                lowest = 0; highest = 10;
                break;

            case MathDrill::EASY:
                min_questions = 10; max_questions = 20;
                lowest = 0; highest = 15;
                break;
            
            case MathDrill::MEDIUM:
                min_questions = 20; max_questions = 50;
                lowest = -25; highest = 25;
                break;
            
            case MathDrill::HARD:
                min_questions = 50; max_questions = 75;
                lowest = -50; highest = 50;
                break;
            
            case MathDrill::EXPERT:
                min_questions = 50; max_questions = 100;
                lowest = -100; highest = 100;
                break;

            default: // User chose an invalid option
                // Invoke a method to prompt the user so
                MathDrill::incorrectOptionResponse();
        }
    }
}

// Prompts the user for the number of questions to answer based on the selected difficulty.
void MathDrill::setNumQuestions(){
    questions = 0; // Initialize the number of questions for the user to set in a specified range.
    while(!Util::withinBounds(questions, min_questions, max_questions)){
        system("cls"); // Clear everything from the console
        // Prompt the user for the number of questions to answer
        std::cout << "How many questions? Select between "
                  << min_questions << " and " << max_questions << ".\n"
                  << '\n';
        std::cout << "Your input: ";
        if(!(std::cin >> questions)){ // If an invalid input has been read
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(buffered_input::max(), '\n'); // Clear the input buffer until a new line character is found
            // Tell the user about the invalidity of their input
            std::cerr << "Non-integer character entered." << '\n';
            outOfBoundsResponse();
        } else{
            if(!Util::withinBounds(questions, min_questions, max_questions))
                outOfBoundsResponse(); // Prompt the user that their input is out of bounds
        }
    }
}

// Reads, from a given file, the prompts for the user to answer the given math problems, in memory
void MathDrill::loadDrillPrompts(std::string promptsFile){
    std::ifstream inputFile(promptsFile); // Open the file containing questions to prompt the user during gameplay
    if(inputFile.fail()){ // Should something occur while trying to access the file
        // Tell the user what went wrong
        std::cerr << "Error opening '" << promptsFile << ".' - It could be opened, moved, renamed, deleted "
            << "or corrupted. The program will stop running." << '\n';
        system("pause"); // Pause for the reader to read the error message
        exit(FILE_ERR); // Exit the drill game
    }

    std::string singlePrompt; // String variable to read the single line of prompt until a new line character
    while(std::getline(inputFile, singlePrompt, '\n')) // While there are still more lines to read
        prompts.push_back(singlePrompt); // Push the read and contained response into the container

    prompts_len = prompts.size(); // Hold on to the size of the prompts container until gameplay is complete
    inputFile.close(); // Close the connection to the file
}

// Reads, from a given file, the responses for when the user gives a correct answer, in memory
void MathDrill::loadRightAnsResponses(std::string responsesFile){
    std::ifstream inputFile(responsesFile); // Open the file containing responses for when the user gives a correct answer during gameplay
    if(inputFile.fail()){ // Should something occur while trying to access the file
        // Tell the user what went wrong
        std::cerr << "Error opening '" << responsesFile << ".' - It could be opened, moved, renamed, deleted "
                  << "or corrupted. The program will stop running." << '\n';
        system("pause"); // Pause for the reader to read the error message
        exit(FILE_ERR); // Exit the drill game
    }

    std::string singleResponse; // String variable to read the single line of response until a new line character
    while(std::getline(inputFile, singleResponse, '\n')) // While there are still more lines to read
        rightAnsResponses.push_back(singleResponse); // Push the read and contained response into the container

    correct_ans_responses_len = rightAnsResponses.size(); // Hold on to the size of the responses container until gameplay is complete
    inputFile.close(); // Close the connection to the file
}

// Reads, from a given file, the responses for when the user gives an incorrect answer, in memory
void MathDrill::loadTryAgainResponses(std::string responsesFile){
    std::ifstream inputFile(responsesFile); // Open the file containing responses for when the user gives an incorrect answer during gameplay
    if(inputFile.fail()){ // Should something occur while trying to access the file
        // Tell the user what went wrong
        std::cerr << "Error opening '" << responsesFile << ".' - It could be opened, moved, renamed, deleted "
            << "or corrupted. The program will stop running." << '\n';
        system("pause"); // Pause for the reader to read the error message
        exit(FILE_ERR); // Exit the drill game
    }

    std::string singleResponse; // String variable to read the single line of response until a new line character
    while(std::getline(inputFile, singleResponse, '\n')) // While there are still more lines to read
        tryAgainResponses.push_back(singleResponse);  // Push the read and contained response into the container

    try_again_responses_len = tryAgainResponses.size(); // Hold on to the size of the responses container until gameplay is complete
    inputFile.close(); // Close the connection to the file
}

// Runs the drill game upon request
void MathDrill::play(){
    //std::cout << "Started." << '\n';
    system("cls"); // Clear everything from the console

    selectDifficulty(); // Prompt the user until a valid difficulty is chosen
    setNumQuestions(); // Prompt for the number of questions to be answered based on selected difficulty

	int points = 0; // The user's number of correctly answered questions, which will be displayed at the end of the drill
    for(int q = 1; q <= questions; q++){
		system("cls"); // Clear everything from the console
		
		// Pick a random operation sign, generate random values from either side of the operation sign,
		// and pick a random prompt for the user to answer questions during gameplay
		char		randOp		= OPERATIONS[Util::randInt(0, OP_SIZE - 1)];
        int			lOp			= Util::randInt(lowest, highest);
		int			rOp			= Util::randInt(lowest, highest);
		std::string	randPrompt	= prompts[Util::randInt(0, prompts_len - 1)];

		int	correctAnswer;	// Variable to hold on to the correct answer based on the selected
							// operation sign and generated operands
		switch(randOp){	// From the randomly picked operation sign, apply the conditions due to chosen difficulty and
						// calculate the correct answer
            case '/': { // A division sign is picked
				while(rOp == 0 || lOp % rOp != 0) // Avoid division by zero and indivisibility by the denominator
					rOp = Util::randInt(lowest, highest); // Generate another denominator value until a suitable value is found
				
				correctAnswer = lOp / rOp;
				break;
			}
			
			case '*': { // A multiplication sign is picked
				if(difficulty == MathDrill::CHILD_FRIENDLY){ // Should it be a child-friendly game
					if(lOp == 0) // If the left operand is zero, generate a non-zero value
						lOp = Util::randInt(1, highest);
					
					if(rOp == 0) // If the right operand is zero, generate a non-zero value
						rOp = Util::randInt(1, highest);
				}
				correctAnswer = lOp * rOp;
				break;
			}
					
			case '+': // An addition sign is picked
				correctAnswer = lOp + rOp;
				break;
				
			case '-': { // A subtraction sign is picked
				if(Util::withinBounds(difficulty, MathDrill::CHILD_FRIENDLY, MathDrill::EASY)){ // Should the difficulty be at most easy
					while(lOp - rOp < 0){ // If the difference between the operands is negative
						// Re-assign random numbers on both operands
						lOp = Util::randInt(lowest, highest);
						rOp = Util::randInt(lowest, highest);
					}
				}
				correctAnswer = lOp - rOp;
				break;
			}
		}
		
		int userAnswer = 0; // Variable to evaluate the user's answer to the current question
		// Display the question to the user
		std::cout << q << ". " << randPrompt << ": "
				 << lOp << " "
				 << randOp << " "
				 << rOp << "?" << '\n';
		while(true) { // Run a loop until a correct answer is found
			std::cout << "Enter your answer: "; // Prompt for user input
			if(!(std::cin >> userAnswer)){ // Should an invalid input be made
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(buffered_input::max(), '\n'); // Clear the input buffer until a new line character is found
				// Tell the user about the invalidity of their input
				std::cerr << "Non-numeric input entered - please enter a number to answer the question." << '\n' ;
			} else { // If a valid input is made otherwise
				std::cout << '\n';
				if(userAnswer == correctAnswer){ // User entered the correct answer
					// Provide random complimentary feedback to the answer
					std::cout << rightAnsResponses[Util::randInt(0, correct_ans_responses_len - 1)] << '\n';
                    points++;
					system("pause"); // Give the user a chance to read the response
					break;
				} else {
					// Provide a random critique to the answer
					std::cout << tryAgainResponses[Util::randInt(0, try_again_responses_len - 1)] << '\n';
				}
			}
		}
    }
	
	// The game is done - display the drill results
	drillResultsAndFeedback(points);
}
