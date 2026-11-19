#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <string>
#include <cmath>
#include <limits>

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

struct OpposingTeam {
    string name;
    int averageTime;
    int raceTime;
    int teamScore;
};

OpposingTeam markCovertTeams[4] = {
    {"Cal State Fullerton", 1510, 0, 0},
    {"UC Irvine", 1490, 0, 0},
    {"Concordia Irvine", 1540, 0, 0},
    {"Azusa Pacific", 1550, 0, 0}
};

void getName(string& name, int number);
int startScore(int difficulty);
void chooseWorkout(string& workout, int number);
void applyWorkout(Runner& runner, string workout);
int chooseDivision();
RunnerStats generateRunnerStats(int difficulty);
void schedule(Runner runners[], int division);
int calc8kTime(RunnerStats& stats);
int calc10kTime(RunnerStats& stats);
void runMeet(Runner runners[], int meetNumber, int division);
int calculateScore(int time, int meetNumber, int averageTime);
void nationalComparison(int runnersTimes[], int division, int meetNumber);
void simulateOpponents(OpposingTeam teams[], int teamCount);
int calculatePlacement(int runnersTimes[], OpposingTeam teams[], int teamCount);

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

// Regionals and Nationals are 10K races.
const int RegionalTimes[23]={1810, 1817, 1819, 1828, 1837, 1857, 1861, 1867, 1892, 1894, 1899, 1903, 1906, 1910, 1921, 1933, 1929, 1930, 1947, 1960, 1991, 2010, 2055};
const int RegionalScores[23]={75, 88, 97, 126, 141, 190, 206, 223, 299, 304, 317, 324, 338, 346, 379, 402, 402, 425, 455, 493, 599, 642, 695};
const int NationalsTimes[34]={1810, 1811, 1827, 1828, 1841, 1862, 1873, 1879, 1884, 1885, 1880, 1884, 1891, 1884, 1894, 1895, 1903, 1905, 1913, 1909, 1916, 1912, 1917, 1922, 1926, 1927, 1937, 1935, 1937, 1942, 1947, 1947, 1997, 2064};
const int NationalsScores[34]={62, 71, 121, 122, 162, 261, 310, 338, 373, 375, 380, 390, 394, 430, 431, 456, 490, 500, 518, 541, 543, 554, 560, 582, 640, 644, 664, 670, 695, 737, 770, 770, 980, 1096};

const string Schedule[7]={"Mark Covert","UCR","Lewis Invitational","Highlander Invitational","Conference","Regionals","Nationals"};

const string D1NationalTeams[3] = {
    "Alabama",
    "New Mexico",
    "Arkansas"
};
const double D1NationalAverage[3] = {
    1345.8,  // Alabama: 22:25.8
    1369.2,  // New Mexico: 22:49.2
    1368.3   // Arkansas: 22:48.3

const string D2NationalTeams[3] = {
    "Adams State",
    "Colorado School of Mines",
    "West Texas A&M"
};

const double D2NationalAverage[3] = {
    1396.5,  // Adams State: 23:16.5
    1399.5,  // Colorado School of Mines: 23:19.5
    1404.4   // West Texas A&M: 23:24.4
};

const string D3NationalTeams[3] = {
    "MIT",
    "SUNY Geneseo",
    "UW-La Crosse"
};

const double D3NationalAverage[3] = {
    1447.1,  // MIT: 24:07.1
    1452.3,  // SUNY Geneseo: 24:12.3
    1459.7   // UW-La Crosse: 24:19.7
};

};
int main() {
    cout << "============================\n";
    cout << "       XC MANAGEMENT\n";
    cout << "============================\n";
    cout << "\n1. Start New Season\n";
    cout << "2. Quit Game\n";

    int choice;
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int division = chooseDivision();
        int difficulty = 0;

        if (division == 1) {
            cout << "\nYou selected Division III.\n";
            difficulty = 3;
        } else if (division == 2) {
            cout << "\nYou selected Division II.\n";
            difficulty = 2;
        } else if (division == 3) {
            cout << "\nYou selected Division I.\n";
            difficulty = 1;
        } else {
            cout << "\nInvalid division choice.\n";
            return 0;
        }

        Runner runners[7];
        int scores[7];

        for (int i = 0; i < 7; i++) {
            getName(runners[i].name, i + 1);
            scores[i] = startScore(difficulty);
            runners[i].stats = generateRunnerStats(difficulty);
            runners[i].workout = "";

            cout << runners[i].name << " has a starting score of " << scores[i] << "\n";
            cout << "Endurance: " << runners[i].stats.endurance
                 << ", Speed: " << runners[i].stats.speed
                 << ", Fatigue: " << runners[i].stats.fatigue << "\n";
        }

        schedule(runners, division);
    } else if (choice == 2) {
        cout << "\nThanks for playing!\n";
    } else {
        cout << "\nInvalid choice. Please restart the game.\n";
    }

    return 0;
}

