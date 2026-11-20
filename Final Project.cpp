#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>
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
    { "Cal State Fullerton", 1510, 0, 0 },
    { "UC Irvine", 1490, 0, 0 },
    { "Concordia Irvine", 1540, 0, 0 },
    { "Azusa Pacific", 1550, 0, 0 }
};

void getName(string& name, int number);
int startScore(int difficulty);
void chooseWorkout(string& workout, int number);
void applyWorkout(Runner& runner, string workout);
int chooseDivision();
RunnerStats generateRunnerStats(int difficulty);
void schedule(Runner runners[], int division);
int calc8kTime(const RunnerStats& stats);
int calc10kTime(const RunnerStats& stats);
void runMeet(Runner runners[], int meetNumber, int division);
int calculateScore(int time, int meetNumber, int averageTime);
void nationalComparison(const int runnersTimes[], int division, int meetNumber);
void simulateOpponents(OpposingTeam teams[], int teamCount);
int calculatePlacement(const int runnersTimes[], const OpposingTeam teams[], int teamCount);
void printTime(double seconds);
int interpolateScore(int time, const int times[], const int scores[], int count);

const int UCRTimes[25] = { 1437,1447,1447,1463,1445,1455,1456,1457,1465,1466,1465,1467,1471,1472,1476,1477,1483,1486,1494,1492,1500,1503,1513,1508,1524 };
const int UCRScores[25] = { 49,97,103,159,178,235,247,251,298,313,315,320,350,366,389,395,440,483,492,497,539,568,579,597,710 };
const int LewisTimes[27] = { 1487,1489,1491,1494,1495,1495,1502,1509,1516,1522,1529,1525,1542,1546,1545,1546,1551,1554,1557,1561,1585,1585,1600,1607,1607,1638,1655 };
const int LewisScores[27] = { 114,120,130,137,141,155,195,214,260,296,308,319,381,409,411,413,426,462,475,506,596,609,663,677,697,762,845 };
const int MarkCovertTimes[9] = { 1528,1531,1535,1541,1560,1578,1612,1636,1655 };
const int MarkCovertScores[9] = { 54,59,68,92,119,153,200,224,240 };
const int HighlanderTimes[16] = { 1459,1468,1469,1472,1473,1476,1479,1477,1485,1484,1486,1485,1500,1516,1531,1559 };
const int HighlanderScores[16] = { 76,124,131,151,154,177,192,199,215,219,221,224,286,374,390,487 };
const int ConferenceTimes[10] = { 1509,1525,1527,1540,1581,1660,1707,1830,1950,2021 };
const int ConferenceScores[10] = { 35,53,57,72,130,179,202,252,262,280 };
const int RegionalTimes[23] = { 1810,1817,1819,1828,1837,1857,1861,1867,1892,1894,1899,1903,1906,1910,1921,1933,1929,1930,1947,1960,1991,2010,2055 };
const int RegionalScores[23] = { 75,88,97,126,141,190,206,223,299,304,317,324,338,346,379,402,402,425,455,493,599,642,695 };
const int NationalsTimes[34] = { 1810,1811,1827,1828,1841,1862,1873,1879,1884,1885,1880,1884,1891,1884,1894,1895,1903,1905,1913,1909,1916,1912,1917,1922,1926,1927,1937,1935,1937,1942,1947,1947,1997,2064 };
const int NationalsScores[34] = { 62,71,121,122,162,261,310,338,373,375,380,390,394,430,431,456,490,500,518,541,543,554,560,582,640,644,664,670,695,737,770,770,980,1096 };

const string Schedule[7] = {
    "Mark Covert",
    "UCR",
    "Lewis Invitational",
    "Highlander Invitational",
    "Conference",
    "Regionals",
    "Nationals"
};

const string D1NationalTeams[3] = {
    "Alabama",
    "New Mexico",
    "Arkansas"
};

const double D1NationalAverage[3] = {
    1345.8,
    1369.2,
    1368.3
};

const string D2NationalTeams[3] = {
    "Adams State",
    "Colorado School of Mines",
    "West Texas A&M"
};

const double D2NationalAverage[3] = {
    1396.5,
    1399.5,
    1404.4
};

const string D3NationalTeams[3] = {
    "MIT",
    "SUNY Geneseo",
    "UW-La Crosse"
};

const double D3NationalAverage[3] = {
    1447.1,
    1452.3,
    1459.7
};

