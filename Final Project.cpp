#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <string>

using namespace std;

void getName(string& name, int number);
int startScore(int diffiuclty)
void chooseWorkout(string workout, int number, int choice);
int chooseDivision();

//Initial Menu
int main()
{
    cout << "============================\n";
    cout << "       XC MANAGEMENT\n";
    cout << "============================\n";

    cout << "\n1. Start New Season\n";
    cout << "2. Quit Game\n";

    int choice;

    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
    {

        //selecting difficulty
        int difficulty = 0;
        int division = chooseDivision();
    
        if (division == 1)
        {
            cout << "\nYou selected Division III.\n";
            difficulty = 3;
        }
        else if (division == 2)
        {
            cout << "\nYou selected Division II.\n";
            difficulty = 2;
        }
        else if (division == 3)
        {
            cout << "\nYou selected Division I.\n";
            difficulty = 1;
        }
        else
        {
            cout << "\nInvalid division choice.\n";
        }

        //Naming the runners 
        
        string runners[7];
        int scores[7];
        
        for(int i = 0; i<7; i++)
        {
            getName(runners[i], i + 1);
            scores[i] = startScore(difficulty);
            
            cout << runners[i] << " has a starting score of " << scores[i] << "\n";
        }
        
    }
    else if (choice == 2)
    {
        cout << "\nThanks for playing!\n";
    }
    else
    {
        cout << "\nInvalid choice. Please restart the game.\n";
    }

    return 0;
} 

int chooseDivision()
{
    int division;
    
    cout << "\nChoose Your Division\n";
    cout << "1. Division III (Easy)\n";
    cout << "2. Division II (Medium)\n";
    cout << "3. Division I (Hard)\n";

    cout << "\nEnter your division: ";
    cin >> division;

    return division;
}

void getName(string& name, int number){
    cout<<"Enter the name for runner "<<number<<": ";
    cin>>name;
}

int startScore(int difficulty)
{
    random_device scoreStarter;
    mt19937 generator(scoreStarter());

    int minScore = 1;
    int maxScore = 100;

    if (difficulty == 3)
    {
        minScore = 60;
        maxScore = 85;
    }
    else if (difficulty == 2)
    {
        minScore = 45;
        maxScore = 75;
    }
    else if (difficulty == 1)
    {
        minScore = 30;
        maxScore = 65;
    }

    uniform_int_distribution<int> distribution(minScore, maxScore);

    return distribution(generator);
}

void chooseWorkout (string& workout, int number)
{
    int choice;

    cout << "\nChoose workout #" << number << " for the week:\n";
    cout << "1. Steady State\n";
    cout << "2. Mile Repeats\n";
    cout << "3. The Eagle\n";
    cout << "4. Hill Repeats\n";
    cout << "5. 2k Repeats\n";
    cout << "6. Premeet\n";

    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
        workout = "Steady State";
    else if (choice == 2)
        workout = "Mile Repeats";
    else if (choice == 3)
        workout = "The Eagle";
    else if (choice == 4)
        workout = "Hill Repeats";
    else if (choice == 5)
        workout = "2k Repeats";
    else if (choice == 6)
        workout = "Premeet";
    else
        workout = "Invalid";

    cout << "\nSelected workout: " << workout << "\n";
}
