#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

const int RUNNERS = 7;
const int MEETS = 7;
const int WEEKS = 16;
const string meetNames[MEETS] = { "Mark Covert", "UCR", "Lewis Invitational", "Highlander Invitational", "Conference", "Regionals", "Nationals" };
const int meetWeeks[MEETS] = { 3, 5, 8, 9, 12, 14, 16 };
const int courseSeconds[MEETS] = { 10, -10, 30, -10, 25, 35, 45 };

struct Runner {
    string name;
    int endurance;
    int speed;
    int fatigue;
    int weeksOut;
};
struct Finisher {
    int team;
    int time;
    int place;
};
struct TeamResult {
    int points;
    int sixth;
    int seventh;
};
struct MeetRecord {
    int place;
    int points;
    int teams;
};

// Random numbers
int randomNumber(int low, int high) {
    return low + rand() % (high - low + 1);
}
// Stat limits (0-100)
int limitStat(int value) {
    if (value < 0) return 0;
    if (value > 100) return 100;
    return value;
}
// Menu input
int askNumber(int low, int high) {
    int answer;
    while (true) {
        cin >> answer;
        if (cin && answer >= low && answer <= high) return answer;
        if (cin.eof()) return low;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter a number from " << low << " to " << high << ": ";
    }
}
// Race time display
void printTime(int seconds) {
    cout << seconds / 60 << ":";
    if (seconds % 60 < 10) cout << "0";
    cout << seconds % 60;
}
// Runner setup
void setupRunners(Runner runners[], int division) {
    for (int i = 0; i < RUNNERS; i++) {
        cout << "Name of runner " << i + 1 << ": ";
        getline(cin >> ws, runners[i].name);
        runners[i].endurance = randomNumber(40 + division * 5, 60 + division * 5);
        runners[i].speed = randomNumber(35 + division * 5, 55 + division * 5);
        runners[i].fatigue = randomNumber(30 - division * 5, 50 - division * 5);
        runners[i].weeksOut = 0;
    }
}
// Runner stats
void showStats(Runner runners[]) {
    // Stores stats in a table.
    int stats[RUNNERS][3];
    for (int i = 0; i < RUNNERS; i++) {
        stats[i][0] = runners[i].endurance;
        stats[i][1] = runners[i].speed;
        stats[i][2] = runners[i].fatigue;
    }
    cout << "\nRUNNER STATS (endurance, speed, fatigue)\n";
    for (int i = 0; i < RUNNERS; i++) {
        cout << i + 1 << ". " << runners[i].name << ": ";
        for (int j = 0; j < 3; j++) cout << stats[i][j] << " ";
        if (runners[i].weeksOut > 0) cout << "OUT " << runners[i].weeksOut << " week(s)";
        cout << "\n";
    }
}


// Team averages
void showTeamReport(Runner runners[]) {
    int ready = 0;
    int totalEndurance = 0;
    int totalSpeed = 0;
    int totalFatigue = 0;

    cout << "\n========== TEAM REPORT ==========\n";

    for (int i = 0; i < RUNNERS; i++) {
        totalEndurance += runners[i].endurance;
        totalSpeed += runners[i].speed;
        totalFatigue += runners[i].fatigue;

        if (runners[i].weeksOut == 0) {
            ready++;
        }
    }

    cout << "Runners ready to race: " << ready << " of " << RUNNERS << "\n";
    cout << "Average endurance: " << totalEndurance / RUNNERS << "\n";
    cout << "Average speed: " << totalSpeed / RUNNERS << "\n";
    cout << "Average fatigue: " << totalFatigue / RUNNERS << "\n";

    if (ready < 5) {
        cout << "Warning: You need five runners to score at a meet.\n";
    }
    else {
        cout << "You have enough runners to score at a meet.\n";
    }

    if (totalFatigue / RUNNERS >= 70) {
        cout << "Your team is tired. Consider choosing Rest.\n";
    }
    else if (totalFatigue / RUNNERS >= 45) {
        cout << "Your team has moderate fatigue.\n";
    }
    else {
        cout << "Your team is recovering well.\n";
    }
}

