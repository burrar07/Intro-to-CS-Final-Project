#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>

using namespace std;

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
