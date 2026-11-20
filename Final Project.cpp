#include <iostream>
#include <cstdlib>
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
    int grades = 80;
    int weeksOut = 0;
    int racePenalty = 0;
    int eventWeeks = 0;
    string currentEvent = "Healthy";
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

struct MeetHistory {
    string meetName;
    int week;
    int teamPlace;
    int teamScore;
    vector<RaceFinisher> yourRunners;
    vector<pair<string, int>> standings;
};

vector<MeetHistory> meetHistory;

struct RandomEvent {
    string name, category;
    int racePenalty, fatigueChange, gradeChange, enduranceChange, speedChange;
    int weeksOut, duration;
};
const vector<RandomEvent> eventDatabase = {
    { "Shin splints", "Fatigue", 15, 5, 0, 0, 0, 0, 2 },
    { "Rolled ankle", "Fatigue", 0, 5, 0, 0, 0, 2, 2 },
    { "Stress fracture", "Fatigue", 0, 5, 0, 0, 0, 6, 6 },
    { "Pulled hamstring", "Fatigue", 0, 5, 0, 0, 0, 3, 3 },
    { "Knee pain", "Fatigue", 20, 5, 0, 0, 0, 0, 2 },
    { "Achilles soreness", "Fatigue", 15, 5, 0, 0, 0, 0, 2 },
    { "Plantar fasciitis", "Fatigue", 20, 5, 0, 0, 0, 0, 3 },
    { "Hip flexor strain", "Fatigue", 0, 5, 0, 0, 0, 2, 2 },
    { "Calf strain", "Fatigue", 0, 5, 0, 0, 0, 2, 2 },
    { "Back spasms", "Fatigue", 15, 5, 0, 0, 0, 0, 1 },
    { "Blisters", "Fatigue", 5, 2, 0, 0, 0, 0, 1 },
    { "Tight quads", "Fatigue", 0, 10, 0, 0, 0, 0, 1 },
    { "IT band irritation", "Fatigue", 15, 5, 0, 0, 0, 0, 2 },
    { "Pulled groin", "Fatigue", 0, 5, 0, 0, 0, 2, 2 },
    { "Bruised heel", "Fatigue", 10, 5, 0, 0, 0, 0, 1 },
    { "Tripped on a trail", "Fatigue", 0, 10, 0, 0, 0, 0, 1 },
    { "Fell during strides", "Fatigue", 10, 5, 0, 0, 0, 0, 1 },
    { "Basketball ankle injury", "Fatigue", 0, 5, 0, 0, 0, 2, 2 },
    { "Concussion during intramurals", "Fatigue", 0, 0, 0, 0, 0, 3, 3 },
    { "Injury from bad decisions", "Fatigue", 0, 5, 0, 0, 0, 2, 2 },
    { "Common cold", "Sickness", 10, 5, 0, 0, 0, 0, 1 },
    { "Flu", "Sickness", 0, 5, 0, 0, 0, 2, 2 },
    { "Stomach bug", "Sickness", 0, 5, 0, 0, 0, 1, 1 },
    { "Food poisoning", "Sickness", 0, 5, 0, 0, 0, 1, 1 },
    { "Seasonal allergies", "Sickness", 10, 3, 0, 0, 0, 0, 2 },
    { "Sinus infection", "Sickness", 15, 5, 0, 0, 0, 0, 2 },
    { "Fever", "Sickness", 0, 5, 0, 0, 0, 1, 1 },
    { "Bad cough", "Sickness", 15, 5, 0, 0, 0, 0, 1 },
    { "Dehydrated after a hot day", "Sickness", 0, 10, 0, 0, 0, 0, 1 },
    { "Poor sleep all week", "Sickness", 0, 15, 0, 0, 0, 0, 1 },
    { "Stayed up studying", "Sickness", 0, 10, 0, 0, 0, 0, 1 },
    { "Overtrained", "Sickness", 0, 10, 0, 0, 0, 2, 2 },
    { "General exhaustion", "Sickness", 20, 10, 0, 0, 0, 0, 1 },
    { "Questionable dining hall food", "Sickness", 10, 5, 0, 0, 0, 0, 1 },
    { "Roommate brought home a bug", "Sickness", 15, 5, 0, 0, 0, 0, 1 },
    { "Failed a midterm", "Academic", 0, 5, -15, 0, 0, 0, 1 },
    { "Missed an assignment", "Academic", 0, 0, -10, 0, 0, 0, 1 },
    { "Forgot a final exam", "Academic", 0, 10, -25, 0, 0, 0, 1 },
    { "Academic probation warning", "Academic", 0, 5, -10, 0, 0, 0, 1 },
    { "Academic eligibility review", "Academic", 0, 0, -15, 0, 0, 0, 1 },
    { "Major project due", "Academic", 0, 10, 0, 0, 0, 0, 1 },
    { "Three exams in one week", "Academic", 0, 15, 0, 0, 0, 0, 1 },
    { "All-night study session", "Academic", 0, 10, 0, 0, 0, 0, 1 },
    { "Surprise homework", "Academic", 0, 5, 0, 0, 0, 0, 1 },
    { "Missed class for a race", "Academic", 0, 0, -5, 0, 0, 0, 1 },
    { "Academic advisor meeting", "Academic", 0, 5, 5, 0, 0, 0, 1 },
    { "Aced a major exam", "Academic", 0, 0, 10, 0, 0, 0, 1 },
    { "Finished a project early", "Academic", 0, -10, 5, 0, 0, 0, 1 },
    { "Got tutoring", "Academic", 0, 0, 10, 0, 0, 0, 1 },
    { "Made the Deans List", "Academic", 0, -5, 15, 0, 0, 0, 1 },
    { "Went through a breakup", "Social", 15, 5, 0, 0, 0, 0, 2 },
    { "Started dating someone", "Social", 0, -5, 0, 0, 0, 0, 1 },
    { "Relationship drama", "Social", 0, 10, 0, 0, 0, 0, 1 },
    { "Argument with teammate", "Social", 10, 5, 0, 0, 0, 0, 1 },
    { "Team group chat argument", "Social", 0, 5, 0, 0, 0, 0, 1 },
    { "Roommate conflict", "Social", 0, 10, 0, 0, 0, 0, 1 },
    { "Homesick", "Social", 10, 5, 0, 0, 0, 0, 1 },
    { "Lost motivation", "Social", 15, 5, 0, 0, 0, 0, 2 },
    { "Feeling overwhelmed", "Social", 0, 15, 0, 0, 0, 0, 1 },
    { "Mental burnout", "Social", 0, 10, 0, 0, 0, 1, 1 },
    { "Captain gives a great speech", "Social", 0, -5, 0, 0, 0, 0, 1 },
    { "Team bonding night", "Social", 0, -10, 0, 0, 0, 0, 1 },
    { "New friendship", "Social", 0, -5, 0, 0, 0, 0, 1 },
    { "Teammates stop talking", "Social", 10, 5, 0, 0, 0, 0, 1 },
    { "Runner regains confidence", "Social", -10, -5, 0, 0, 0, 0, 1 },
    { "Locked out of dorm", "Luck", 0, 5, 0, 0, 0, 0, 1 },
    { "All-night Minecraft session", "Luck", 0, 15, 0, 0, 0, 0, 1 },
    { "Intramural basketball marathon", "Luck", 0, 10, 0, 0, 0, 0, 1 },
    { "Tried to dunk and hurt ankle", "Luck", 0, 5, 0, 0, 0, 2, 2 },
    { "Fell off a skateboard", "Luck", 0, 5, 0, 0, 0, 2, 2 },
    { "Lost running shoes", "Luck", 0, 10, 0, 0, 0, 0, 1 },
    { "Forgot spikes at meet", "Luck", 10, 0, 0, 0, 0, 0, 1 },
    { "Accidentally ran too far", "Luck", 0, 20, 0, 0, 0, 0, 1 },
    { "Risky pre-race meal", "Luck", 15, 0, 0, 0, 0, 0, 1 },
    { "Entire pizza before practice", "Luck", 0, 10, 0, 0, 0, 0, 1 },
    { "Slept through morning practice", "Luck", 0, 5, 0, -1, 0, 0, 1 },
    { "Went to wrong race location", "Luck", 0, 0, 0, 0, 0, 1, 1 },
    { "Got lost on long run", "Luck", 0, 15, 0, 0, 0, 0, 1 },
    { "Prank war escalates", "Luck", 0, 5, 0, 0, 0, 0, 1 },
    { "Tried racing a cyclist", "Luck", 0, 10, 0, 0, 0, 0, 1 },
    { "Squirrel distraction", "Luck", 0, 5, 0, 0, 0, 0, 1 },
    { "Joined intramural tournament", "Luck", 0, 15, 0, 0, 0, 0, 1 },
    { "Tried to impress at gym", "Luck", 0, 20, 0, 0, 0, 0, 1 },
    { "Late-night Strava argument", "Luck", 0, 10, 0, 0, 0, 0, 1 },
    { "Unexplained nonsense", "Luck", 10, 5, 0, 0, 0, 0, 1 },
    { "Huge training breakthrough", "Positive", 0, 0, 0, 3, 0, 0, 1 },
    { "Perfect recovery week", "Positive", 0, -15, 0, 0, 0, 0, 1 },
    { "Unexpected fitness jump", "Positive", 0, 0, 0, 0, 2, 0, 1 },
    { "Great team chemistry", "Positive", 0, -5, 0, 0, 0, 0, 1 },
    { "New motivation", "Positive", 0, 0, 0, 2, 0, 0, 1 },
    { "Excellent sleep schedule", "Positive", 0, -10, 0, 0, 0, 0, 1 },
    { "Great workout", "Positive", 0, 0, 0, 0, 2, 0, 1 },
    { "Finally figures out pacing", "Positive", -10, 0, 0, 0, 0, 0, 1 },
    { "Successful team retreat", "Positive", 0, -10, 0, 0, 0, 0, 1 },
    { "Improved running form", "Positive", 0, 0, 0, 0, 2, 0, 1 },
    { "Breakthrough long run", "Positive", 0, 0, 0, 3, 0, 0, 1 },
    { "Unusually healthy week", "Positive", 0, -5, 0, 0, 0, 0, 1 },
    { "Won a friendly competition", "Positive", 0, -5, 0, 0, 0, 0, 1 },
    { "Motivational coach speech", "Positive", 0, -5, 0, 0, 0, 0, 1 },
    { "Everything clicks", "Positive", -15, 0, 0, 0, 0, 0, 1 }
};