// Upcoming meet
void showNextMeet(int week) {
    int next = -1;

    // Linear search through the meet schedule
    for (int i = 0; i < MEETS; i++) {
        if (meetWeeks[i] >= week) {
            next = i;
            break;
        }
    }

    cout << "\n========== NEXT MEET ==========\n";
    if (next == -1) {
        cout << "No meets remaining.\n";
        return;
    }

    cout << "Meet: " << meetNames[next] << "\n";
    cout << "Week: " << meetWeeks[next] << "\n";
    cout << "Weeks away: " << meetWeeks[next] - week << "\n";

    if (next < 5) cout << "Distance: 8K\n";
    else cout << "Distance: 10K\n";

    if (courseSeconds[next] > 0) cout << "Course: Slower than average\n";
    else if (courseSeconds[next] < 0) cout << "Course: Faster than average\n";
    else cout << "Course: Average\n";

    if (next == 2) {
        cout << "Goal: Top 7 helps if you finish 4th at Regionals.\n";
    }
    else if (next == 5) {
        cout << "Goal: Top 3 qualifies for Nationals.\n";
        cout << "4th also qualifies with a top 7 finish at Lewis.\n";
    }
    else if (next == 6) {
        cout << "Goal: Compete at Nationals!\n";
    }
    else {
        cout << "Goal: Improve your team placement.\n";
    }

    if (meetWeeks[next] == week) cout << "This is race week!\n";
}