int main() {
    cout << "============================\n";
    cout << "       XC MANAGEMENT\n";
    cout << "============================\n";

    cout << "\n1. Start New Season\n";
    cout << "2. Quit Game\n";

    int choice;
    cout << "\nEnter your choice: ";
    if (!(cin >> choice)) return 0;

    if (choice == 2) {
        cout << "\nThanks for playing!\n";
        return 0;
    }

    if (choice != 1) {
        cout << "\nInvalid choice. Please restart the game.\n";
        return 0;
    }

    int division = chooseDivision();

    if (division < 1 || division > 3) {
        cout << "\nInvalid division choice.\n";
        return 0;
    }

    int difficulty = 4 - division;

    if (division == 1) {
        cout << "\nYou selected Division III.\n";
    }
    else if (division == 2) {
        cout << "\nYou selected Division II.\n";
    }
    else {
        cout << "\nYou selected Division I.\n";
    }

    Runner runners[7];

    for (int i = 0; i < 7; i++) {
        getName(runners[i].name, i + 1);

        int score = startScore(difficulty);

        runners[i].stats = generateRunnerStats(difficulty);
        runners[i].workout = "";

        cout << runners[i].name
            << " has a starting score of "
            << score << "\n";

        cout << "Endurance: " << runners[i].stats.endurance
            << ", Speed: " << runners[i].stats.speed
            << ", Fatigue: " << runners[i].stats.fatigue
            << "\n";
    }

    schedule(runners, division);

    return 0;
}

int chooseDivision() {
    int division;

    cout << "\nChoose Your Division\n";
    cout << "1. Division III (Easy)\n";
    cout << "2. Division II (Medium)\n";
    cout << "3. Division I (Hard)\n";

    cout << "\nEnter your division: ";

    if (!(cin >> division)) return 0;

    return division;
}

int startScore(int difficulty) {
    random_device rd;
    mt19937 gen(rd());

    int minScore = 1;
    int maxScore = 100;

    if (difficulty == 3) {
        minScore = 60;
        maxScore = 85;
    }
    else if (difficulty == 2) {
        minScore = 45;
        maxScore = 75;
    }
    else if (difficulty == 1) {
        minScore = 30;
        maxScore = 65;
    }

    uniform_int_distribution<int> distribution(minScore, maxScore);

    return distribution(gen);
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

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = 0;
    }

    if (choice == 1) workout = "Steady State";
    else if (choice == 2) workout = "Mile Repeats";
    else if (choice == 3) workout = "The Eagle";
    else if (choice == 4) workout = "Hill Repeats";
    else if (choice == 5) workout = "2k Repeats";
    else if (choice == 6) workout = "Premeet";
    else workout = "Rest";

    cout << "\nSelected workout: " << workout << "\n";
}



void applyWorkout(Runner& runner, string workout) {
    runner.workout = workout;

    if (workout == "Steady State") {
        runner.stats.endurance += 2;
        runner.stats.fatigue += 3;
    }
    else if (workout == "Mile Repeats") {
        runner.stats.speed += 2;
        runner.stats.fatigue += 4;
    }
    else if (workout == "The Eagle") {
        runner.stats.endurance += 2;
        runner.stats.speed += 2;
        runner.stats.fatigue += 9;
    }
    else if (workout == "Hill Repeats") {
        runner.stats.endurance += 3;
        runner.stats.fatigue += 7;
    }
    else if (workout == "2k Repeats") {
        runner.stats.endurance += 1;
        runner.stats.speed += 2;
        runner.stats.fatigue += 6;
    }
    else if (workout == "Premeet") {
        runner.stats.fatigue -= 7;
    }
    else if (workout == "Rest") {
        runner.stats.fatigue -= 15;
    }

    runner.stats.endurance = clamp(runner.stats.endurance, 0, 100);
    runner.stats.speed = clamp(runner.stats.speed, 0, 100);
    runner.stats.fatigue = clamp(runner.stats.fatigue, 0, 100);
}


void getName(string& name, int number) {
    cout << "Enter the name for runner " << number << ": ";
    getline(cin >> ws, name);
}