int capped(int value) { return clamp(value, 0, 100); }

void beginWeek(Runner runners[]) {
    for (int i = 0; i < 7; ++i) {
        Runner& r = runners[i];
        if (r.weeksOut > 0) --r.weeksOut;
        if (r.eventWeeks > 0) {
            --r.eventWeeks;
            if (r.eventWeeks == 0) {
                r.racePenalty = 0;
                r.currentEvent = "Healthy";
            }
        }
        r.grades = capped(r.grades + 2);
    }
}

bool canRace(const Runner& r) {
    return r.weeksOut == 0 && r.grades >= 60;
}

void applyRandomEvent(Runner& r, const RandomEvent& e) {
    r.stats.fatigue = capped(r.stats.fatigue + e.fatigueChange);
    r.stats.endurance = capped(r.stats.endurance + e.enduranceChange);
    r.stats.speed = capped(r.stats.speed + e.speedChange);
    r.grades = capped(r.grades + e.gradeChange);
    r.weeksOut = max(r.weeksOut, e.weeksOut);
    if (e.duration >= r.eventWeeks || e.weeksOut > 0) {
        r.currentEvent = e.name;
        r.racePenalty = max(-30, r.racePenalty + e.racePenalty);
        r.eventWeeks = max(r.eventWeeks, e.duration);
    }
}

