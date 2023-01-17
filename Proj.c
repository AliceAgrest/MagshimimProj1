#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
enum difficultLevel {EASY = 1, MEDIUM, HARD, ULTRA_HARD};

void rules(void);
void theLion (void);
int creditCodeRnd(void);
enum difficultLevel selectOptions(void);
int difficultyTries(enum difficultLevel difficulty);
bool inRange (int guessCode);
void clear (void);
bool doesDigitExist (int credit,int creditCode);
int creditCodeRnd (void);
bool duplictesNumberCount (int guessCode);
int anotherGuess (int guessCode, bool duplication, bool range);
void correctNhalfGuess (int creditCode, int guessCode);

#define MAX_NUM 6
#define MIN_NUM 1
#define DIGIT_COUNT 4
#define EASY_TRIES 20
#define MEDIUM_TRIES 15
#define HARD_TRIES 10
#define MAX_RAND_TRY 25
#define MIN_RAND_TRY 5

int main(void) {
	srand(time(NULL));
	bool dontStop = true;
	while (dontStop == true){
		rules();
		theLion();
		int creditCode = creditCodeRnd();
		int option = selectOptions();
		int tries = difficultyTries(option);
		int guessCode;
		bool range;
		bool duplication = false;
		char toContinue;
		bool toContinue1 = true;

		//loop of selected tries
		for (; tries > 0; tries--){
			if (option != ULTRA_HARD)
				printf("You have %d tries\n", tries);
			puts("Enter a guess for the code: ");
			scanf("%d", &guessCode);
			clear();
			range = inRange(guessCode);
			duplication = duplictesNumberCount(guessCode);
			guessCode = anotherGuess(inRange(guessCode), duplication, range);

			if (creditCode == guessCode){
				printf("You win!!! The credit code was %d\nCongratulations!\n", creditCode);
				break;
			}
			else{
				correctNhalfGuess(creditCode, guessCode);
				continue;
			}
		}
		//checks if user entered the right code before he ends all of his tries
		if (creditCode == guessCode && tries == 0)
			printf("You win!!!\nThe credit code was %d\nCongratulations!\n", creditCode);
		else if (creditCode != guessCode)
			printf("You lost :(\nThe credit Code was %d\nMaybe next time\n", creditCode);
		
		puts("Do you want go to another round?\nPress any key to continue\nn - no");
		scanf(" %c", &toContinue);
		if (toContinue == 'n')
			dontStop = false;
		else
			dontStop = true;
	}
	return 0;
}

//explains the rules of the game
void rules (void) {
	puts("Welcome to the \"Guess The Antiochus's Code\" game");
	puts("You have a mission, you need to discover the credit's card code!");
	puts("Here some rules:");
	puts("1 - you have to guess a code that composed by 4 digits number, in a range of 1-6 values");
	puts("2 - if you put two same numbers, you'll lose a guess");
	puts("3 - correct guess means that you put the right number in right place");
	puts("4 - half guess means that you put the right number in wrong place");
}

//prints lion
void theLion (void){
	puts("	      ,  ,, ,");
	puts(" 	   , ,; ; ;;  ; ;  ;");
	puts("         , ; ';  ;  ;; .-''\\ ; ;");
	puts("	, ;  ;`  ; ,; . / /8b \\ ; ;");
	puts("	`; ; .;'         ;,\\8 |  ;  ;");
	puts("	` ;/   / `_      ; ;;    ;  ; ;");
	puts("	   |/.'  /9)    ;  ; `    ;  ; ;");
	puts("	  ,/'          ; ; ;  ;   ; ; ; ;");
	puts("	 /_            ;    ;  `    ;  ;");
	puts("	`?8P\"  .      ;  ; ; ; ;     ;  ;;");
	puts("	| ;  .:: `     ;; ; ;   `  ;  ;");
	puts("	`' `--._      ;;  ;;  ; ;   ;   ;");
	puts("	`-..__..--''   ; ;    ;;   ; ;   ;");
	puts("			;    ; ; ;   ;     ;");
}