RunnerStats generateRunnerStats(int difficulty) {
    random_device rd;
    mt19937 gen(rd());

    int enduranceMin, enduranceMax;
    int speedMin, speedMax;
    int fatigueMin, fatigueMax;

    if (difficulty == 3) {
        // Division III
        enduranceMin = 45;
        enduranceMax = 65;
        speedMin = 40;
        speedMax = 60;
        fatigueMin = 25;
        fatigueMax = 45;
    }
    else if (difficulty == 2) {
        // Division II
        enduranceMin = 50;
        enduranceMax = 70;
        speedMin = 45;
        speedMax = 65;
        fatigueMin = 20;
        fatigueMax = 40;
    }
    else {
        // Division I
        enduranceMin = 55;
        enduranceMax = 75;
        speedMin = 50;
        speedMax = 70;
        fatigueMin = 15;
        fatigueMax = 35;
    }

    uniform_int_distribution<int> enduranceDist(enduranceMin, enduranceMax);
    uniform_int_distribution<int> speedDist(speedMin, speedMax);
    uniform_int_distribution<int> fatigueDist(fatigueMin, fatigueMax);

    RunnerStats stats;

    stats.endurance = enduranceDist(gen);
    stats.speed = speedDist(gen);
    stats.fatigue = fatigueDist(gen);

    return stats;

}

void schedule(Runner runner[], int division) {
    int meetCount = 0;
    string workoutChoice;

    for (int week = 1; week <= 16; week++) {
        cout << "\nWelcome to week " << week;
        cout << ". These are the current stats of the runners:\n";

        for (int j = 0; j < 7; j++) {
            cout << runner[j].name << ":\n";

            cout << "Endurance: " << runner[j].stats.endurance
                << ", Speed: " << runner[j].stats.speed
                << ", Fatigue: " << runner[j].stats.fatigue
                << "\n";
        }

        for (int a = 1; a <= 2; a++) {
            chooseWorkout(workoutChoice, a);

            for (int b = 0; b < 7; b++) {
                applyWorkout(runner[b], workoutChoice);
            }
        }

        if (week == 3 || week == 5 || week == 8 ||
            week == 9 || week == 12 || week == 14 ||
            week == 16) {

            runMeet(runner, meetCount, division);
            meetCount++;
        }

        for (int j = 0; j < 7; j++) {
            runner[j].stats.fatigue -= 3;

            if (runner[j].stats.fatigue < 0) {
                runner[j].stats.fatigue = 0;
            }
        }
    }
}

int calc8kTime(const RunnerStats& stats) {
    double time = 1700.0
        - 2.0 * stats.endurance
        - 1.2 * stats.speed
        + 1.2 * stats.fatigue;

    return static_cast<int>(round(time));
}

int calc10kTime(const RunnerStats& stats) {
    int time8k = calc8kTime(stats);

    return static_cast<int>(round(time8k * 1.27));
}

void printTime(double seconds) {
    int tenths = static_cast<int>(round(seconds * 10));

    cout << tenths / 600 << ":"
        << setfill('0') << setw(2) << (tenths / 10) % 60
        << "." << tenths % 10
        << setfill(' ');
}

void runMeet(Runner runners[], int meetNumber, int division) {
    int runnersTimes[7];
    int runnersScores[7];
    int totalTime = 0;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> raceVariation(-15, 15);

    for (int i = 0; i < 7; i++) {
        if (meetNumber >= 5) {
            runnersTimes[i] = calc10kTime(runners[i].stats);
        }
        else {
            runnersTimes[i] = calc8kTime(runners[i].stats);
        }

        runnersTimes[i] += raceVariation(gen);

        runners[i].stats.fatigue += 8;

        if (runners[i].stats.fatigue > 100) {
            runners[i].stats.fatigue = 100;
        }

        totalTime += runnersTimes[i];
    }

    int averageTime = totalTime / 7;

    for (int i = 0; i < 7; i++) {
        runnersScores[i] = calculateScore(
            runnersTimes[i], meetNumber, averageTime
        );
    }

    cout << "\n============================\n";
    cout << Schedule[meetNumber] << " Results\n";
    cout << "============================\n";

    for (int i = 0; i < 7; i++) {
        cout << runners[i].name << ": ";
        printTime(runnersTimes[i]);

        cout << " | Historical score estimate: "
            << runnersScores[i] << "\n";
    }

    int sortedScores[7];

    for (int i = 0; i < 7; i++) {
        sortedScores[i] = runnersScores[i];
    }

    sort(sortedScores, sortedScores + 7);

    int teamScore = 0;

    for (int i = 0; i < 5; i++) {
        teamScore += sortedScores[i];
    }

    cout << "\nHistorical Team Score Estimate: "
        << teamScore << "\n";

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

    cout << "Average Team Time (all 7): ";
    printTime(totalTime / 7.0);
    cout << "\n";

    // Mark Covert opposing team simulation
    if (meetNumber == 0) {
        simulateOpponents(markCovertTeams, 4);

        cout << "\nOPPOSING TEAM PERFORMANCES ";
        cout << "(TOP-FIVE AVERAGES)\n";

        for (int i = 0; i < 4; i++) {
            cout << markCovertTeams[i].name << ": ";
            printTime(markCovertTeams[i].raceTime);
            cout << "\n";
        }

        int placement = calculatePlacement(
            runnersTimes, markCovertTeams, 4
        );

        cout << "\nESTIMATED TEAM PLACEMENT: "
            << placement << " out of 5 teams\n";

        cout << "(Based on top-five average times, ";
        cout << "not official XC scoring.)\n";
    }

    nationalComparison(runnersTimes, division, meetNumber);
}

