#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <string>

using namespace std;

struct RunnerStats {
    int endurance;
    int speed;
    int fatigue;
};

struct Runner {
    string name;
    RunnerStats stats;
    string workout;
};

void getName(string& name, int number);
int startScore(int difficulty);
void chooseWorkout(string workout, int number, int choice);
void applyWorkout(Runner& runner, string workout);
void runWeek(Runner runners[], int runnerCount, int week);
int chooseDivision();
RunnerStats generateRunnerStats(int difficulty);

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
        RunnerStats runnerStats[7];
        
        for(int i = 0; i<7; i++)
        {
            getName(runners[i], i + 1);
            scores[i] = startScore(difficulty);
            runnerStats[i] = generateRunnerStats(difficulty);

            cout << runners[i] << " has a starting score of " << scores[i] << "\n";
            cout << "Endurance: " << runnerStats[i].endurance << ", Speed: " << runnerStats[i].speed << ", Fatigue: " << runnerStats[i].fatigue << "\n";
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

void applyWorkout(Runner& runner, string workout) 
{
    runner.workout = workout;

    if (workout == "Steady State") {
        runner.stats.endurance += 6;
        runner.stats.speed += 2;
        runner.stats.fatigue += 5;
    } else if (workout == "Mile Repeats") {
        runner.stats.speed += 6;
        runner.stats.endurance += 3;
        runner.stats.fatigue += 7;
    } else if (workout == "The Eagle") {
        runner.stats.endurance += 5;
        runner.stats.speed += 4;
        runner.stats.fatigue += 6;
    } else if (workout == "Hill Repeats") {
        runner.stats.endurance += 6;
        runner.stats.speed += 3;
        runner.stats.fatigue += 10;
    } else if (workout == "2k Repeats") {
        runner.stats.speed += 4;
        runner.stats.endurance += 4;
        runner.stats.fatigue += 7;
    } else if (workout == "Premeet") {
        runner.stats.speed += 1;
        runner.stats.endurance += 1;
        runner.stats.fatigue += 2;
    } else if (workout == "Rest") {
        runner.stats.fatigue -= 6;
    }

    // Just makes sure that things can't go too high or too low
    if (runner.stats.endurance > 100) runner.stats.endurance = 100;
    if (runner.stats.speed > 100) runner.stats.speed = 100;
    if (runner.stats.fatigue > 100) runner.stats.fatigue = 100;

    if (runner.stats.fatigue < 0) runner.stats.fatigue = 0;
    if (runner.stats.endurance < 0) runner.stats.endurance = 0;
    if (runner.stats.speed < 0) runner.stats.speed = 0;
}

void getName(string& name, int number)
{
    cout<<"Enter the name for runner "<<number<<": ";
    cin>>name;
}

RunnerStats generateRunnerStats(int difficulty) {
    RunnerStats stats;

    random_device rd;
    mt19937 gen(rd());

    int enduranceMin = 40, enduranceMax = 95;
    int speedMin = 35, speedMax = 90;
    int fatigueMin = 20, fatigueMax = 80;

    if (difficulty == 3) { // Division III
        enduranceMin = 55; enduranceMax = 95;
        speedMin = 40; speedMax = 85;
        fatigueMin = 15; fatigueMax = 30;
    } else if (difficulty == 2) { // Division II
        enduranceMin = 50; enduranceMax = 90;
        speedMin = 35; speedMax = 80;
        fatigueMin = 25; fatigueMax = 45;
    } else if (difficulty == 1) { // Division I
        enduranceMin = 45; enduranceMax = 85;
        speedMin = 30; speedMax = 75;
        fatigueMin = 35; fatigueMax = 60;
    }

    uniform_int_distribution<int> enduranceDist(enduranceMin, enduranceMax);
    uniform_int_distribution<int> speedDist(speedMin, speedMax);
    uniform_int_distribution<int> fatigueDist(fatigueMin, fatigueMax);

    stats.endurance = enduranceDist(gen);
    stats.speed = speedDist(gen);
    stats.fatigue = fatigueDist(gen);

    return stats;
}