// Upcoming schedule
void showSchedule(int week) {
    for (int i = 0; i < MEETS; i++) {
        cout << "Week " << meetWeeks[i] << ": " << meetNames[i];
        if (meetWeeks[i] < week) cout << " (completed)";
        cout << "\n";
    }
}
// Meet history
void showHistory(MeetRecord history[], int completed) {
    if (completed == 0) cout << "No meets yet.\n";
    for (int i = 0; i < completed; i++) {
        cout << meetNames[i] << ": ";
        if (history[i].points < 0) cout << "DNF";
        else cout << history[i].place << "/" << history[i].teams << " place, " << history[i].points << " points";
        cout << "\n";
    }
}
// Workout choices
void showWorkouts() {
    cout << "1. Steady State (+2 endurance, +3 fatigue)\n";
    cout << "2. Mile Repeats (+2 speed, +4 fatigue)\n";
    cout << "3. The Eagle (+2 endurance, +2 speed, +9 fatigue)\n";
    cout << "4. Hills (+3 endurance, +7 fatigue)\n";
    cout << "5. 1k Repeats (+3 speed, +6 fatigue)\n";
    cout << "6. Premeet (-7 fatigue)\n";
    cout << "7. Rest (-1 endurance, -1 speed, -15 fatigue)\n";
}
// Training stat changes
void applyWorkout(Runner& runner, int choice) {
    if (runner.weeksOut > 0) return;
    switch (choice) {
    case 1: runner.endurance += 2; runner.fatigue += 3; break;
    case 2: runner.speed += 2; runner.fatigue += 4; break;
    case 3: runner.endurance += 2; runner.speed += 2; runner.fatigue += 9; break;
    case 4: runner.endurance += 3; runner.fatigue += 7; break;
    case 5: runner.speed += 3; runner.fatigue += 6; break;
    case 6: runner.fatigue -= 7; break;
    case 7: runner.endurance -= 1; runner.speed -= 1; runner.fatigue -= 15; break;
    }
    runner.endurance = limitStat(runner.endurance);
    runner.speed = limitStat(runner.speed);
    runner.fatigue = limitStat(runner.fatigue);
}
// Random team events
void randomEvents(Runner runners[]) {
    const string messages[10] = {
        "stayed up all night playing Minecraft", "ate suspicious dining hall chicken",
        "rolled an ankle playing basketball", "had a huge training breakthrough",
        "finally figured out pacing", "had a perfect recovery week",
        "raced a cyclist and lost", "got lost on a long run",
        "received a legendary pep talk", "tripped over absolutely nothing"
    };
    cout << "\nTEAM NEWS\n";
    int count = randomNumber(0, 2);
    bool chosen[RUNNERS] = { false };
    int available = 0;
    for (int i = 0; i < RUNNERS; i++) if (runners[i].weeksOut == 0) available++;
    if (count > available) count = available;
    if (count == 0) cout << "A surprisingly normal week.\n";
    for (int n = 0; n < count; n++) {
        int index = randomNumber(0, RUNNERS - 1);
        while (chosen[index] || runners[index].weeksOut > 0)
            index = randomNumber(0, RUNNERS - 1);
        chosen[index] = true;
        int event = randomNumber(0, 9);
        cout << runners[index].name << " " << messages[event] << ".\n";
        switch (event) {
        case 0: runners[index].fatigue += 15; break;
        case 1: runners[index].fatigue += 8; runners[index].weeksOut = 1; break;
        case 2: runners[index].fatigue += 5; runners[index].weeksOut = 2; break;
        case 3: runners[index].endurance += 3; break;
        case 4: runners[index].speed += 3; break;
        case 5: runners[index].fatigue -= 15; break;
        case 6: runners[index].fatigue += 12; break;
        case 7: runners[index].fatigue += 12; break;
        case 8: runners[index].fatigue -= 8; break;
        case 9: runners[index].fatigue += 5; break;
        }
        runners[index].fatigue = limitStat(runners[index].fatigue);
        runners[index].speed = limitStat(runners[index].speed);
        runners[index].endurance = limitStat(runners[index].endurance);
    }
}
// Exhausted runners
void checkFatigue(Runner runners[]) {
    for (int i = 0; i < RUNNERS; i++) {
        if (runners[i].fatigue >= 95 && runners[i].weeksOut == 0) {
            runners[i].weeksOut = 1;
            cout << runners[i].name << " is exhausted and cannot race this week.\n";
        }
    }
}
// Race time calculation
int raceTime(Runner runner, int meet) {
    double seconds = 1700 - 2.0 * runner.endurance - 1.2 * runner.speed + 1.2 * runner.fatigue;
    if (meet >= 5) seconds = seconds * 1.27;
    seconds += courseSeconds[meet] + randomNumber(-15, 15);
    return (int)(seconds + 0.5);
}
// Runner finish order
void selectionSortFinishers(Finisher finishers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int smallest = i;
        for (int j = i + 1; j < count; j++) {
            if (finishers[j].time < finishers[smallest].time) smallest = j;
        }
        Finisher temp = finishers[i];
        finishers[i] = finishers[smallest];
        finishers[smallest] = temp;
    }
}
// Team standings order
void selectionSortTeams(TeamResult scores[], int order[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int smallest = i;
        for (int j = i + 1; j < count; j++) {
            int a = order[j];
            int b = order[smallest];
            if (scores[a].points < scores[b].points ||
                (scores[a].points == scores[b].points && scores[a].sixth < scores[b].sixth) ||
                (scores[a].points == scores[b].points && scores[a].sixth == scores[b].sixth && scores[a].seventh < scores[b].seventh))
                smallest = j;
        }
        int temp = order[i];
        order[i] = order[smallest];
        order[smallest] = temp;
    }
}
// Matching team names
bool sameTeamName(string first, string second) {
    if (first.length() != second.length()) return false;

    for (int i = 0; i < (int)first.length(); i++) {
        if (tolower(first[i]) != tolower(second[i])) return false;
    }

    return true;
}

