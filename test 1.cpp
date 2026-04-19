#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

string subjects[8][10] = {

{
"Engineering Physics",
"Linear Algebra and Calculus",
"Basic Electrical and Electronics Engineering",
"Engineering Graphics",
"Introduction to Programming",
"Engineering Physics Laboratory",
"Electrical and Electronics Engineering Workshop",
"Computer Programming Laboratory",
"IT Workshop",
"NSS / NCC / Community Service"
},

{
"Communicative English",
"Differential Equations and Vector Calculus",
"Chemistry",
"Basic Civil and Mechanical Engineering",
"Data Structures",
"Engineering Workshop",
"Communicative English Laboratory",
"Data Structures Laboratory",
"Chemistry Laboratory",
"Health and Wellness, Yoga and Sports"
},

{
"Discrete Mathematics and Graph Theory",
"Universal Human Values – Understanding Harmony",
"Digital Logic and Computer Organization",
"Advanced Data Structures and Algorithm Analysis",
"Object Oriented Programming through Java",
"Advanced Data Structures and Algorithm Analysis Laboratory",
"Object Oriented Programming through Java Laboratory",
"Python Programming",
"Environmental Science",
"Skill Enhancement Course"
},

{
"Managerial Economics and Financial Analysis",
"Probability and Statistics",
"Operating Systems",
"Database Management Systems",
"Software Engineering",
"Operating Systems Laboratory",
"Database Management Systems Laboratory",
"Full Stack Development",
"Design Thinking and Innovation",
"Skill Enhancement Course"
},

{
"Computer Networks",
"Compiler Design",
"Machine Learning",
"Web Technologies",
"Professional Elective I",
"Computer Networks Laboratory",
"Machine Learning Laboratory",
"Mini Project",
"Seminar",
"Skill Enhancement Course"
},

{
"Artificial Intelligence",
"Cloud Computing",
"Cyber Security",
"Data Mining",
"Professional Elective II",
"Artificial Intelligence Laboratory",
"Cloud Computing Laboratory",
"Project Work",
"Seminar",
"Internship"
},

{
"Big Data Analytics",
"Internet of Things",
"Professional Elective III",
"Professional Elective IV",
"Project Phase I",
"Seminar",
"Internship",
"Skill Enhancement Course",
"Open Elective",
"Laboratory"
},

{
"Major Project",
"Internship",
"Professional Elective V",
"Professional Elective VI",
"Viva Voce",
"Project Work",
"Seminar",
"Skill Enhancement Course",
"Open Elective",
"Laboratory"
}

};

float credits[8][10] = {
    {3,3,3,3,3,1,1.5,1.5,1,0.5},
    {2,3,3,3,3,1.5,1,1.5,1,0.5},
    {3,3,3,3,3,1.5,1.5,2,1,0},
    {2,3,3,3,3,1.5,1.5,2,1,0},
    {3,3,3,3,3,1,1,2,1,0},
    {3,3,3,3,3,1,1,2,1,0},
    {3,3,3,3,3,2,1,1,1,0},
    {6,2,3,3,2,1,1,1,1,0}
};

int getGradePoint(int m) {
    if (m >= 90) return 10;
    else if (m >= 80) return 9;
    else if (m >= 70) return 8;
    else if (m >= 60) return 7;
    else if (m >= 50) return 6;
    else if (m >= 40) return 5;
    else return 0;
}

class Student {
public:
    int roll, semester, marks[10], total;
    string name;
    float percent, sgpa;

    void input() {
        cout << "\n+--------------------------------------------------+\n";
        cout << "|               ENTER STUDENT DETAILS              |\n";
        cout << "+--------------------------------------------------+\n";

        cout << "| Roll Number : ";
        cin >> roll;

        cout << "| Name        : ";
        cin.ignore();
        getline(cin, name);

        cout << "| Semester(1-8): ";
        cin >> semester;

        total = 0;

        cout << "+--------------------------------------------------+\n";
        cout << "|                ENTER SUBJECT MARKS              |\n";
        cout << "+--------------------------------------------------+\n";

        for (int i = 0; i < 10; i++) {
            cout << "| " << setw(35) << left << subjects[semester-1][i] << ": ";
            cin >> marks[i];
            total += marks[i];
        }

        percent = (total / 1000.0) * 100;
        calculateSGPA();

        cout << "+--------------------------------------------------+\n";
    }