int interpolateScore(int time, const int times[],
    const int scores[], int count) {

    int lower = -1;
    int upper = -1;

    for (int i = 0; i < count; i++) {
        if (times[i] <= time &&
            (lower == -1 || times[i] > times[lower])) {
            lower = i;
        }

        if (times[i] >= time &&
            (upper == -1 || times[i] < times[upper])) {
            upper = i;
        }
    }

    if (lower == -1) {
        return scores[upper];
    }

    if (upper == -1) {
        return scores[lower];
    }

    if (times[lower] == times[upper]) {
        return scores[lower];
    }

    double fraction = double(time - times[lower])
        / (times[upper] - times[lower]);

    return static_cast<int>(round(
        scores[lower] +
        fraction * (scores[upper] - scores[lower])
    ));
}

int calculateScore(int time, int meetNumber, int averageTime) {
    // Reserved for future scoring adjustments
    (void)averageTime;

    if (meetNumber == 0) {
        return interpolateScore(
            time, MarkCovertTimes, MarkCovertScores, 9
        );
    }
    else if (meetNumber == 1) {
        return interpolateScore(
            time, UCRTimes, UCRScores, 25
        );
    }
    else if (meetNumber == 2) {
        return interpolateScore(
            time, LewisTimes, LewisScores, 27
        );
    }
    else if (meetNumber == 3) {
        return interpolateScore(
            time, HighlanderTimes, HighlanderScores, 16
        );
    }
    else if (meetNumber == 4) {
        return interpolateScore(
            time, ConferenceTimes, ConferenceScores, 10
        );
    }
    else if (meetNumber == 5) {
        return interpolateScore(
            time, RegionalTimes, RegionalScores, 23
        );
    }
    else if (meetNumber == 6) {
        return interpolateScore(
            time, NationalsTimes, NationalsScores, 34
        );
    }

    return 0;
}

void nationalComparison(const int runnersTimes[],
    int division, int meetNumber) {

    int times[7];

    // Convert 10K performances to 8K equivalents
    for (int i = 0; i < 7; i++) {
        if (meetNumber >= 5) {
            times[i] = static_cast<int>(
                round(runnersTimes[i] / 1.27)
                );
        }
        else {
            times[i] = runnersTimes[i];
        }
    }

    sort(times, times + 7);

    int total = 0;

    for (int i = 0; i < 5; i++) {
        total += times[i];
    }

    double teamAverage = total / 5.0;

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

    cout << "\nNATIONAL PERFORMANCE COMPARISON ";
    cout << "(8K EQUIVALENT)\n";

    cout << "Your Team: ";
    printTime(teamAverage);
    cout << "\n";

    for (int i = 0; i < 3; i++) {
        double difference = teamAverage - nationalTimes[i];

        cout << nationalTeams[i] << " (";
        printTime(nationalTimes[i]);
        cout << "): ";

        cout << fixed << setprecision(1)
            << abs(difference) << " seconds ";

        if (difference > 0) {
            cout << "behind\n";
        }
        else if (difference < 0) {
            cout << "ahead\n";
        }
        else {
            cout << "equal\n";
        }
    }
}

void simulateOpponents(OpposingTeam teams[], int teamCount) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> variation(-15, 15);

    for (int i = 0; i < teamCount; i++) {
        teams[i].raceTime =
            teams[i].averageTime + variation(gen);
    }
}

int calculatePlacement(const int runnersTimes[],
    const OpposingTeam teams[],
    int teamCount) {

    int times[7];

    for (int i = 0; i < 7; i++) {
        times[i] = runnersTimes[i];
    }

    sort(times, times + 7);

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