// Opposing teams
int buildOpponents(int meet, int division, string names[], int averages[], string playerTeam) {
    const string local[10] = { "Cal State Fullerton", "UC Irvine", "Cal Poly Pomona", "Concordia Irvine", "Azusa Pacific", "Westmont", "Cal State LA", "Vanguard", "Chapman", "UC Riverside" };
    const string lewis[12] = { "Grand Valley State", "Lewis", "Augustana", "Minnesota State", "Michigan Tech", "Cedarville", "Walsh", "Hillsdale", "Indianapolis", "Wayne State", "Ashland", "Findlay" };
    const string d3[12] = { "Pomona-Pitzer", "Claremont-Mudd-Scripps", "George Fox", "MIT", "UW-La Crosse", "North Central", "Wartburg", "Caltech", "Occidental", "Redlands", "Whitworth", "Willamette" };
    const string d2[12] = { "Chico State", "Cal Poly Pomona", "Western Washington", "Adams State", "Colorado Mines", "Grand Valley State", "Westmont", "Concordia Irvine", "Western Oregon", "Alaska Anchorage", "Lewis", "Vanguard" };
    const string d1[12] = { "Oregon", "Stanford", "Washington", "BYU", "Northern Arizona", "Gonzaga", "Portland", "UC Davis", "UCLA", "UC Riverside", "Cal Poly SLO", "New Mexico" };
    int count = 10;
    if (meet == 2 || meet >= 4) count = 12;
    int fastest = 1528;
    if (meet == 1) fastest = 1425;
    if (meet == 2) fastest = 1459;
    if (meet == 3) fastest = 1458;
    if (meet == 4) {
        if (division == 1) fastest = 1480;
        if (division == 2) fastest = 1555;
        if (division == 3) fastest = 1420;
    }
    if (meet >= 5) {
        if (division == 1) fastest = 1840;
        if (division == 2) fastest = 1810;
        if (division == 3) fastest = 1780;
    }
    int added = 0;
    for (int i = 0; i < count; i++) {
        string opponent;
        if (meet == 2) opponent = lewis[i];
        else if (meet >= 4 && division == 1) opponent = d3[i];
        else if (meet >= 4 && division == 2) opponent = d2[i];
        else if (meet >= 4) opponent = d1[i];
        else opponent = local[i];

        // Skip opponents with the player's team name.
        if (sameTeamName(opponent, playerTeam)) continue;

        names[added] = opponent;
        averages[added] = fastest + i * 12;
        if (meet == 0) averages[added] = fastest + i * 20;
        if (meet == 2) averages[added] = fastest + i * 6;
        if (meet == 3) averages[added] = fastest + i * 4;
        if (meet >= 5) averages[added] = fastest + i * 10;
        added++;
    }
    return added;
}
// Meet simulation and scoring
MeetRecord runMeet(Runner runners[], int meet, int division, string teamName) {
    const int MAX_TEAMS = 13;
    const int MAX_FINISHERS = MAX_TEAMS * RUNNERS;
    const int offsets[RUNNERS] = { -25, -15, -5, 15, 30, 45, 60 };
    string names[MAX_TEAMS];
    int averages[MAX_TEAMS];
    names[0] = teamName;
    int opponents = buildOpponents(meet, division, names + 1, averages + 1, teamName);
    int teamCount = opponents + 1;
    Finisher finishers[MAX_FINISHERS];
    int count = 0;
    int eligible = 0;
    cout << "\n========== " << meetNames[meet] << " ==========\n";
    for (int i = 0; i < RUNNERS; i++) {
        cout << runners[i].name << ": ";
        if (runners[i].weeksOut > 0) {
            cout << "DID NOT START\n";
        }
        else {
            int time = raceTime(runners[i], meet);
            printTime(time);
            cout << "\n";
            finishers[count].team = 0;
            finishers[count].time = time;
            finishers[count].place = 0;
            count++;
            eligible++;
            runners[i].fatigue = limitStat(runners[i].fatigue + 8);
        }
    }
    for (int t = 1; t < teamCount; t++) {
        for (int j = 0; j < RUNNERS; j++) {
            finishers[count].team = t;
            finishers[count].time = averages[t] + offsets[j] + randomNumber(-12, 12);
            finishers[count].place = 0;
            count++;
        }
    }
    // Assigns finishing places.
    selectionSortFinishers(finishers, count);
    TeamResult scores[MAX_TEAMS];
    int found[MAX_TEAMS] = { 0 };
    for (int t = 0; t < teamCount; t++) {
        scores[t].points = 0;
        scores[t].sixth = 100000;
        scores[t].seventh = 100000;
    }
    cout << "\nYOUR RUNNERS' FINISHES\n";
    for (int i = 0; i < count; i++) {
        finishers[i].place = i + 1;
        int t = finishers[i].team;
        found[t]++;
        // Adds the first five places.
        if (found[t] <= 5) scores[t].points += finishers[i].place;
        if (found[t] == 6) scores[t].sixth = finishers[i].place;
        if (found[t] == 7) scores[t].seventh = finishers[i].place;
        if (t == 0) {
            cout << "Place " << finishers[i].place << " - ";
            printTime(finishers[i].time);
            cout << "\n";
        }
    }
    // Checks for five finishers.
    if (eligible < 5) scores[0].points = 1000000;
    int order[MAX_TEAMS];
    for (int i = 0; i < teamCount; i++) order[i] = i;
    selectionSortTeams(scores, order, teamCount);
    MeetRecord result;
    result.place = 0;
    result.points = -1;
    result.teams = teamCount;
    cout << "\nTEAM STANDINGS\n";
    for (int i = 0; i < teamCount; i++) {
        int t = order[i];
        cout << i + 1 << ". " << names[t] << " - ";
        if (scores[t].points == 1000000) cout << "DNF\n";
        else cout << scores[t].points << " points\n";
        if (t == 0) {
            result.place = i + 1;
            if (eligible >= 5) result.points = scores[t].points;
        }
    }
    cout << teamName << ": ";
    if (result.points < 0) cout << "DNF\n";
    else cout << result.place << "/" << result.teams << " place, " << result.points << " points\n";
    return result;
}
// Nationals qualification
bool qualified(MeetRecord history[]) {
    int lewis = 100;
    int regionals = 100;
    if (history[2].points >= 0) lewis = history[2].place;
    if (history[5].points >= 0) regionals = history[5].place;
    // Checks automatic qualification.
    if (regionals <= 3) return true;
    // Checks fourth-place qualification.
    if (regionals == 4 && lewis <= 7) return true;
    return false;
}
// Save game
void saveGame(Runner runners[], MeetRecord history[], int division, int week, int completed, string teamName) {
    ofstream file("season.txt");
    if (!file) {
        cout << "Could not save game.\n";
        return;
    }
    file << division << " " << week << " " << completed << "\n";
    file << teamName << "\n";
    for (int i = 0; i < RUNNERS; i++) {
        file << runners[i].name << "\n";
        file << runners[i].endurance << " " << runners[i].speed << " "
            << runners[i].fatigue << " " << runners[i].weeksOut << "\n";
    }
    for (int i = 0; i < completed; i++)
        file << history[i].place << " " << history[i].points << " " << history[i].teams << "\n";
    file.close();
    cout << "Saved to season.txt\n";
}
// Load game
bool loadGame(Runner runners[], MeetRecord history[], int& division, int& week, int& completed, string& teamName) {
    ifstream file("season.txt");
    if (!file) return false;
    if (!(file >> division >> week >> completed)) return false;
    if (division < 1 || division > 3 || week < 1 || week > WEEKS || completed < 0 || completed > MEETS) return false;
    getline(file >> ws, teamName);
    if (teamName.empty()) return false;
    for (int i = 0; i < RUNNERS; i++) {
        getline(file >> ws, runners[i].name);
        if (!(file >> runners[i].endurance >> runners[i].speed >> runners[i].fatigue >> runners[i].weeksOut)) return false;
        if (runners[i].endurance < 0 || runners[i].endurance > 100 ||
            runners[i].speed < 0 || runners[i].speed > 100 ||
            runners[i].fatigue < 0 || runners[i].fatigue > 100 ||
            runners[i].weeksOut < 0 || runners[i].weeksOut > WEEKS) return false;
    }
    for (int i = 0; i < completed; i++) {
        if (!(file >> history[i].place >> history[i].points >> history[i].teams)) return false;
    }
    file.close();
    return true;
}