void clearScreen();

void eventScene(const Runner& runner, const RandomEvent& event, int week) {
    clearScreen();
    cout << "\n====================================================\n";
    cout << "               WEEK " << week << " - TEAM NEWS\n";
    cout << "====================================================\n\n";
    cout << "EVENT: " << event.name << "\n\n";
    if (event.category == "Fatigue")
        cout << "The athletic trainer has an update about " << runner.name
        << ". The training load has caught up with them.\n";
    else if (event.category == "Sickness")
        cout << runner.name << " hasn't been feeling right this week.\n"
        << "The team will have to adjust its expectations.\n";
    else if (event.category == "Academic")
        cout << "An update from the classroom has arrived for " << runner.name
        << ". School comes first, even during race season.\n";
    else if (event.category == "Social")
        cout << "There's been some news around the dorms involving "
        << runner.name << ". Team life isn't always simple.\n";
    else if (event.category == "Luck")
        cout << "You weren't expecting this one. " << runner.name
        << " has found a new way to make the season interesting.\n";
    else
        cout << "Some good news for " << runner.name
        << "! Sometimes things just go your way.\n";

    cout << "\nCOACH'S REPORT\n";
    if (event.weeksOut > 0)
        cout << "  Unavailable for at least " << event.weeksOut << " week(s).\n";
    if (event.racePenalty != 0)
        cout << "  Race time adjustment: " << (event.racePenalty > 0 ? "+" : "")
        << event.racePenalty << " seconds.\n";
    if (event.fatigueChange != 0)
        cout << "  Fatigue: " << (event.fatigueChange > 0 ? "+" : "")
        << event.fatigueChange << "\n";
    if (event.gradeChange != 0)
        cout << "  Grades: " << (event.gradeChange > 0 ? "+" : "")
        << event.gradeChange << "\n";
    if (event.enduranceChange != 0)
        cout << "  Endurance: " << (event.enduranceChange > 0 ? "+" : "")
        << event.enduranceChange << "\n";
    if (event.speedChange != 0)
        cout << "  Speed: " << (event.speedChange > 0 ? "+" : "")
        << event.speedChange << "\n";
    if (runner.grades < 60)
        cout << "  ACADEMICALLY INELIGIBLE: cannot race until grades recover.\n";
    cout << "\n----------------------------------------------------\n";
    cout << "Enter 0 to continue to your team. ";
    int choice = -1;
    while (choice != 0) {
        if (!(cin >> choice)) {
            if (cin.eof()) return;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (choice != 0) cout << "Please enter 0: ";
    }
}

void enforceFatigue(Runner runners[], int week) {
    for (int i = 0; i < 7; ++i) {
        Runner& r = runners[i];
        if (r.stats.fatigue < 95 || r.weeksOut > 0) continue;
        RandomEvent event = { "Extreme fatigue: mandatory recovery", "Fatigue",
                             0, 0, 0, 0, 0, 1, 1 };
        applyRandomEvent(r, event);
        eventScene(r, event, week);
    }
}

void generateRandomEvents(Runner runners[], int week) {
    static mt19937 gen(random_device{}());
    uniform_int_distribution<int> runnerPick(0, 6);
    uniform_int_distribution<int> percent(1, 100);
    cout << "\n========== WEEK " << week << " RANDOM EVENTS ==========\n";
    int eventCount = uniform_int_distribution<int>(0, 2)(gen);
    bool affected[7] = {};
    int generated = 0;
    for (int attempt = 0; attempt < 30 && generated < eventCount; ++attempt) {
        int i = runnerPick(gen);
        if (affected[i] || runners[i].weeksOut > 0) continue;
        int fatigue = runners[i].stats.fatigue;
        int risk = fatigue >= 85 ? 75 : fatigue >= 70 ? 45 :
            fatigue >= 50 ? 20 : fatigue >= 30 ? 8 : 2;
        string category;
        int roll = percent(gen);
        if (roll <= 20) category = "Positive";
        else if (roll <= 40) category = "Academic";
        else if (roll <= 60) category = "Social";
        else if (roll <= 80) category = "Luck";
        else category = (percent(gen) <= risk ? "Fatigue" : "Sickness");
        vector<int> options;
        for (int j = 0; j < (int)eventDatabase.size(); ++j)
            if (eventDatabase[j].category == category) options.push_back(j);
        if (options.empty()) continue;
        const RandomEvent& e = eventDatabase[options[uniform_int_distribution<int>(0, (int)options.size() - 1)(gen)]];
        applyRandomEvent(runners[i], e);
        eventScene(runners[i], e, week);
        affected[i] = true;
        ++generated;
        cout << runners[i].name << ": " << e.name;
        if (e.weeksOut) cout << " | unavailable for " << e.weeksOut << " week(s)";
        if (e.racePenalty) cout << " | race time change " << (e.racePenalty > 0 ? "+" : "") << e.racePenalty << "s";
        cout << "\n";
    }
    enforceFatigue(runners, week);
    if (!generated) cout << "No random incidents this week.\n";
}

void showAvailability(const Runner runners[]) {
    cout << "\n========== TEAM AVAILABILITY ==========\n";
    for (int i = 0; i < 7; ++i) {
        const Runner& r = runners[i];
        cout << r.name << " | " << (canRace(r) ? "READY" : "UNAVAILABLE")
            << " | Grades " << r.grades << "/100"
            << " | " << r.currentEvent;
        if (r.weeksOut) cout << " | " << r.weeksOut << " week(s) out";
        if (r.racePenalty && canRace(r)) cout << " | " << r.racePenalty << "s race adjustment";
        cout << "\n";
    }
}


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H" << flush;
#endif
}

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
bool seasonMenu(const Runner runners[], int division, int week);
void showRunnerStats(const Runner runners[]);
void showWorkoutInfo();
void showMeetHistory();
void showSeasonSchedule(int currentWeek);
void showNextRace(int currentWeek);
void showNationalProjection(const Runner runners[], int division);
bool advanceWeekMenu(const Runner runners[], int division, int week);
bool qualifiedForNationals();
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
    cout << "5. 1k Repeats\n";
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
    else if (choice == 5) workout = "1k Repeats";
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
    else if (workout == "1k Repeats") {
        runner.stats.speed += 3;
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

const int meetWeeks[7] = { 3, 5, 8, 9, 12, 14, 16 };

void showRunnerStats(const Runner runners[]) {
    cout << "\n========== RUNNER STATS ==========\n";
    for (int i = 0; i < 7; i++) {
        cout << i + 1 << ". " << runners[i].name
            << " | Endurance: " << runners[i].stats.endurance
            << " | Speed: " << runners[i].stats.speed
            << " | Fatigue: " << runners[i].stats.fatigue
            << " | Grades: " << runners[i].grades << "\n";
    }
}

void showWorkoutInfo() {
    cout << "\n========== WORKOUT GUIDE ==========\n";
    cout << "1. Steady State: +2 endurance, +3 fatigue\n";
    cout << "2. Mile Repeats: +2 speed, +4 fatigue\n";
    cout << "3. The Eagle: +2 endurance, +2 speed, +9 fatigue\n";
    cout << "4. Hill Repeats: +3 endurance, +7 fatigue\n";
    cout << "5. 1k Repeats: +3 speed, +6 fatigue\n";
    cout << "6. Premeet: -7 fatigue\n";
    cout << "7. Rest: -15 fatigue\n";
    cout << "Stats are limited to the range 0-100.\n";
    cout << "You choose two workouts each week for available runners.\n";
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
        projectedTimes[i] = canRace(runners[i]) ? calc8kTime(runners[i].stats) : -1;
    }
    int ready = count_if(projectedTimes, projectedTimes + 7, [](int t) { return t >= 0; });
    if (ready >= 5) nationalComparison(projectedTimes, division, 0);
    else cout << "Team projection: DNF (fewer than 5 eligible runners).\n";
}

