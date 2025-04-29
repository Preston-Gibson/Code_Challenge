//Start time: 11/27/2021 at 8:39 a.m
//Finish time: 11/27/2021 at 12:28 p.m
//To-do: If I had more time I would have fixed a small bug with that happens after playing the game about 7 times through
//which ends the program without an error code. I'm pretty sure it has something to do with trying to use the 10th word "Mountain".
//After fixing the bug I would have created an if loop with another variable that would track how many times the game has been completed.
//After all the words had been guessed I would have created a different ending with a congratulatory message and ended the code without
//asking for the Y/N as it would be unnecessary to have that prompt.


#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>
using namespace std;

void PrintProgress(vector<char> playerGuesses, string playerProgress, int numCorrect, int numIncorrect, int numGuesses); //PRINTS THE SUMMARY OF GUESSES (CORRECT, INCORRECT, TOTAL, AND REMAINING SPACES LEFT)
void GuessLetter(vector<char>& GuessList, string currentWord, string& playerProgress, int& numCorrect, int& numIncorrect, int& numGuesses); //FUNCTION FOR GUESSING THE WORD
void UpdateWordBank(vector<string> &wordBank, string wordToDelete); //DELETES THE WORD FROM THE WORD BANK TO PREVENT GETTING THE SAME WORD ON REPEATED ITERATIONS
void ValidGuess(bool& validGuess, char letterGuess, vector<char> guessList); //CHECKS TO MAKE SURE THE USER ENTERS A NEW LETTER

int main() {
    bool hasFinished; //BLAH BLAH BLAH
    bool keepPlaying = true;
    char playerInput;
    int correctGuesses;
    int incorrectGuesses;
    int totalGuesses;
    string currentWord;
    string playerProgress;
    vector<char> playerGuesses;
    vector<string> wordBank{"APPLE", "KARATE", "TIRAMISU", "CATAPULT", "BEDROOM", "FIREFIGHTER", "APARTMENT", "SWEATER", "AVALANCHE", "MOUNTAIN"};
    srand(time(0));

    cout << "Welcome to Hangman! The proud cure for boredom ever since you can remember!" << endl;
    sleep(1);
    while(keepPlaying){
        currentWord = wordBank.at(rand() % (wordBank.size() - 1)); //Chooses a random word
        UpdateWordBank(wordBank, currentWord);
        correctGuesses = 0; //RESETS VARIABLES FOR EACH FUTURE ITERATION
        incorrectGuesses = 0; //RESETS VARIABLES FOR EACH FUTURE ITERATION
        totalGuesses = 0; //RESETS VARIABLES FOR EACH FUTURE ITERATION
        playerProgress.clear(); //RESETS VARIABLES FOR EACH FUTURE ITERATION
        playerGuesses.clear(); //RESETS VARIABLES FOR EACH FUTURE ITERATION
        for (unsigned int i = 0; i < currentWord.size(); i++){
            playerProgress.push_back('_');
        }
        cout << "There are " << currentWord.size() << " letters in the mystery word!" << endl;
        hasFinished = false;
        while(!hasFinished){
            GuessLetter(playerGuesses, currentWord, playerProgress, correctGuesses, incorrectGuesses, totalGuesses);
            sleep(1); //GIVES TIME FOR READABILITY
            PrintProgress(playerGuesses, playerProgress, correctGuesses, incorrectGuesses, totalGuesses);
            sleep(1); //GIVES TIME FOR READABILITY
            if(playerProgress == currentWord){
                hasFinished = true;
            }
        }
        cout << "CONGRATULATIONS! You've won!\n" << "It only took you " << totalGuesses << " guesses!" << endl;
        sleep(1);
        cout << "Want to play again? (Y/N)" << endl;
        cin >> playerInput;
        playerInput = toupper(playerInput);
        if (playerInput == 'N'){
            keepPlaying = false;
        }
        sleep(1);
    }
    cout << "Thanks for playing! See you next time!" << endl;
    return 0;
}

void PrintProgress(vector<char> playerGuesses, string playerProgress, int numCorrect, int numIncorrect, int numGuesses) {
    cout << "Letters Guessed: ";
    for (unsigned int i = 0; i < playerGuesses.size() - 1; i++){
        cout << playerGuesses.at(i) << ", ";
    }
    cout << playerGuesses.at(playerGuesses.size() - 1);
    cout << "\nTotal Guesses: " << numGuesses << "\nCorrect letters: " << numCorrect << "/" << playerProgress.size() << "\nIncorrect Letters: " << numIncorrect << "/" << numGuesses << "\n" << endl;
    cout << playerProgress << endl;
}

void ValidGuess(bool& validGuess, char letterGuess, vector<char> guessList){
    for (unsigned int i = 0; i < guessList.size(); i++){
        if (letterGuess == guessList.at(i)){
            cout << "You've already guessed that letter! Please guess again.\n" << endl;
            return;
        }
    }
    validGuess = true;
}

void GuessLetter(vector<char>& guessList, string currentWord, string& playerProgress, int& numCorrect, int& numIncorrect, int& numGuesses){
    char playerGuess;
    bool validGuess = false;
    while (!validGuess) { //Only accepts a letter that hasn't been guessed before
        cout << "Guess a letter: " << endl;
        cin >> playerGuess;
        playerGuess = toupper(playerGuess);
        ValidGuess(validGuess, playerGuess, guessList);
    }
    guessList.push_back(playerGuess);
    if (currentWord.find(playerGuess) == string::npos){
        cout << "Oops! Try Again! Your letter was not in the mystery word." << endl;
        numIncorrect++;
    } else{
        while(currentWord.find(playerGuess) != string::npos){
            playerProgress.at(currentWord.find(playerGuess)) = currentWord.at(currentWord.find(playerGuess));
            currentWord.at(currentWord.find(playerGuess)) = '*';
            numCorrect++;
        }
    }
    numGuesses++;
}

void UpdateWordBank(vector<string> &wordBank, string wordToDelete){
    for (unsigned int i = 0; i < wordBank.size(); i++){
        if (wordToDelete == wordBank.at(i)){
            wordBank.erase(wordBank.begin() + i);
        }
    }
}