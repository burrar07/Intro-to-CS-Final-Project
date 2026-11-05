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
const int UCRTimes[25]={1437,1447,1447,1463,1445,1455,1456,1457,1465,1466,1465,1467,1471,1472,1476,1477,1483,1486,1494,1492,1500,1503,1513,1508,1524};
const int UCRScores[25]={49,97,103,159,178,235,247,251,298,313,315,320,350,366,389,395,440,483,492,497,539,568,579,597,710};
const int LewisTimes[27]={1487, 1489, 1491, 1494, 1495, 1495, 1502, 1509, 1516, 1522, 1529, 1525, 1542, 1546, 1545, 1546, 1551, 1554, 1557, 1561, 1585, 1585, 1600, 1607, 1607, 1638, 1655};
const int LewisScores[27]={114, 120, 130, 137, 141, 155, 195, 214, 260, 296, 308, 319, 381, 409, 411, 413, 426, 462, 475, 506, 596, 609, 663, 677, 697, 762, 845};
const int MarkCovertTimes[9]={1528, 1531, 1535, 1541, 1560, 1578, 1612, 1636, 1655};
const int MarkCovertScores[9]={54, 59, 68, 92, 119, 153, 200, 224, 240};
const int HighlanderTimes[16]={1459, 1468, 1469, 1472, 1473, 1476, 1479, 1477, 1485, 1484, 1486, 1485, 1500, 1516, 1531, 1559};
const int HighlanderScores[16]={76, 124, 131, 151, 154, 177, 192, 199, 215, 219, 221, 224, 286, 374, 390, 487};
const int ConferenceTimes[10]={1509, 1525, 1527, 1540, 1581, 1660, 1707, 1830, 1950, 2021};
const int ConferenceScores[10]={35, 53, 57, 72, 130, 179, 202, 252, 262, 280};
//Note both of these are 10ks
const int RegionalTimes[23]={1810, 1817, 1819, 1828, 1837, 1857, 1861, 1867, 1892, 1894, 1899, 1903, 1906, 1910, 1921, 1933, 1929, 1930, 1947, 1960, 1991, 2010, 2055};
const int RegionalScores[23]={75, 88, 97, 126, 141, 190, 206, 223, 299, 304, 317, 324, 338, 346, 379, 402, 402, 425, 455, 493, 599, 642, 695};
const int NationalsTimes[34]={1810, 1811, 1827, 1828, 1841, 1862, 1873, 1879, 1884, 1885, 1880, 1884, 1891, 1884, 1894, 1895, 1903, 1905, 1913, 1909, 1916, 1912, 1917, 1922, 1926, 1927, 1937, 1935, 1937, 1942, 1947, 1947, 1997, 2064};
const int NationalsScores[34]={62, 71, 121, 122, 162, 261, 310, 338, 373, 375, 380, 390, 394, 430, 431, 456, 490, 500, 518, 541, 543, 554, 560, 582, 640, 644, 664, 670, 695, 737, 770, 770, 980, 1096};
const string Schedule[7]={"Mark Covert","UCR","Lewis Invitational","Highlander Invitational","Conference","Regionals","Nationals"};

//Initial Menu
int main()
{
    int meetCount=0;
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

void schedule (Runner runner[],int division){
string workoutChoice;
    for (int i=1; i<=16;i++){
if (i!=3&&i!=5&&i!=8&&i!=9&&i!=12&&i!=14&&i!=16)
        cout<<"Welcome to week "<<i<<". These are the current stats of the runners: \n";
for (int j=0; j<7;j++){
    cout<<runner[j].name<<":"<<endl;
cout << "Endurance: " << runner[j].stats.endurance << ", Speed: " << runner[j].stats.speed << ", Fatigue: " <<runner[j].stats.fatigue << "\n";
}
for (int a=1;a<=2;a++){
chooseWorkout(workoutChoice,a);
for (int b=0;b<7;b++){
    applyWorkout(runner[b],workoutChoice);
}
}
if (i==3||i==5||i==8||i==9||i==12||i==14||i==16){
//meet week function
}
}
}

int calc8kTime(RunnerStats& stats){
    double time = 1803.0- 3.0 * stats.endurance- 1.8 * stats.speed+ 1.5 * stats.fatigue;

    return static_cast<int>(round(time));
}

void runMeet(Runner runners[],int meetNumber){
    int runnersTimes[7];
    int totalTime, averageTime;
    for (int i=0;i<7;i++){
        runnersTimes[i]=calc8kTime(runners[i].stats);
        totalTime+=runnersTimes[i];
    }
    averageTime = totalTime / 7;
    cout<<"Meet Results:\n";
    for (int i=0;i<7;i++){
        cout<<runners[i].name<<": "<<runnersTimes[i]/60<<":"<<runnersTimes[i]%60<<endl;
    }
}

int calculateScore(int time, int meetNumber, int averageTime){
    
}