// Game goals and rules
void showIntroduction() {
    cout << "\n========================================\n";
    cout << "       WELCOME TO XC MANAGEMENT\n";
    cout << "========================================\n";
    cout << "You are the coach of a college cross country team.\n";
    cout << "Your goal is to build a strong team and qualify\n";
    cout << "for Nationals at the end of the season!\n\n";

    cout << "HOW THE GAME WORKS\n";
    cout << "1. Choose a division: DIII, DII, or DI.\n";
    cout << "2. Give your team a name.\n";
    cout << "3. Name your seven runners.\n";
    cout << "4. Manage your team through 16 weeks and seven meets.\n";
    cout << "5. Choose two workouts each week to improve your team.\n";
    cout << "6. Watch fatigue: tired runners race slower.\n";
    cout << "7. Random events can help or hurt your runners.\n\n";

    cout << "RACING RULES\n";
    cout << "- Your five best finishers score points.\n";
    cout << "- Lower team scores are better.\n";
    cout << "- Your sixth and seventh runners break ties.\n";
    cout << "- You need at least five finishers to score.\n";
    cout << "- Regionals and Nationals are 10K races.\n\n";

    cout << "HOW TO REACH NATIONALS\n";
    cout << "- Finish in the top 3 at Regionals, OR\n";
    cout << "- Finish 4th at Regionals AND top 7 at Lewis.\n";
    cout << "- Otherwise, your season ends at Regionals.\n\n";

    cout << "You can view stats, check your schedule,\n";
    cout << "and save your season as you play.\n";
    cout << "Good luck, Coach!\n";
    cout << "========================================\n\n";
}