int chooseDivision() {
    int division;
    cout << "\nChoose Your Division\n";
    cout << "1. Division III (Easy)\n";
    cout << "2. Division II (Medium)\n";
    cout << "3. Division I (Hard)\n";
    cout << "\nEnter your division: ";
    cin >> division;
    return division;
}

int startScore(int difficulty) {
    random_device scoreStarter;
    mt19937 generator(scoreStarter());
    int minScore = 1;
    int maxScore = 100;

    if (difficulty == 3) {
        minScore = 60;
        maxScore = 85;
    } else if (difficulty == 2) {
        minScore = 45;
        maxScore = 75;
    } else if (difficulty == 1) {
        minScore = 30;
        maxScore = 65;
    }

    uniform_int_distribution<int> distribution(minScore, maxScore);
    return distribution(generator);
}

void chooseWorkout(string& workout, int number) {
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

    if (choice == 1) workout = "Steady State";
    else if (choice == 2) workout = "Mile Repeats";
    else if (choice == 3) workout = "The Eagle";
    else if (choice == 4) workout = "Hill Repeats";
    else if (choice == 5) workout = "2k Repeats";
    else if (choice == 6) workout = "Premeet";
    else workout = "Invalid";

    cout << "\nSelected workout: " << workout << "\n";
}

void applyWorkout(Runner& runner, string workout) {
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
        runner.stats.fatigue -= 3;
    } else if (workout == "Rest") {
        runner.stats.fatigue -= 6;
    }

    if (runner.stats.endurance > 100) runner.stats.endurance = 100;
    if (runner.stats.speed > 100) runner.stats.speed = 100;
    if (runner.stats.fatigue > 100) runner.stats.fatigue = 100;
    if (runner.stats.fatigue < 0) runner.stats.fatigue = 0;
    if (runner.stats.endurance < 0) runner.stats.endurance = 0;
    if (runner.stats.speed < 0) runner.stats.speed = 0;
}

void getName(string& name, int number) {
    cout << "Enter the name for runner " << number << ": ";
    cin >> name;
}