void showMeetHistory() {
    cout << "\n========== MEET HISTORY ==========\n";
    if (meetHistory.empty()) {
        cout << "No meets completed yet.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(meetHistory.size()); i++) {
        const MeetHistory& meet = meetHistory[i];
        cout << "\n" << i + 1 << ". " << meet.meetName
            << " (Week " << meet.week << ")\n";
        if (meet.teamScore == 0) cout << "   Team: DNF (fewer than 5 finishers)\n";
        else cout << "   Team: " << meet.teamPlace << " of "
            << meet.standings.size() << " | "
            << meet.teamScore << " points\n";
        cout << "   Your runners:\n";
        for (const RaceFinisher& runner : meet.yourRunners) {
            cout << "     " << runner.place << ". " << runner.runner << " - ";
            printTime(runner.time);
            cout << "\n";
        }
        cout << "   Team standings:\n";
        for (int j = 0; j < static_cast<int>(meet.standings.size()); j++) {
            cout << "     " << j + 1 << ". "
                << meet.standings[j].first << " - "
                << meet.standings[j].second << " points\n";
        }
    }
}

bool qualifiedForNationals() {
    int lewisPlace = 100;
    int regionalPlace = 100;

    for (int i = 0; i < static_cast<int>(meetHistory.size()); i++) {
        if (meetHistory[i].meetName == "Lewis Invitational") {
            lewisPlace = meetHistory[i].teamPlace;
        }

        if (meetHistory[i].meetName == "Regionals") {
            regionalPlace = meetHistory[i].teamScore == 0 ? 100 : meetHistory[i].teamPlace;
        }
    }

    if (regionalPlace <= 3) {
        return true;
    }

    if (regionalPlace == 4 && lewisPlace <= 7) {
        return true;
    }

    return false;
}

