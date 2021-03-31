#include <iostream>
#include <algorithm>

using namespace std;

class Student {
public:
    string name;
    int score;
    Student(string name, int score) {
        this->name = name;
        this->score = score;
    }
    bool operator <(Student &student) {
        return this->score > student.score;
    }
};

int main(void) {
    Student students[] = {
        Student("윤동현", 96),
        Student("이한울", 91),
        Student("안성우", 92),
        Student("김동현", 94),
        Student("한기우", 95)
    };
    sort(students, students + 5, compare);
    for(int i = 0; i < 5; i++)
        cout << students[i].name << ' ';
    return 0;
}
