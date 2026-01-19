#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <limits>

#include "Util.h"

// Give an alias to the string vector type
using string_list = std::vector<std::string>;
using buffered_input = std::numeric_limits<std::streamsize>;

// An enumeration for returning status codes during program runtime
enum ProgramStatus{ FILE_ERR = -1, SUCCESS };

// Definition of a math drill game object
class MathDrill{
	private:
	// Attributes
	int questions; // Number of game questions entered.
	
	char difficulty; // Difficulty of the game selected.
	int min_questions; // The lowest number of questions to select.
	int max_questions; // The highest number of questions to select.
	int lowest; // The lowest value for the operands to reach.
	int highest; // The highest value for the operands to reach.

	string_list prompts; // A list of prompts to ask the user for an answer.
	string_list rightAnsResponses; // A list of complimentary responses for when the user enters a correct answer.
	string_list tryAgainResponses; // A list of consturctive critique responses for when the user enters an incorrect answer.

	int prompts_len; // The length of the prompt list.
	int correct_ans_responses_len; // The length of the complimentary responses list.
	int try_again_responses_len; // The length of the consturctive critique responses list.

	// Constant character array of math operations for random selection during gameplay.
	const char	OPERATIONS[4]		= {'/', '*', '+', '-'};
	// The constant size of the operations array.
	const int	OP_SIZE			= sizeof(OPERATIONS) / sizeof(OPERATIONS[0]);

	// Character constants for difficulty validation
	static const char	CHILD_FRIENDLY	= 'G';
	static const char	EASY				= 'H';
	static const char	MEDIUM			= 'J';
	static const char	HARD				= 'K';
	static const char	EXPERT			= 'L';

	// Useful methods for the game to run
	void loadDrillPrompts(std::string promptsFile);
	void loadRightAnsResponses(std::string responsesFile);
	void loadTryAgainResponses(std::string responsesFile);
	void selectDifficulty();
	void setNumQuestions();
	void outOfBoundsResponse();
	void drillResultsAndFeedback(int points);

	public:
	MathDrill(); // The game object's constructor for initialization

	// Character constants for main menu input validation
	static const char PLAY	= 'K';
	static const char LEAVE	= 'L';
	
	// Methods to display to the user at the beginning of gameplay
	static char mainMenu();
	static void leaveResponse();
	static void incorrectOptionResponse();

	// Method to start the math drill game
	void play();
};