RunnerStats generateRunnerStats(int difficulty) {
    RunnerStats stats;
    random_device rd;
    mt19937 gen(rd());
    int enduranceMin = 40, enduranceMax = 95;
    int speedMin = 35, speedMax = 90;
    int fatigueMin = 20, fatigueMax = 80;

    if (difficulty == 3) {
        enduranceMin = 55; enduranceMax = 95;
        speedMin = 40; speedMax = 85;
        fatigueMin = 15; fatigueMax = 30;
    } else if (difficulty == 2) {
        enduranceMin = 50; enduranceMax = 90;
        speedMin = 35; speedMax = 80;
        fatigueMin = 25; fatigueMax = 45;
    } else if (difficulty == 1) {
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

void schedule(Runner runner[], int division) {
    int meetCount = 0;
    string workoutChoice;

    for (int i = 1; i <= 16; i++) {
        cout << "\nWelcome to week " << i << ". These are the current stats of the runners:\n";
        for (int j = 0; j < 7; j++) {
            cout << runner[j].name << ":\n";
            cout << "Endurance: " << runner[j].stats.endurance
                 << ", Speed: " << runner[j].stats.speed
                 << ", Fatigue: " << runner[j].stats.fatigue << "\n";
        }

        for (int a = 1; a <= 2; a++) {
            chooseWorkout(workoutChoice, a);
            for (int b = 0; b < 7; b++) {
                applyWorkout(runner[b], workoutChoice);
            }
        }

        if (i == 3 || i == 5 || i == 8 || i == 9 || i == 12 || i == 14 || i == 16) {
            runMeet(runner, meetCount, division);
            meetCount++;
        }
        
        for (int j = 0; j < 7; j++) {
            runner[j].stats.fatigue -= 10;
    
            if (runner[j].stats.fatigue < 0) {
                runner[j].stats.fatigue = 0;
            }
        }
    }
}

int calc8kTime(RunnerStats& stats) {
    double time = 1803.0 - 3.0 * stats.endurance
                  - 1.8 * stats.speed + 1.5 * stats.fatigue;
    return static_cast<int>(round(time));
}

int calc10kTime(RunnerStats& stats) {
    int time8k = calc8kTime(stats);
    return static_cast<int>(round(time8k * 1.27));
}

void runMeet(Runner runners[], int meetNumber) {
    int runnersTimes[7];
    int runnersScores[7];
    int totalTime = 0;
    int averageTime;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> raceVariation(-15, 15);

    for (int i = 0; i < 7; i++) {
        if (meetNumber >= 5) {
            runnersTimes[i] = calc10kTime(runners[i].stats);
        } else {
            runnersTimes[i] = calc8kTime(runners[i].stats);
        }
        runnersTimes[i] += raceVariation(gen);
        runners[i].stats.fatigue += 8;

        if (runners[i].stats.fatigue > 100) {
            runners[i].stats.fatigue = 100;
        }
        
        totalTime += runnersTimes[i];
        }
    
        averageTime = totalTime / 7;
        for (int i = 0; i < 7; i++) {
            runnersScores[i] = calculateScore(runnersTimes[i], meetNumber, averageTime);
        }
    
        cout << "\n============================\n";
        cout << Schedule[meetNumber] << " Results\n";
        cout << "============================\n";
    
        for (int i = 0; i < 7; i++) {
            cout << runners[i].name << ": "
                 << runnersTimes[i] / 60 << ":"
                 << setfill('0') << setw(2) << runnersTimes[i] % 60
                 << setfill(' ')
                 << " | Score: " << runnersScores[i] << endl;
        }
    
        for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 7; j++) {
            if (runnersScores[j] < runnersScores[i]) {
                int temp = runnersScores[i];
                runnersScores[i] = runnersScores[j];
                runnersScores[j] = temp;
            }
        }
        nationalComparison(runnersTimes, division, meetNumber);
    }
    
    int teamScore = 0;
    
    for (int i = 0; i < 5; i++) {
        teamScore += runnersScores[i];
    }
    
    cout << "\nTeam Score: " << teamScore << endl;
    if (teamScore < 300) {
    cout << "Team Performance: Excellent\n";
    }
    else if (teamScore < 500) {
        cout << "Team Performance: Great\n";
    }
    else if (teamScore < 750) {
        cout << "Team Performance: Good\n";
    }
    else if (teamScore < 1000) {
        cout << "Team Performance: Average\n";
    }
    else {
        cout << "Team Performance: Needs Improvement\n";
    }
    
    cout << "Average Team Time: "
         << averageTime / 60 << ":"
         << setfill('0') << setw(2) << averageTime % 60
         << setfill(' ') << endl;
}

