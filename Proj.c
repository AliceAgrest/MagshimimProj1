#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
enum difficultLevel {EASY = 1, MEDIUM, HARD, ULTRA_HARD};

void rules(void);
int creditCodeRnd(void);
enum difficultLevel selectOptions(void);
int difficultyTries(enum difficultLevel difficulty);
bool doesDigitExist (int credit,int creditCode);
int creditCodeRnd (void);
int duplictesNumberCount (int guessCode);
void correctNhalfGuess (int creditCode, int guessCode);
bool toContinue (void);

#define MAX_NUM 6
#define MIN_NUM 1
#define DIGIT_COUNT 4

int main(void) {
	/*srand(time(NULL));
	bool dontStop = true;
	while (dontStop){
		rules();
		int creditCode = creditCodeRnd();
		int tries = difficultyTries(selectOptions());
		int guessCode;
		int duplicateNumCount;

		for (int i = 1; i <= tries; i++){
			printf("You have %d tries\n", tries);
			puts("Enter a guess for a code: ");
			scanf("%d", &guessCode);

			duplicateNumCount = duplictesNumberCount(guessCode);
			tries -= duplicateNumCount;

			if (creditCode == guessCode){
				printf("You win!!! The credit code was %d\nCongratulations!\n", creditCode);
				break;
			}
			else{
				correctNhalfGuess(creditCode, guessCode);
				continue;
			}
		}
		if (creditCode == guessCode)
			printf("You win!!!\nThe credit code was %d\nCongratulations!\n", creditCode);
		else if (creditCode != guessCode)
			printf("You lost :(\nThe credit Code was %d\nMaybe next time\n", creditCode);
		
		dontStop = toContinue();
	}*/
	int creditCode = 1234;
	int guess = 1243;
	correctNhalfGuess(creditCode, guess);
	return 0;
}

//explains the rules of the game
void rules(void) {
	puts("Welcome to the \"Guess The Antiochus's Code\" game");
	puts("You have a mission, you need to discover the credit's card code!");
	puts("Here some rules:");
	puts("1 - you have to guess a code that composed by 4 digits number, in a range of 1-6 values");
	puts("2 - if you put two same numbers, you'll lose a guess");
	puts("3 - correct guess means that you put the right number in right place");
	puts("4 - half guess means that you put the right number in wrong place");
}

//you enter which level you want then it returns into the enum difficulty level
enum difficultLevel selectOptions (void){
	int option;
	puts("Which level you want?");
	puts("1 - Easy");
	puts("2 - Medium");
	puts("3 - Hard");
	puts("4 - Very Hard");
	
	while (true){
		scanf("%d", &option);
	
		switch (option){
			case 1:
				return EASY;
			case 2:
				return MEDIUM;
			case 3:
				return HARD;
			case 4:
				return ULTRA_HARD;
			default:
				puts ("Invalid option!!!!!!!!!!!!!!\nTry again blyat");
		}
	}
}

//returns the number of tries for each difficult
int difficultyTries(enum difficultLevel difficulty) {
	switch (difficulty){
		case EASY: return 20;
		case MEDIUM: return 15;
		case HARD: return 10;
		case ULTRA_HARD: return rand() % 21 + 5;
	}
}

//randomize each number in code and check if there is a duplications (by using 'doesDigitExist' function)
int creditCodeRnd (void){
	int creditCode = 0;
	
	for (int i = 0; i < DIGIT_COUNT; i++) {
		int credit = 0;

		do {
			credit = rand () % (MAX_NUM - MIN_NUM + 1) + MIN_NUM;
		} while (doesDigitExist(credit, creditCode));
		
		creditCode *= 10;
		creditCode += credit;
	}
	
	return creditCode;
}

//checks if there is(in credit code) numbers that duplicates
bool doesDigitExist (int credit,int creditCode){
	while (creditCode != 0){
		if (creditCode % 10 == credit)
			return true;
		else
			creditCode /= 10;
	}
	return false;
}

//checks that there is no duplicate numbers in input
int duplictesNumberCount (int guessCode){
	int guessCopy = guessCode;
	int duplicateCount = 0;

	for (int i = 1; i <= DIGIT_COUNT; guessCode /= 10, i++){
		int guessCopy = guessCode;
		for (int x = 1; x <= DIGIT_COUNT; guessCopy /= 10, x++){
			if(guessCode % 10 == guessCopy % 10)
				duplicateCount ++;
		}
	}
	return duplicateCount;
}

//checks the user guess code with genereted credit code
//correct guess means that you put the right number in right place
//half guess means that you put the right number in wrong place
void correctNhalfGuess (int creditCode, int guessCode){
	int creditCopy = creditCode;
	int guessCopy = guessCode;
	int correctNumCount = 0;
	int halfNumCount = 0;
	
	for (int i = 1; i <= DIGIT_COUNT; creditCopy /= 10, i++){
		guessCopy = guessCode;
		for (int x = 1; i <= DIGIT_COUNT; guessCopy /= 10, x++){
			if (i == x && creditCopy % 10 == guessCopy % 10){
				printf("Correct guess number %d\n", guessCopy % 10);
				correctNumCount ++;
			}
			else if (creditCopy % 10 == guessCopy % 10){
				printf ("Half guess number %d\n", guessCopy % 10);
				halfNumCount ++;
			}
		}
	}
	printf ("The count of correct numbers count is %d\n", correctNumCount);
	printf ("The count of half-correct numbers count is %d\n", halfNumCount);
}

//the func asks if the user want to play another round or not
bool toContinue (void){
	char choice;
	puts("Do you want another round?\ny - yes\nn - no");
	scanf("%c", &choice);

	if (choice == 'y')
		return true;
	else
		return false;
}