//you enter which level you want then it returns into the enum difficulty level
enum difficultLevel selectOptions (void){
	int option;
	puts("Which level you want?");
	printf("%d - Easy\n", EASY);
	printf("%d - Medium\n", MEDIUM);
	printf("%d - Hard\n", HARD);
	printf("%d - Very Hard\n", ULTRA_HARD);

	while (true){
		scanf("%d", &option);
		if (option >= EASY && option <= ULTRA_HARD)
			return option;
		else
			puts("Invalid input!!!!!!\nTry again");
	}
}

//returns the number of tries for each difficult
int difficultyTries(enum difficultLevel difficulty) {
	switch (difficulty){
		case EASY: return EASY_TRIES;
		case MEDIUM: return MEDIUM_TRIES;
		case HARD: return HARD_TRIES;
		case ULTRA_HARD: return rand() % (MAX_RAND_TRY - MIN_RAND_TRY + 1) + MIN_RAND_TRY;
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

//checks that the input is in range
bool inRange (int guessCode){
	bool was = false;
	while (true) {
		int inRange = 0; 
		int guessCopy = guessCode;
		for (int i = 1; i <= DIGIT_COUNT; guessCopy /= 10, i++){
			if (guessCopy % 10 >= 1 && guessCopy % 10 <= 6)
				inRange ++;
			else if ((guessCopy % 10 >= 'a' && guessCopy <= 'z') || (guessCopy >= 'A' && guessCopy <= 'Z')){
				printf("Invaild input!!!!!!!!!!Enter another guess: ");	
				was = true;
			}
		}
		if (inRange != DIGIT_COUNT && was != true)
			return false;
		else 
			return true;
	}
}

//clears inputs buffer also check the input 
void clear (void){
	while(getchar() != '\n'){
		if ((getchar() >= 'a' && getchar() <= 'z') || (getchar() >= 'A' && getchar() <= 'Z') || getchar() == 32){
			for(;;)
				printf("Invalid input!!!!!Enter another guess: ");
		}
		else
			break;
	}
}

//checks that there is no duplicate numbers in input
bool duplictesNumberCount (int guessCode){
	bool duplication = false;
	int duplicateCount = 0;
	int t = guessCode / 1000;//t - thousands
	int h = (guessCode / 100) % 10;//h - hundreds
	int d = (guessCode / 10) % 10;//d - dozens
	int u = guessCode % 10;//u - units

	if (t == h || t == d || t == u)
		duplicateCount++;
	else if (h == d || h == u)
		duplicateCount++;
	else if (d == u)
		duplicateCount++;

	duplication = (duplicateCount > 0) ? true : false;
	return duplication;
}

//if the input has duplicates the func asks for another input also check if the other iput is in range
int anotherGuess (int guessCode, bool duplication, bool range){
	while(true){
		puts ("Invaild input!!!!!!!!!!\nEnter another guess code: ");
		scanf("%d", &guessCode);
		clear();
		range = inRange (guessCode);
		duplication = duplictesNumberCount(guessCode);
		if (duplication == false && range == true)
			return guessCode;
	}
}

//checks the user guess code with genereted credit code
//correct guess means that you put the right number in right place
//half guess means that you put the right number in wrong place
void correctNhalfGuess (int creditCode, int guessCode){
	int guessCopy = guessCode;
	int correctNumCount = 0;
	int halfNumCount = 0;
	
	for (int i = 1; i <= DIGIT_COUNT; creditCode /= 10, i++){
		guessCopy = guessCode;
		for (int x = 1; x <= DIGIT_COUNT; guessCopy /= 10, x++){
			if (i == x && creditCode % 10 == guessCopy % 10){
				printf("Correct guess number %d\n", guessCopy % 10);
				correctNumCount ++;
			}
			else if (creditCode % 10 == guessCopy % 10){
				printf ("Half guess number %d\n", guessCopy % 10);
				halfNumCount ++;
			}
		}
	}
	printf ("The count of correct numbers count is %d\n", correctNumCount);
	printf ("The count of half-correct numbers count is %d\n", halfNumCount);
}
