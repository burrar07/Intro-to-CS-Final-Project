#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>
#include <vector>

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
};

struct RaceFinisher {
    string team;
    string runner;
    int time;
    int place;
};

// ========================================================================
// MEET AND NATIONAL REFERENCE DATA
// ========================================================================
const string Schedule[7] = {
    "Mark Covert",
    "UCR",
    "Lewis Invitational",
    "Highlander Invitational",
    "Conference",
    "Regionals",
    "Nationals"
};

const int courseDifficulty[7] = {
    2, 1, 3, 3, 4, 4, 5
};

const int courseTimeAdjustment[7] = {
    10,   // Mark Covert
    -10,  // UCR
    30,   // Lewis Invitational
    -10,  // Highlander Invitational
    25,   // Conference
    35,   // Regionals
    45    // Nationals
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

// ========================================================================
// FUNCTION DECLARATIONS
// ========================================================================
int chooseDivision();
void getName(string& name, int number);
int startScore(int difficulty);
RunnerStats generateRunnerStats(int difficulty);
void chooseWorkout(string& workout, int number);
void applyWorkout(Runner& runner, string workout);
void schedule(Runner runners[], int division);
void seasonMenu(const Runner runners[], int division, int week);
void showRunnerStats(const Runner runners[]);
void showWorkoutInfo();
void showSeasonSchedule(int currentWeek);
void showNextRace(int currentWeek);
void showNationalProjection(const Runner runners[], int division);
void advanceWeekMenu(const Runner runners[], int division, int week);
int calc8kTime(const RunnerStats& stats);
int calc10kTime(const RunnerStats& stats);
int calculateCourseEffect(const RunnerStats& stats, int meetNumber);
void printTime(double seconds);
void runMeet(Runner runners[], int meetNumber, int division);
vector<OpposingTeam> selectOpponents(int meetNumber, int division);
void calculateXCResults(const int runnersTimes[], const Runner runners[], vector<OpposingTeam>& teams, int meetNumber);
void nationalComparison(const int runnersTimes[], int division, int meetNumber);

// ========================================================================
// GAME SETUP
// ========================================================================
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

void getName(string& name, int number) {
    cout << "Enter the name for runner " << number << ": ";
    getline(cin >> ws, name);
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

// ========================================================================
// TRAINING
// ========================================================================
void chooseWorkout(string& workout, int number) {
    int choice;

    cout << "\nChoose workout #" << number << " for the week:\n";
    cout << "1. Steady State\n";
    cout << "2. Mile Repeats\n";
    cout << "3. The Eagle\n";
    cout << "4. Hill Repeats\n";
    cout << "5. 2k Repeats\n";
    cout << "6. Premeet\n";
    cout << "7. Rest\n";

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
    else if (choice == 7) workout = "Rest";
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

// ========================================================================
// SEASON SCHEDULE
// ========================================================================
// Weeks in which the seven meets take place.
const int meetWeeks[7] = {3, 5, 8, 9, 12, 14, 16};

void showRunnerStats(const Runner runners[]) {
    cout << "\n========== RUNNER STATS ==========\n";
    for (int i = 0; i < 7; i++) {
        cout << i + 1 << ". " << runners[i].name
             << " | Endurance: " << runners[i].stats.endurance
             << " | Speed: " << runners[i].stats.speed
             << " | Fatigue: " << runners[i].stats.fatigue << "\n";
    }
}

void showWorkoutInfo() {
    cout << "\n========== WORKOUT GUIDE ==========\n";
    cout << "1. Steady State: +2 endurance, +3 fatigue\n";
    cout << "2. Mile Repeats: +2 speed, +4 fatigue\n";
    cout << "3. The Eagle: +2 endurance, +2 speed, +9 fatigue\n";
    cout << "4. Hill Repeats: +3 endurance, +7 fatigue\n";
    cout << "5. 2k Repeats: +1 endurance, +2 speed, +6 fatigue\n";
    cout << "6. Premeet: -7 fatigue\n";
    cout << "7. Rest: -15 fatigue\n";
    cout << "Stats are limited to the range 0-100.\n";
    cout << "You choose two workouts each week for the entire team.\n";
}

void showSeasonSchedule(int currentWeek) {
    cout << "\n========== FULL SEASON SCHEDULE ==========\n";
    for (int i = 0; i < 7; i++) {
        cout << "Week " << setw(2) << meetWeeks[i] << ": " << Schedule[i];
        if (meetWeeks[i] < currentWeek) cout << " (completed)";
        else if (meetWeeks[i] == currentWeek) cout << " (this week)";
        cout << "\n";
    }
    cout << "All other weeks are training weeks.\n";
}

void showNextRace(int currentWeek) {
    cout << "\n========== NEXT RACE ==========\n";
    for (int i = 0; i < 7; i++) {
        if (meetWeeks[i] >= currentWeek) {
            int weeksAway = meetWeeks[i] - currentWeek;
            cout << Schedule[i] << " (Week " << meetWeeks[i] << ")\n";
            if (weeksAway == 0) cout << "Your race is THIS WEEK, after training!\n";
            else cout << weeksAway << " week(s) until race week.\n";
            return;
        }
    }
    cout << "All races are finished.\n";
}

void showNationalProjection(const Runner runners[], int division) {
    int projectedTimes[7];
    cout << "\n========== NATIONAL PROJECTION ==========\n";
    cout << "Based on current runner stats, assuming a neutral 8K course.\n";
    cout << "No random race variation is included.\n";
    for (int i = 0; i < 7; i++) {
        projectedTimes[i] = calc8kTime(runners[i].stats);
    }
    // The comparison function uses 8K times when meetNumber is below 5.
    nationalComparison(projectedTimes, division, 0);
}

void seasonMenu(const Runner runners[], int division, int week) {
    int choice = 0;
    while (choice != 5) {
        cout << "\n========== WEEK " << week << " MENU ==========\n";
        showNextRace(week);
        cout << "1. View national projection\n";
        cout << "2. View runner stats\n";
        cout << "3. Workout information\n";
        cout << "4. Full season schedule\n";
        cout << "5. Continue to this week's training\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            if (cin.eof()) return;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        if (choice == 1) showNationalProjection(runners, division);
        else if (choice == 2) showRunnerStats(runners);
        else if (choice == 3) showWorkoutInfo();
        else if (choice == 4) showSeasonSchedule(week);
        else if (choice != 5) cout << "Invalid option. Please choose 1-5.\n";
    }
}

// Review the team after workouts and racing before advancing.
void advanceWeekMenu(const Runner runners[], int division, int week) {
    while (true) {
        cout << "\n========== END OF WEEK " << week << " ==========\n";
        cout << "1. Review runner stats\n";
        cout << "2. Review national projection\n";
        cout << "3. Advance to next week\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) return;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option.\n";
            continue;
        }

        if (choice == 1) showRunnerStats(runners);
        else if (choice == 2) showNationalProjection(runners, division);
        else if (choice == 3) return;
        else cout << "Invalid option. Please choose 1-3.\n";
    }
}

void schedule(Runner runners[], int division) {
    int meetCount = 0;
    string workoutChoice;

    for (int week = 1; week <= 16; week++) {
        seasonMenu(runners, division, week);
        if (!cin) return;

        for (int workoutNumber = 1; workoutNumber <= 2; workoutNumber++) {
            chooseWorkout(workoutChoice, workoutNumber);
            if (!cin) return;
            for (int i = 0; i < 7; i++) {
                applyWorkout(runners[i], workoutChoice);
            }
        }

        if (meetCount < 7 && week == meetWeeks[meetCount]) {
            runMeet(runners, meetCount, division);
            meetCount++;
        }

        for (int i = 0; i < 7; i++) {
            runners[i].stats.fatigue = max(0, runners[i].stats.fatigue - 3);
        }

        if (week < 16) {
            advanceWeekMenu(runners, division, week);
            if (!cin) return;
        }
    }

    cout << "\nSeason complete! Thanks for playing.\n";
}

// ========================================================================
// RACE TIME CALCULATIONS
// ========================================================================
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

int calculateCourseEffect(const RunnerStats& stats, int meetNumber) {
    int adjustment = courseTimeAdjustment[meetNumber];

    // Endurance helps runners handle difficult courses.
    if (courseDifficulty[meetNumber] >= 3) {
        adjustment -= (stats.endurance - 50) / 5;
    }

    return adjustment;
}

void printTime(double seconds) {
    int tenths = static_cast<int>(round(seconds * 10));

    cout << tenths / 600 << ":"
        << setfill('0') << setw(2) << (tenths / 10) % 60
        << "." << tenths % 10
        << setfill(' ');
}

// ========================================================================
// MEET SIMULATION
// ========================================================================
void runMeet(Runner runners[], int meetNumber, int division) {
    int runnersTimes[7];
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

        runnersTimes[i] += calculateCourseEffect(runners[i].stats, meetNumber);
        runnersTimes[i] += raceVariation(gen);

        runners[i].stats.fatigue += 8;

        if (runners[i].stats.fatigue > 100) {
            runners[i].stats.fatigue = 100;
        }

        totalTime += runnersTimes[i];
    }

    cout << "\n============================\n";
    cout << Schedule[meetNumber] << " Results\n";
    cout << "Course Difficulty: "
         << courseDifficulty[meetNumber] << "/5\n";
    cout << "============================\n";

    for (int i = 0; i < 7; i++) {
        cout << runners[i].name << ": ";
        printTime(runnersTimes[i]);
        cout << "\n";
    }

    cout << "Average Team Time (all 7): ";
    printTime(totalTime / 7.0);
    cout << "\n";

    vector<OpposingTeam> teams = selectOpponents(meetNumber, division);
    
    calculateXCResults(runnersTimes, runners, teams, meetNumber);
        
    nationalComparison(runnersTimes, division, meetNumber);
}

vector<OpposingTeam> selectOpponents(int meetNumber, int division) {
    vector<string> names;

    if (meetNumber == 0) {
        names = {
            "Cal State Fullerton",
            "UC Irvine",
            "Cal Poly Pomona",
            "Concordia Irvine",
            "Azusa Pacific",
            "Westmont",
            "Cal State LA",
            "Vanguard",
            "Chapman"
        };
    }
    else if (meetNumber == 1) {
        names = {
            "Cal Poly SLO",
            "UC Davis",
            "UC Irvine",
            "UC Riverside",
            "UC San Diego",
            "UCLA",
            "Chico State",
            "Cal Poly Pomona",
            "Cal State Fullerton",
            "Long Beach State",
            "Cal State San Marcos",
            "Pepperdine",
            "Loyola Marymount",
            "San Diego",
            "Concordia Irvine",
            "Westmont",
            "Vanguard",
            "USC",
            "San Diego State"
        };
    }
    else if (meetNumber == 2) {
        names = {
            "Grand Valley State",
            "Lewis",
            "Augustana (SD)",
            "Minnesota State",
            "Michigan Tech",
            "Saginaw Valley State",
            "Cedarville",
            "Walsh",
            "Hillsdale",
            "Indianapolis",
            "Wayne State",
            "Missouri S&T",
            "Ashland",
            "Findlay",
            "Davenport",
            "Northern Michigan",
            "Wisconsin-Parkside",
            "Ferris State",
            "Sioux Falls",
            "Truman State",
            "Drury",
            "Malone",
            "Tiffin",
            "Southern Indiana"
        };
    }
    else if (meetNumber == 3) {
        names = {
            "Cal Poly SLO",
            "UC Davis",
            "UC Irvine",
            "UC Riverside",
            "UC San Diego",
            "Chico State",
            "Cal Poly Pomona",
            "UCLA",
            "Cal State Fullerton",
            "Long Beach State",
            "Cal State San Marcos",
            "Stanislaus State",
            "Azusa Pacific",
            "Concordia Irvine",
            "Westmont",
            "Loyola Marymount",
            "Pepperdine",
            "Vanguard",
            "Cal State LA"
        };
    }
    else if (meetNumber == 4) {
        if (division == 1) {
            names = {
                "Pomona-Pitzer",
                "Claremont-Mudd-Scripps",
                "Occidental",
                "Redlands",
                "Caltech",
                "Chapman",
                "La Verne",
                "Whittier"
            };
        }
        else if (division == 2) {
            names = {
                "Westmont",
                "Concordia Irvine",
                "Vanguard",
                "Academy of Art",
                "Jessup",
                "Dominican (CA)",
                "Hawaii Pacific",
                "Chaminade"
            };
        }
        else {
            names = {
                "Cal Poly SLO",
                "UC Davis",
                "UC Irvine",
                "UC Riverside",
                "UC San Diego",
                "Cal State Fullerton",
                "Long Beach State",
                "Cal State Bakersfield",
                "Hawaii"
            };
        }
    }
    else if (meetNumber == 5) {
        if (division == 1) {
            names = {
                "Pomona-Pitzer",
                "Claremont-Mudd-Scripps",
                "George Fox",
                "UC Santa Cruz",
                "Whitworth",
                "Pacific Lutheran",
                "Willamette",
                "Lewis & Clark",
                "Whitman",
                "Occidental",
                "Redlands",
                "Caltech",
                "Chapman",
                "La Verne",
                "Whittier",
                "Linfield",
                "Pacific (OR)",
                "Puget Sound",
                "Colorado College",
                "Trinity (TX)",
                "Southwestern (TX)",
                "Texas Lutheran",
                "Hardin-Simmons",
                "McMurry"
            };
        }
        else if (division == 2) {
            names = {
                "Chico State",
                "Cal Poly Pomona",
                "Western Washington",
                "Alaska Anchorage",
                "Cal State San Marcos",
                "Western Oregon",
                "Stanislaus State",
                "Simon Fraser",
                "Northwest Nazarene",
                "Seattle Pacific",
                "Westmont",
                "Concordia Irvine",
                "Vanguard",
                "Cal State LA",
                "San Francisco State",
                "Cal Poly Humboldt",
                "Academy of Art",
                "Cal State East Bay",
                "Cal State Monterey Bay",
                "Saint Martin's",
                "Jessup",
                "Dominican (CA)",
                "Hawaii Pacific",
                "Chaminade"
            };
        }
        else {
            names = {
                "Oregon",
                "Stanford",
                "Washington",
                "Gonzaga",
                "Portland",
                "Boise State",
                "California",
                "Cal Poly SLO",
                "UC Davis",
                "Washington State",
                "Oregon State",
                "San Francisco",
                "Santa Clara",
                "UC Irvine",
                "UC Riverside",
                "UC San Diego",
                "UCLA",
                "Sacramento State",
                "Fresno State",
                "Loyola Marymount",
                "Pepperdine",
                "San Jose State",
                "Pacific",
                "USC"
            };
        }
    }
    else if (meetNumber == 6) {
        if (division == 1) {
            names = {
                "UW-La Crosse",
                "North Central (IL)",
                "MIT",
                "Pomona-Pitzer",
                "Wartburg",
                "SUNY Geneseo",
                "Johns Hopkins",
                "UW-Whitewater",
                "Williams",
                "RPI",
                "Carnegie Mellon",
                "Washington University",
                "UW-Eau Claire",
                "UW-Stout",
                "UW-Oshkosh",
                "St. Olaf",
                "Carleton",
                "Tufts",
                "Amherst",
                "Middlebury",
                "Colby",
                "Bates",
                "Haverford",
                "Dickinson",
                "Lynchburg",
                "Emory",
                "Calvin",
                "Hope",
                "George Fox",
                "Claremont-Mudd-Scripps",
                "Case Western Reserve"
            };
        }
        else if (division == 2) {
            names = {
                "Adams State",
                "Colorado School of Mines",
                "Grand Valley State",
                "Western Colorado",
                "West Texas A&M",
                "Wingate",
                "Chico State",
                "Colorado Christian",
                "Lee",
                "UCCS",
                "CSU Pueblo",
                "Cal Poly Pomona",
                "Western Washington",
                "Lewis",
                "Augustana (SD)",
                "Minnesota State",
                "Michigan Tech",
                "Saginaw Valley State",
                "Missouri Southern",
                "Pittsburg State",
                "Northwest Missouri State",
                "Harding",
                "Alabama Huntsville",
                "Tampa",
                "Embry-Riddle (FL)",
                "Anderson (SC)",
                "Lenoir-Rhyne",
                "Western Oregon",
                "Alaska Anchorage",
                "Northwest Nazarene",
                "Westmont"
            };
        }
        else {
            names = {
                "Oklahoma State",
                "BYU",
                "Northern Arizona",
                "Stanford",
                "Oregon",
                "New Mexico",
                "Arkansas",
                "Wisconsin",
                "Iowa State",
                "Colorado",
                "Notre Dame",
                "North Carolina",
                "Wake Forest",
                "Alabama",
                "Tennessee",
                "Villanova",
                "Georgetown",
                "Washington",
                "Gonzaga",
                "Portland",
                "Boise State",
                "Michigan",
                "Michigan State",
                "Indiana",
                "Princeton",
                "Harvard",
                "Syracuse",
                "Virginia",
                "NC State",
                "Florida State",
                "Tulsa"
            };
        }
    }

    vector<OpposingTeam> teams;

    int fastestTime;

    if (meetNumber >= 5) {
        if (division == 1) fastestTime = 1840;
        else if (division == 2) fastestTime = 1810;
        else fastestTime = 1780;
    }
    else if (meetNumber == 4) {
        if (division == 1) fastestTime = 1480;
        else if (division == 2) fastestTime = 1450;
        else fastestTime = 1420;
    }
    else if (meetNumber == 0) fastestTime = 1490;
    else if (meetNumber == 1) fastestTime = 1425;
    else if (meetNumber == 2) fastestTime = 1450;
    else fastestTime = 1435;

    for (int i = 0; i < static_cast<int>(names.size()); i++) {
        OpposingTeam team;

        team.name = names[i];
        team.averageTime = fastestTime + i * 5;

        teams.push_back(team);
    }

    return teams;
}

// ========================================================================
// RACE RESULTS AND XC SCORING
// ========================================================================
void calculateXCResults(const int runnersTimes[], const Runner runners[],
                        vector<OpposingTeam>& teams, int meetNumber) {

    struct TeamResult {
        string name;
        int score;
        int sixthPlace;
        int seventhPlace;
    };

    vector<RaceFinisher> finishers;
    vector<TeamResult> results;

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> variation(-12, 12);

    for (int i = 0; i < 7; i++) {
        RaceFinisher finisher;

        finisher.team = "Your Team";
        finisher.runner = runners[i].name;
        finisher.time = runnersTimes[i];
        finisher.place = 0;

        finishers.push_back(finisher);
    }

    int offsets[7] = {
        -35, -20, -10, 0, 15, 30, 45
    };

    for (int i = 0; i < static_cast<int>(teams.size()); i++) {
        for (int j = 0; j < 7; j++) {
            RaceFinisher finisher;

            finisher.team = teams[i].name;
            finisher.runner = "Runner " + to_string(j + 1);

            finisher.time = teams[i].averageTime
                + offsets[j]
                + courseTimeAdjustment[meetNumber]
                + variation(gen);

            finisher.place = 0;

            finishers.push_back(finisher);
        }
    }

    sort(finishers.begin(), finishers.end(),
        [](const RaceFinisher& a, const RaceFinisher& b) {
            return a.time < b.time;
        });

    for (int i = 0; i < static_cast<int>(finishers.size()); i++) {
        finishers[i].place = i + 1;
    }

    vector<string> teamNames;
    teamNames.push_back("Your Team");

    for (int i = 0; i < static_cast<int>(teams.size()); i++) {
        teamNames.push_back(teams[i].name);
    }

    for (int i = 0; i < static_cast<int>(teamNames.size()); i++) {
        TeamResult result;

        result.name = teamNames[i];
        result.score = 0;
        result.sixthPlace = 100000;
        result.seventhPlace = 100000;

        int runnersFound = 0;

        for (int j = 0; j < static_cast<int>(finishers.size()); j++) {
            if (finishers[j].team == teamNames[i]) {
                runnersFound++;

                if (runnersFound <= 5) {
                    result.score += finishers[j].place;
                }
                else if (runnersFound == 6) {
                    result.sixthPlace = finishers[j].place;
                }
                else if (runnersFound == 7) {
                    result.seventhPlace = finishers[j].place;
                }
            }
        }

        results.push_back(result);
    }

    sort(results.begin(), results.end(),
        [](const TeamResult& a, const TeamResult& b) {
            if (a.score != b.score) {
                return a.score < b.score;
            }

            if (a.sixthPlace != b.sixthPlace) {
                return a.sixthPlace < b.sixthPlace;
            }

            return a.seventhPlace < b.seventhPlace;
        });

    cout << "\n============================\n";
    cout << "INDIVIDUAL RACE RESULTS\n";
    cout << "============================\n";

    for (int i = 0; i < static_cast<int>(finishers.size()); i++) {
        cout << setw(3) << finishers[i].place << ". "
             << finishers[i].team << " - "
             << finishers[i].runner << " - ";

        printTime(finishers[i].time);
        cout << "\n";
    }

    cout << "\n============================\n";
    cout << "XC TEAM STANDINGS\n";
    cout << "============================\n";

    for (int i = 0; i < static_cast<int>(results.size()); i++) {
        cout << setw(2) << i + 1 << ". "
             << results[i].name
             << " - " << results[i].score
             << " points\n";
    }

    for (int i = 0; i < static_cast<int>(results.size()); i++) {
        if (results[i].name == "Your Team") {
            cout << "\nYOUR TEAM FINISHED "
                 << i + 1 << " OF "
                 << results.size() << " TEAMS\n";

            cout << "Final XC Score: "
                 << results[i].score << "\n";

            break;
        }
    }
}

// ========================================================================
// NATIONAL COMPARISON
// ========================================================================
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