    void calculateSGPA() {
        float totalCredits = 0, weightedSum = 0;

        for (int i = 0; i < 10; i++) {
            int gp = getGradePoint(marks[i]);
            weightedSum += gp * credits[semester-1][i];
            totalCredits += credits[semester-1][i];
        }

        sgpa = weightedSum / totalCredits;
    }

    void printMarksheet() {
        cout << "\n+--------------------------------------------------+\n";
        cout << "|        PRAGATI ENGINEERING COLLEGE              |\n";
        cout << "|    COMPUTER SCIENCE & ENGINEERING DEPT          |\n";
        cout << "+--------------------------------------------------+\n";
        cout << "|               STUDENT MARKS MEMO                |\n";
        cout << "+--------------------------------------------------+\n";

        cout << "| Roll No   : " << setw(34) << left << roll << "|\n";
        cout << "| Name      : " << setw(34) << left << name << "|\n";
        cout << "| Semester  : " << setw(34) << left << semester << "|\n";

        cout << "+--------------------------------------------------+\n";
        cout << "| Subject                | Marks | Grade | Credit |\n";
        cout << "+--------------------------------------------------+\n";

        for (int i = 0; i < 10; i++) {
            int gp = getGradePoint(marks[i]);

            cout << "| " << setw(22) << left << subjects[semester-1][i]
                 << "| " << setw(6) << marks[i]
                 << "| " << setw(6) << gp
                 << "| " << setw(7) << credits[semester-1][i] << "|\n";
        }

        cout << "+--------------------------------------------------+\n";
        cout << "| Total Marks : " << setw(30) << left << total << "|\n";
        cout << "| Percentage  : " << setw(30) << left << percent << "|\n";
        cout << "| SGPA        : " << setw(30) << left << sgpa << "|\n";
        cout << "| Result      : " << setw(30) << left << (percent >= 40 ? "PASS" : "FAIL") << "|\n";
        cout << "+--------------------------------------------------+\n";
    }

    string toString() {
        stringstream ss;
        ss << roll << "," << name << "," << semester;
        for (int i = 0; i < 10; i++) ss << "," << marks[i];
        ss << "," << total << "," << percent << "," << sgpa;
        return ss.str();
    }
};

int toInt(string s) {
    int x; stringstream ss(s); ss >> x; return x;
}
float toFloat(string s) {
    float x; stringstream ss(s); ss >> x; return x;
}

void addStudent() {
    Student s;
    s.input();

    ofstream f("data.txt", ios::app);
    f << s.toString() << endl;
    f.close();

    cout << "\n+--------------------------------------------------+\n";
    cout << "|        RESULT SAVED SUCCESSFULLY                |\n";
    cout << "+--------------------------------------------------+\n";
}

void viewMarksheet() {
    int r, sem;
    cout << "\n+--------------------------------------------------+\n";
    cout << "|               SEARCH MARKSHEET                  |\n";
    cout << "+--------------------------------------------------+\n";

    cout << "| Enter Roll No : ";
    cin >> r;
    cout << "| Enter Semester: ";
    cin >> sem;

    ifstream f("data.txt");
    string line;

    while (getline(f, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        int roll = toInt(temp);

        string name;
        getline(ss, name, ',');

        getline(ss, temp, ',');
        int semester = toInt(temp);

        if (roll == r && semester == sem) {
            Student s;
            s.roll = roll;
            s.name = name;
            s.semester = semester;

            for (int i = 0; i < 10; i++) {
                getline(ss, temp, ',');
                s.marks[i] = toInt(temp);
            }

            getline(ss, temp, ','); s.total = toInt(temp);
            getline(ss, temp, ','); s.percent = toFloat(temp);
            getline(ss, temp, ','); s.sgpa = toFloat(temp);

            s.printMarksheet();
            return;
        }
    }

    cout << "\n+--------------------------------------------------+\n";
    cout << "|               RECORD NOT FOUND                  |\n";
    cout << "+--------------------------------------------------+\n";
}

void menu() {
    int choice;

    do {
        cout << "\n+--------------------------------------------------+\n";
        cout << "|              STUDENT RESULT SYSTEM              |\n";
        cout << "+--------------------------------------------------+\n";
        cout << "| 1. Add Student Result                           |\n";
        cout << "| 2. View Student Marksheet                       |\n";
        cout << "| 3. Exit                                         |\n";
        cout << "+--------------------------------------------------+\n";
        cout << "| Enter Choice: ";
        cin >> choice;
        cout << "+--------------------------------------------------+\n";

        if (choice == 1) addStudent();
        else if (choice == 2) viewMarksheet();

    } while (choice != 3);
}

int main() {
    menu();
    return 0;
}
