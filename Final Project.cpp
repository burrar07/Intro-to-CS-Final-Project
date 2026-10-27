#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <string>

using namespace std;

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
        cout << "\nChoose Your Division\n";
        cout << "1. Division III (Easy)\n";
        cout << "2. Division II (Medium)\n";
        cout << "3. Division I (Hard)\n";
    
        int division;
    
        cout << "\nEnter your division: ";
        cin >> division;
    
        if (division == 1)
        {
            cout << "\nYou selected Division III.\n";
        }
        else if (division == 2)
        {
            cout << "\nYou selected Division II.\n";
        }
        else if (division == 3)
        {
            cout << "\nYou selected Division I.\n";
        }
        else
        {
            cout << "\nInvalid division choice.\n";
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

void getName(string name, int number){
    cout<<"Enter the name for runner "<<number<<": ";
    cin>>name;
}

int startScore(string name){
    int score;
    random_device scoreStarter;
    mt19937 generator(scoreStarter());
    uniform_int_distribution<int> distribution(1, 100);
    score = distribution(generator);
    return score;
}

void chooseWorkout (string workout, int number, int choice){
    if (number==1){
        cout<<"Choose the first workout for the week";
    }
    else if (number==2){
        cout<<"Choose the second workout for the week";
    }
    cout<<"Options: \n1. Steady State\n2. Mile Repeats\n3. The Eagle\n4. Hill Repeats\n5. 2k Repeats\n6. Premeet\n";
    cin>>choice;
}