void returnToMenu() {
    int choice = -1;

    while (choice != 0) {
        cout << "\nEnter 0 to return to the menu: ";
        cin >> choice;

        if (choice != 0) {
            cout << "Please enter 0 to return.\n";
        }
    }
}

void printMenuHeader(const string& title) {
    cout << "\n+--------------------------------------------------+\n";
    cout << "| " << left << setw(48) << title << " |\n";
    cout << "+--------------------------------------------------+\n";
    cout << right;
}

void printMenuOption(int number, const string& label) {
    cout << "  [" << number << "] " << label << "\n";
}

void printRaceCountdown(int week) {
    for (int i = 0; i < 7; i++) {
        if (meetWeeks[i] >= week) {
            int weeksAway = meetWeeks[i] - week;
            cout << "  NEXT RACE: " << Schedule[i]
                << " (Week " << meetWeeks[i] << ")\n";
            if (weeksAway == 0) {
                cout << "  STATUS:    Race week! Race follows training.\n";
            }
            else {
                cout << "  COUNTDOWN: " << weeksAway
                    << (weeksAway == 1 ? " week" : " weeks")
                    << " until race week\n";
            }
            return;
        }
    }
    cout << "  NEXT RACE: Season complete\n";
}

bool seasonMenu(const Runner runners[], int division, int week) {
    while (true) {
        clearScreen();
        printMenuHeader("XC MANAGEMENT | WEEK " + to_string(week) + " OF 16");
        printRaceCountdown(week);
        cout << "  ------------------------------------------------\n";
        cout << "  TEAM INFORMATION\n";
        printMenuOption(1, "National projection");
        printMenuOption(2, "Runner stats");
        printMenuOption(3, "Workout guide");
        printMenuOption(4, "Full season schedule");
        printMenuOption(5, "Meet history");
        cout << "  ------------------------------------------------\n";
        cout << "  ACTIONS\n";
        printMenuOption(6, "Start this week's training");
        printMenuOption(7, "Quit game");
        cout << "  ------------------------------------------------\n";
        cout << "  Select an option (1-7): ";

        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) return false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Please enter a number from 1 to 7.\n";
            continue;
        }

        if (choice >= 1 && choice <= 5) clearScreen();
        if (choice == 1) showNationalProjection(runners, division);
        else if (choice == 2) showRunnerStats(runners);
        else if (choice == 3) showWorkoutInfo();
        else if (choice == 4) showSeasonSchedule(week);
        else if (choice == 5) showMeetHistory();
        else if (choice == 6) return true;
        else if (choice == 7) return false;
        else cout << "  Invalid option. Please choose 1-7.\n";

        if (choice >= 1 && choice <= 5) returnToMenu();
    }
}

