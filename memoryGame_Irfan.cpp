#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm> 
#include <windows.h> 
#include <chrono>    
#include <ratio>     

using namespace std;

const int EASY_GRID_SIZE = 2;
const int MEDIUM_GRID_SIZE = 3;
const int HARD_GRID_SIZE = 4;

const int EASY_NUM_CARDS = EASY_GRID_SIZE * EASY_GRID_SIZE;
const int MEDIUM_NUM_CARDS = MEDIUM_GRID_SIZE * MEDIUM_GRID_SIZE;
const int HARD_NUM_CARDS = HARD_GRID_SIZE * HARD_GRID_SIZE;

const int EASY_SHOW_TIME_SECONDS = 3;
const int MEDIUM_SHOW_TIME_SECONDS = 5;
const int HARD_SHOW_TIME_SECONDS = 7;

vector<vector<int>> gameGrid;
vector<int> shuffledNumbers;

void InitializeGame(int gridSize) {
    
    for (int i = 1; i <= gridSize * gridSize; ++i) {
        shuffledNumbers.push_back(i);
    }

    
    srand(static_cast<unsigned int>(time(nullptr))); 
    random_shuffle(shuffledNumbers.begin(), shuffledNumbers.end());

    
    gameGrid.assign(gridSize, vector<int>(gridSize, 0));
    int numIndex = 0;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            gameGrid[i][j] = shuffledNumbers[numIndex++];
        }
    }
}

void RenderGame(int gridSize, bool reveal) {
    system("cls"); 
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (reveal) {
                cout << gameGrid[i][j] << '\t';
            } else {
                cout << "X\t"; 
            }
        }
        cout << endl;
    }
}

void ShowCardsForDuration(int gridSize, int showTimeSeconds) {
    RenderGame(gridSize, true); 
    cout << "Remember the numbers for " << showTimeSeconds << " seconds..." << endl;
    Sleep(showTimeSeconds * 1000); 
    RenderGame(gridSize, false); 
}

int GuessCards(int gridSize) {
    int score = 0;
    auto startTime = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            cout << "Enter your guess for row " << i + 1 << ", column " << j + 1 << ": ";
            int guess;
            cin >> guess;
            
            if (guess == gameGrid[i][j]) {
                cout << "Correct!" << endl;
                score++;
            } else {
                cout << "Wrong!" << endl;
            }
        }
    }
    
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = endTime - startTime;
    double elapsedTimeSeconds = duration.count();
    
    cout << "Time taken: " << elapsedTimeSeconds << " seconds" << endl;
    cout << "Your score: " << score << " out of " << gridSize * gridSize << endl;
    
    return score;
}

int main() {
    int difficulty;
    
    cout << "Welcome to the Memory Game!" << endl;
    cout << "Select the difficulty level:" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "Enter your choice (1/2/3): ";
    cin >> difficulty;
    
    int gridSize, showTimeSeconds;
    
    switch (difficulty) {
        case 1:
            gridSize = EASY_GRID_SIZE;
            showTimeSeconds = EASY_SHOW_TIME_SECONDS;
            break;
        case 2:
            gridSize = MEDIUM_GRID_SIZE;
            showTimeSeconds = MEDIUM_SHOW_TIME_SECONDS;
            break;
        case 3:
            gridSize = HARD_GRID_SIZE;
            showTimeSeconds = HARD_SHOW_TIME_SECONDS;
            break;
        default:
            cout << "Invalid choice. Exiting." << endl;
            return 1;
    }
    
    InitializeGame(gridSize);
    
    cout << "Press Enter to reveal the numbers for " << showTimeSeconds << " seconds..." << endl;
    cin.ignore(); 
    ShowCardsForDuration(gridSize, showTimeSeconds);
    
    cout << "Now, guess the positions of the numbers:" << endl;
    int score = GuessCards(gridSize);
    
    cout << "Game over!" << endl;
    
    return 0;
}