// Main game menu
int main() {
    srand((unsigned int)time(0));
    Runner runners[RUNNERS];
    MeetRecord history[MEETS];
    int division = 1;
    int week = 1;
    int completed = 0;
    string teamName;
    showIntroduction();
    cout << "========== XC MANAGEMENT ==========\n";
    cout << "1. New season\n2. Load season\n3. Quit\nChoice: ";
    int start = askNumber(1, 3);
    switch (start) {
    case 1:
        cout << "1. Division III (Easy)\n2. Division II (Medium)\n3. Division I (Hard)\nChoice: ";
        division = askNumber(1, 3);
        cout << "Enter your team name: ";
        getline(cin >> ws, teamName);
        setupRunners(runners, division);
        break;
    case 2:
        if (!loadGame(runners, history, division, week, completed, teamName)) {
            cout << "No valid saved season found.\n";
            return 0;
        }
        cout << "Season loaded for " << teamName << ".\n";
        break;
    case 3:
        return 0;
    }
    while (week <= WEEKS) {
        cout << "\n========================================\n";
        cout << "  " << teamName << " - WEEK " << week << " OF " << WEEKS << "\n";
        cout << "========================================\n";
        cout << "  TEAM\n";
        cout << "    1. Runner Stats\n";
        cout << "    2. Team Report\n";
        cout << "\n  RACES\n";
        cout << "    3. Next Meet\n";
        cout << "    4. Season Schedule\n";
        cout << "    5. Meet History\n";
        cout << "\n  TRAINING\n";
        cout << "    6. Workout Guide\n";
        cout << "    7. Start Weekly Training\n";
        cout << "\n  EXIT\n";
        cout << "    8. Save and Quit\n";
        cout << "----------------------------------------\n";
        cout << "Choice: ";
        int choice = askNumber(1, 8);
        switch (choice) {
        case 1: showStats(runners); break;
        case 2: showTeamReport(runners); break;
        case 3: showNextMeet(week); break;
        case 4: showSchedule(week); break;
        case 5: showHistory(history, completed); break;
        case 6: showWorkouts(); break;
        case 7: {
            // Prevents repeated weekly events.
            for (int i = 0; i < RUNNERS; i++) {
                if (runners[i].weeksOut > 0) runners[i].weeksOut--;
            }
            randomEvents(runners);
            for (int workout = 1; workout <= 2; workout++) {
                cout << "\nWorkout " << workout << " of 2\n";
                showWorkouts();
                cout << "Choice: ";
                int workoutChoice = askNumber(1, 7);
                for (int i = 0; i < RUNNERS; i++) applyWorkout(runners[i], workoutChoice);
            }
            checkFatigue(runners);
            if (completed < MEETS && week == meetWeeks[completed]) {
                history[completed] = runMeet(runners, completed, division, teamName);
                completed++;
                if (completed == 6) {
                    if (qualified(history)) cout << "\nQUALIFIED FOR NATIONALS!\n";
                    else {
                        cout << "\nSEASON OVER. Needed top 3 at Regionals, or 4th with top 7 at Lewis.\n";
                        showHistory(history, completed);
                        return 0;
                    }
                }
            }
            for (int i = 0; i < RUNNERS; i++) runners[i].fatigue = limitStat(runners[i].fatigue - 3);
            week++;
            break;
        }
        case 8:
            saveGame(runners, history, division, week, completed, teamName);
            return 0;
        }
    }
    cout << "\nSEASON COMPLETE!\n";
    showHistory(history, completed);
    return 0;
}