bool advanceWeekMenu(const Runner runners[], int division, int week) {
    while (true) {
        clearScreen();
        printMenuHeader("END OF WEEK " + to_string(week) + " | TEAM REVIEW");
        cout << "  TEAM INFORMATION\n";
        printMenuOption(1, "Review runner stats");
        printMenuOption(2, "Review national projection");
        printMenuOption(3, "Meet history");
        cout << "  ------------------------------------------------\n";
        cout << "  ACTIONS\n";
        printMenuOption(4, "Advance to week " + to_string(week + 1));
        printMenuOption(5, "Quit game");
        cout << "  ------------------------------------------------\n";
        cout << "  Select an option (1-5): ";

        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) return false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Please enter a number from 1 to 5.\n";
            continue;
        }

        if (choice >= 1 && choice <= 3) clearScreen();
        if (choice == 1) showRunnerStats(runners);
        else if (choice == 2) showNationalProjection(runners, division);
        else if (choice == 3) showMeetHistory();
        else if (choice == 4) return true;
        else if (choice == 5) return false;
        else cout << "  Invalid option. Please choose 1-5.\n";

        if (choice >= 1 && choice <= 3) returnToMenu();
    }
}

void schedule(Runner runners[], int division) {
    int meetCount = 0;
    string workoutChoice;

    for (int week = 1; week <= 16; week++) {
        beginWeek(runners);
        generateRandomEvents(runners, week);
        if (!seasonMenu(runners, division, week)) {
            cout << "\nThanks for playing!\n";
            return;
        }

        for (int workoutNumber = 1; workoutNumber <= 2; workoutNumber++) {
            chooseWorkout(workoutChoice, workoutNumber);
            if (!cin) return;
            for (int i = 0; i < 7; i++) {
                if (canRace(runners[i])) applyWorkout(runners[i], workoutChoice);
            }
        }


        enforceFatigue(runners, week);
        showAvailability(runners);
        bool raceWeek = (meetCount < 7 && week == meetWeeks[meetCount]);


        if (raceWeek) {
            cout << "\nEnter 0 to begin the race.\n";
            returnToMenu();
            clearScreen();
            runMeet(runners, meetCount, division);

            if (meetCount == 5) {
                cout << "\n============================\n";
                cout << "NATIONALS QUALIFICATION\n";
                cout << "============================\n";

                if (qualifiedForNationals()) {
                    cout << "Congratulations! Your team qualified "
                        << "for Nationals!\n";
                }
                else {
                    cout << "Your team did not qualify for Nationals.\n";
                    cout << "You needed top 3 at Regionals, or 4th "
                        << "with a top 7 finish at Lewis.\n";

                    cout << "\nFinal season results are available "
                        << "in meet history.\n";

                    returnToMenu();
                    return;
                }
            }

            meetCount++;
        }


        for (int i = 0; i < 7; i++) {
            runners[i].stats.fatigue = capped(runners[i].stats.fatigue - 3);
        }

        if (raceWeek) {
            cout << "\nEnd of week " << week << ".\n";
            returnToMenu();

            if (!cin) return;
        }
        else if (week < 16) {
            if (!advanceWeekMenu(runners, division, week)) {
                cout << "\nThanks for playing!\n";
                return;
            }
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
        if (!canRace(runners[i])) { runnersTimes[i] = -1; continue; }
        if (meetNumber >= 5) {
            runnersTimes[i] = calc10kTime(runners[i].stats);
        }
        else {
            runnersTimes[i] = calc8kTime(runners[i].stats);
        }

        runnersTimes[i] += calculateCourseEffect(runners[i].stats, meetNumber);
        runnersTimes[i] += raceVariation(gen);
        runnersTimes[i] += runners[i].racePenalty;

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
        if (runnersTimes[i] < 0) cout << "DID NOT START";
        else printTime(runnersTimes[i]);
        cout << "\n";
    }


    int sortedTimes[7];

    for (int i = 0; i < 7; i++) {
        sortedTimes[i] = runnersTimes[i];
    }

    sort(sortedTimes, sortedTimes + 7);
    int available = count_if(sortedTimes, sortedTimes + 7, [](int t) { return t >= 0; });

    int topFiveTotal = 0;

    for (int i = 0; i < 5 && available >= 5; i++) {
        topFiveTotal += sortedTimes[7 - available + i];
    }

    cout << "Top 5 Team Average: ";
    if (available >= 5) printTime(topFiveTotal / 5.0);
    else cout << "TEAM DNF (fewer than five runners)";
    cout << "\n";

    vector<OpposingTeam> teams = selectOpponents(meetNumber, division);

    calculateXCResults(runnersTimes, runners, teams, meetNumber);

    if (available >= 5) nationalComparison(runnersTimes, division, meetNumber);
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

    if (meetNumber == 0) {
        fastestTime = 1528;  // Mark Covert: 25:28
    }
    else if (meetNumber == 1) {
        fastestTime = 1425;  // UCR: 23:45
    }
    else if (meetNumber == 2) {
        fastestTime = 1459;  // Lewis: 24:19
    }
    else if (meetNumber == 3) {
        fastestTime = 1458;  // Highlander: 24:18
    }
    else if (meetNumber == 4) {
        if (division == 1) fastestTime = 1480;
        else if (division == 2) fastestTime = 1555;
        else fastestTime = 1420;
    }
    else if (meetNumber == 5) {
        if (division == 1) fastestTime = 1840;
        else if (division == 2) fastestTime = 1810;
        else fastestTime = 1780;
    }
    else {
        if (division == 1) fastestTime = 1840;
        else if (division == 2) fastestTime = 1810;
        else fastestTime = 1780;
    }

    for (int i = 0; i < static_cast<int>(names.size()); i++) {
        OpposingTeam team;
        team.name = names[i];

        if (meetNumber == 0) {

            if (i < 3)
                team.averageTime = fastestTime + i * 5;
            else
                team.averageTime = fastestTime + 10 + (i - 2) * 25;
        }
        else if (meetNumber == 1) {

            if (i < 5)
                team.averageTime = fastestTime + i * 10;
            else if (i < 10)
                team.averageTime = fastestTime + 40 + (i - 4) * 12;
            else
                team.averageTime = fastestTime + 100 + (i - 9) * 15;
        }
        else if (meetNumber == 2) {

            team.averageTime = fastestTime + i * 6;
        }
        else if (meetNumber == 3) {

            team.averageTime = fastestTime + i * 4;
        }
        else if (meetNumber == 4) {

            if (i < 3)
                team.averageTime = fastestTime + i * 12;
            else
                team.averageTime = fastestTime + 24 + (i - 2) * 45;
        }
        else if (meetNumber == 5) {

            team.averageTime = fastestTime + i * 10;
        }
        else {

            if (i < 5)
                team.averageTime = fastestTime + i * 8;
            else
                team.averageTime = fastestTime + 32 + (i - 4) * 9;
        }

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

        if (runnersTimes[i] < 0) continue;
        finisher.team = "Your Team";
        finisher.runner = runners[i].name;
        finisher.time = runnersTimes[i];
        finisher.place = 0;

        finishers.push_back(finisher);
    }

    int offsets[7] = {
        -25, -15, -5, 15, 30, 45, 60
    };

    for (int i = 0; i < static_cast<int>(teams.size()); i++) {
        for (int j = 0; j < 7; j++) {
            RaceFinisher finisher;

            finisher.team = teams[i].name;
            finisher.runner = "Runner " + to_string(j + 1);

            finisher.time = teams[i].averageTime
                + offsets[j]
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

        if (result.name == "Your Team" && runnersFound < 5) result.score = 1000000;
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

    MeetHistory history;
    history.meetName = Schedule[meetNumber];
    history.week = meetWeeks[meetNumber];
    history.teamPlace = 0;
    history.teamScore = 0;

    for (const RaceFinisher& finisher : finishers) {
        if (finisher.team == "Your Team") {
            history.yourRunners.push_back(finisher);
        }
    }
    for (int i = 0; i < static_cast<int>(results.size()); i++) {
        history.standings.push_back({ results[i].name, results[i].score });
        if (results[i].name == "Your Team") {
            history.teamPlace = results[i].score == 1000000 ? (int)results.size() : i + 1;
            history.teamScore = results[i].score == 1000000 ? 0 : results[i].score;
        }
    }
    meetHistory.push_back(history);

    cout << "\n============================\n";
    cout << "YOUR RUNNERS - RACE RESULTS\n";
    cout << "============================\n";

    for (const RaceFinisher& finisher : finishers) {
        if (finisher.team == "Your Team") {
            cout << setw(3) << finisher.place << ". "
                << finisher.runner << " - ";
            printTime(finisher.time);
            cout << "\n";
        }
    }

    cout << "\n============================\n";
    cout << "XC TEAM STANDINGS\n";
    cout << "============================\n";

    for (int i = 0; i < static_cast<int>(results.size()); i++) {
        cout << setw(2) << i + 1 << ". "
            << results[i].name
            << " - ";
        if (results[i].score == 1000000) cout << "DNF\n";
        else cout << results[i].score << " points\n";
    }

    for (int i = 0; i < static_cast<int>(results.size()); i++) {
        if (results[i].name == "Your Team") {
            if (results[i].score == 1000000)
                cout << "\nYOUR TEAM: DNF - FEWER THAN FIVE FINISHERS\n";
            else
                cout << "\nYOUR TEAM FINISHED " << i + 1 << " OF "
                << results.size() << " TEAMS\n";

            cout << "Final XC Score: ";
            if (results[i].score == 1000000) cout << "DNF\n";
            else cout << results[i].score << "\n";

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
    int available = count_if(times, times + 7, [](int t) { return t >= 0; });
    if (available < 5) {
        cout << "National comparison unavailable: team DNF.\n";
        return;
    }

    int total = 0;

    for (int i = 0; i < 5; i++) {
        total += times[7 - available + i];
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