int calculateScore(int time, int meetNumber, int averageTime) {
    
    if (meetNumber == 0) {
    simulateOpponents(markCovertTeams, 4);
    }

    if (meetNumber == 0) {
    cout << "\nOPPOSING TEAM PERFORMANCES\n";

        for (int i = 0; i < 4; i++) {
            int minutes = markCovertTeams[i].raceTime / 60;
            int seconds = markCovertTeams[i].raceTime % 60;
    
            cout << markCovertTeams[i].name << ": "
                 << minutes << ":"
                 << setfill('0') << setw(2) << seconds
                 << setfill(' ') << "\n";
        }
    }
    
    if (meetNumber == 0) {
        if (time <= MarkCovertTimes[0]) {
            return MarkCovertScores[0];
        }

        for (int i = 1; i < 9; i++) {
            if (time <= MarkCovertTimes[i]) {
                double fraction = double(time - MarkCovertTimes[i - 1])
                                / (MarkCovertTimes[i] - MarkCovertTimes[i - 1]);
                return static_cast<int>(round(MarkCovertScores[i - 1]
                       + fraction * (MarkCovertScores[i] - MarkCovertScores[i - 1])));
            }
        }
        return MarkCovertScores[8];
        
    } else if (meetNumber == 1) {
        int lower = -1;
        int upper = -1;

        for (int i = 0; i < 25; i++) {
            if (UCRTimes[i] <= time &&
                (lower == -1 || UCRTimes[i] > UCRTimes[lower])) {
                lower = i;
            }
            if (UCRTimes[i] >= time &&
                (upper == -1 || UCRTimes[i] < UCRTimes[upper])) {
                upper = i;
            }
        }

        if (lower == -1) return UCRScores[upper];
        if (upper == -1) return UCRScores[lower];
        if (lower == upper || UCRTimes[lower] == UCRTimes[upper])
            return UCRScores[lower];

        double fraction = double(time - UCRTimes[lower])
                        / (UCRTimes[upper] - UCRTimes[lower]);
        return static_cast<int>(round(UCRScores[lower]
               + fraction * (UCRScores[upper] - UCRScores[lower])));
    }

    else if (meetNumber == 2) {
    int lower = -1;
    int upper = -1;

    for (int i = 0; i < 27; i++) {
        if (LewisTimes[i] <= time &&
            (lower == -1 || LewisTimes[i] > LewisTimes[lower])) {
            lower = i;
        }

        if (LewisTimes[i] >= time &&
            (upper == -1 || LewisTimes[i] < LewisTimes[upper])) {
            upper = i;
        }
    }

    if (lower == -1) return LewisScores[upper];
    if (upper == -1) return LewisScores[lower];

    if (LewisTimes[lower] == LewisTimes[upper])
        return LewisScores[lower];

    double fraction = double(time - LewisTimes[lower])
                    / (LewisTimes[upper] - LewisTimes[lower]);

    return static_cast<int>(round(
        LewisScores[lower] +
        fraction * (LewisScores[upper] - LewisScores[lower])
    ));
    }
        
    else if (meetNumber == 3) {
    int lower = -1;
    int upper = -1;

    for (int i = 0; i < 16; i++) {
        if (HighlanderTimes[i] <= time &&
            (lower == -1 || HighlanderTimes[i] > HighlanderTimes[lower])) {
            lower = i;
        }

        if (HighlanderTimes[i] >= time &&
            (upper == -1 || HighlanderTimes[i] < HighlanderTimes[upper])) {
            upper = i;
        }
    }

    if (lower == -1) return HighlanderScores[upper];
    if (upper == -1) return HighlanderScores[lower];

    if (HighlanderTimes[lower] == HighlanderTimes[upper])
        return HighlanderScores[lower];

    double fraction = double(time - HighlanderTimes[lower])
                    / (HighlanderTimes[upper] - HighlanderTimes[lower]);

    return static_cast<int>(round(
        HighlanderScores[lower] +
        fraction * (HighlanderScores[upper] - HighlanderScores[lower])
    ));
    }

    else if (meetNumber == 4) {
    if (time <= ConferenceTimes[0]) {
        return ConferenceScores[0];
    }

    for (int i = 1; i < 10; i++) {
        if (time <= ConferenceTimes[i]) {
            double fraction = double(time - ConferenceTimes[i - 1])
                            / (ConferenceTimes[i] - ConferenceTimes[i - 1]);

            return static_cast<int>(round(
                ConferenceScores[i - 1] +
                fraction * (ConferenceScores[i] - ConferenceScores[i - 1])
            ));
        }
    }
    return ConferenceScores[9];
    }

    else if (meetNumber == 5) {
    int lower = -1;
    int upper = -1;

    for (int i = 0; i < 23; i++) {
        if (RegionalTimes[i] <= time &&
            (lower == -1 || RegionalTimes[i] > RegionalTimes[lower])) {
            lower = i;
        }

        if (RegionalTimes[i] >= time &&
            (upper == -1 || RegionalTimes[i] < RegionalTimes[upper])) {
            upper = i;
        }
    }

    if (lower == -1) return RegionalScores[upper];
    if (upper == -1) return RegionalScores[lower];

    if (RegionalTimes[lower] == RegionalTimes[upper])
        return RegionalScores[lower];

    double fraction = double(time - RegionalTimes[lower])
                    / (RegionalTimes[upper] - RegionalTimes[lower]);

    return static_cast<int>(round(
        RegionalScores[lower] +
        fraction * (RegionalScores[upper] - RegionalScores[lower])
    ));
    }

    else if (meetNumber == 6) {
    int lower = -1;
    int upper = -1;

    for (int i = 0; i < 34; i++) {
        if (NationalsTimes[i] <= time &&
            (lower == -1 || NationalsTimes[i] > NationalsTimes[lower])) {
            lower = i;
        }

        if (NationalsTimes[i] >= time &&
            (upper == -1 || NationalsTimes[i] < NationalsTimes[upper])) {
            upper = i;
        }
    }

    if (lower == -1) return NationalsScores[upper];
    if (upper == -1) return NationalsScores[lower];

    if (NationalsTimes[lower] == NationalsTimes[upper])
        return NationalsScores[lower];

    double fraction = double(time - NationalsTimes[lower])
                    / (NationalsTimes[upper] - NationalsTimes[lower]);

    return static_cast<int>(round(
        NationalsScores[lower] +
        fraction * (NationalsScores[upper] - NationalsScores[lower])
    ));
    }
    
    return 0;
}

void nationalComparison(int runnersTimes[], int division, int meetNumber) {
    int times[7];

    // Convert all performances to 8K times
    for (int i = 0; i < 7; i++) {
        if (meetNumber >= 5) {
            times[i] = round(runnersTimes[i] / 1.27);
        }
        else {
            times[i] = runnersTimes[i];
        }
    }

    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 7; j++) {
            if (times[j] < times[i]) {
                int temp = times[i];
                times[i] = times[j];
                times[j] = temp;
            }
        }
    }

    int total = 0;

    for (int i = 0; i < 5; i++) {
        total += times[i];
    }

    double teamAverage = total / 5.0;

    // Select the national benchmarks
    const double* nationalTimes;
    const string* nationalTeams;

    if (division == 1) {
        nationalTimes = D3NationalAverage;
        nationalTeams = D3NationalTeams;
    }
    else if (division == 2) {
        nationalTimes = D2NationalAverage;
        nationalTeams = D2NationalTeams;
    }
    else {
        nationalTimes = D1NationalAverage;
        nationalTeams = D1NationalTeams;
    }

    cout << "\nNATIONAL PERFORMANCE COMPARISON\n";

    cout << "Your Team: "
         << int(teamAverage) / 60 << ":"
         << fixed << setprecision(1)
         << fmod(teamAverage, 60.0) << "\n";

    for (int i = 0; i < 3; i++) {
        double difference = teamAverage - nationalTimes[i];

        cout << nationalTeams[i] << ": ";

        if (difference > 0) {
            cout << fixed << setprecision(1)
                 << difference << " seconds behind\n";
        }
        else {
            cout << fixed << setprecision(1)
                 << -difference << " seconds ahead\n";
        }
    }
}

void simulateOpponents(OpposingTeam teams[], int teamCount) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> variation(-15, 15);

    for (int i = 0; i < teamCount; i++) {
        teams[i].raceTime = teams[i].averageTime + variation(gen);
    }
}

int calculatePlacement(int runnersTimes[], OpposingTeam teams[], int teamCount) {
    int times[7];

    for (int i = 0; i < 7; i++) {
        times[i] = runnersTimes[i];
    }
    
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 7; j++) {
            if (times[j] < times[i]) {
                int temp = times[i];
                times[i] = times[j];
                times[j] = temp;
            }
        }
    }

    int total = 0;

    for (int i = 0; i < 5; i++) {
        total += times[i];
    }

    double teamAverage = total / 5.0;

    int placement = 1;

    for (int i = 0; i < teamCount; i++) {
        if (teams[i].raceTime < teamAverage) {
            placement++;
        }
    }

    return placement;
}
