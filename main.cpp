#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

// --- Global Subject Data ---
string subjects[8][10] = {
    {"Engineering Physics","Linear Algebra and Calculus","Basic Electrical and Electronics Engineering","Engineering Graphics","Introduction to Programming","Engineering Physics Laboratory","Electrical and Electronics Engineering Workshop","Computer Programming Laboratory","IT Workshop","NSS / NCC / Community Service"},
    {"Communicative English","Differential Equations and Vector Calculus","Chemistry","Basic Civil and Mechanical Engineering","Data Structures","Engineering Workshop","Communicative English Laboratory","Data Structures Laboratory","Chemistry Laboratory","Health and Wellness, Yoga and Sports"},
    {"Discrete Mathematics","Universal Human Values","Digital Logic","Advanced Data Structures","Java Programming","ADSA Lab","Java Lab","Python Programming","Environmental Science","SEC"},
    {"Managerial Economics","Probability and Statistics","Operating Systems","DBMS","Software Engineering","OS Lab","DBMS Lab","Full Stack","Design Thinking","SEC"},
    {"Computer Networks","Compiler Design","Machine Learning","Web Technologies","PE I","CN Lab","ML Lab","Mini Project","Seminar","SEC"},
    {"Artificial Intelligence","Cloud Computing","Cyber Security","Data Mining","PE II","AI Lab","Cloud Lab","Project","Seminar","Internship"},
    {"Big Data","IoT","PE III","PE IV","Project Phase I","Seminar","Internship","SEC","Open Elective","Lab"},
    {"Major Project","Internship","PE V","PE VI","Viva","Project","Seminar","SEC","Open Elective","Lab"}
};

// --- Student Class ---
class Student {
public:
    int roll, semester, marks[10], total;
    string name, grade;
    float percent, cgpa;
    Student* next;

    Student() { next = NULL; }

    bool isPass() {
        for(int i=0; i<10; i++) if(marks[i] < 35) return false;
        return (percent >= 40);
    }

    void calculate() {
        total = 0;
        for(int i=0; i<10; i++) total += marks[i];
        percent = (total / 1000.0f) * 100;
        cgpa = percent / 9.5f;

        if(!isPass()) { grade = "F"; return; }
        if(percent >= 90) grade="A+";
        else if(percent >= 75) grade="A";
        else if(percent >= 60) grade="B";
        else if(percent >= 50) grade="C";
        else grade="D";
    }

    void input() {
        cout << "\n+----------------------------------------------------------+\n";
        cout << "|                 DATA ENTRY FOR STUDENT                   |\n";
        cout << "+----------------------------------------------------------+\n";
        cout << "  Enter Roll: "; cin >> roll;
        cout << "  Enter Name: "; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        
        do {
            cout << "  Enter Semester (1-8): ";
            cin >> semester;
        } while (semester < 1 || semester > 8);

        cout << "+----------------------------------------------------------+\n";
        for(int i=0; i<10; i++) {
            cout << "  " << left << setw(45) << subjects[semester-1][i] << ": ";
            do {
                cin >> marks[i];
                if(marks[i] < 0 || marks[i] > 100) cout << "  Invalid! 0-100: ";
            } while(marks[i] < 0 || marks[i] > 100);
        }
        calculate();
    }

    void display() {
        string sep = "+-----------------------------------------------------------------------+";
        cout << fixed << setprecision(2);
        cout << "\n" << sep << "\n";
        cout << "|                       PRAGATI ENGINEERING COLLEGE                     |\n";
        cout << "|                  COMPUTER SCIENCE & ENGINEERING DEPT                  |\n";
        cout << sep << "\n";
        cout << "| Name: " << setw(35) << left << name << " Roll: " << setw(23) << roll << " |\n";
        cout << "| Semester: " << setw(61) << left << semester << " |\n";
        cout << sep << "\n";
        cout << "| " << setw(48) << left << "Subject Name" << " | " << setw(18) << "Marks" << " |\n";
        cout << "+--------------------------------------------------+--------------------+\n";
        for(int i = 0; i < 10; i++) {
            cout << "| " << setw(48) << left << subjects[semester-1][i] 
                 << " | " << right << setw(10) << marks[i] << "         |\n";
        }
        cout << sep << "\n";
        cout << "| TOTAL: " << setw(12) << total << " | PERCENT: " << setw(10) << percent << "%" 
             << " | CGPA: " << setw(10) << cgpa << " | GRADE: " << setw(2) << grade << " |\n";
        cout << sep << "\n";
        string status = (isPass() ? "PASSED" : "FAILED (Backlog)");
        cout << "| RESULT STATUS: " << setw(54) << left << status << " |\n";
        cout << sep << "\n";
    }

    string toString() {
        stringstream ss;
        ss << roll << "," << name << "," << semester;
        for(int i=0; i<10; i++) ss << "," << marks[i];
        ss << "," << total << "," << percent << "," << cgpa << "," << grade;
        return ss.str();
    }
};

// --- Linked List Global Head ---
Student* head = NULL;

// --- Helper Functions ---
void saveToFile() {
    ofstream f("data.txt");
    Student* temp = head;
    while(temp) {
        f << temp->toString() << endl;
        temp = temp->next;
    }
    f.close();
}

void addStudent() {
    Student* s = new Student();
    s->input();
    s->next = head;
    head = s;
    saveToFile();
    cout << "\n[!] Record Added Successfully!\n";
}

void listAllRecords() {
    if (!head) { cout << "\n[!] No records found.\n"; return; }
    string line = "+----------+---------------------------+-----+-------+---------+-------+";
    cout << "\n" << line << "\n";
    cout << "| ROLL     | NAME                      | SEM | TOTAL | PERCENT | GRADE |\n";
    cout << line << "\n";
    Student* temp = head;
    while(temp) {
        string displayName = (temp->name.length() > 23) ? temp->name.substr(0, 20) + "..." : temp->name;
        cout << "| " << left << setw(8) << temp->roll 
             << " | " << setw(25) << displayName 
             << " | " << setw(3) << temp->semester 
             << " | " << setw(5) << temp->total 
             << " | " << setw(6) << fixed << setprecision(1) << temp->percent << "%"
             << " | " << setw(5) << temp->grade << " |\n";
        temp = temp->next;
    }
    cout << line << "\n";
}

void viewStudent() {
    int r, sem;
    cout << "Enter Roll: "; cin >> r;
    cout << "Enter Semester: "; cin >> sem;
    Student* temp = head;
    while(temp) {
        if(temp->roll == r && temp->semester == sem) { temp->display(); return; }
        temp = temp->next;
    }
    cout << "\n[!] Record Not Found.\n";
}

void deleteStudent() {
    int r, sem;
    cout << "Enter Roll to Delete: "; cin >> r;
    cout << "Enter Semester: "; cin >> sem;
    Student *temp = head, *prev = NULL;
    while(temp) {
        if(temp->roll == r && temp->semester == sem) {
            if(prev) prev->next = temp->next;
            else head = temp->next;
            delete temp;
            saveToFile();
            cout << "\n[!] Record Deleted.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "\n[!] Record Not Found.\n";
}

void loadData() {
    ifstream f("data.txt");
    if(!f) return;
    string line;
    while(getline(f, line)) {
        if(line.empty()) continue;
        Student* s = new Student();
        stringstream ss(line);
        string temp;
        try {
            getline(ss, temp, ','); s->roll = stoi(temp);
            getline(ss, s->name, ',');
            getline(ss, temp, ','); s->semester = stoi(temp);
            for(int i=0; i<10; i++) { getline(ss, temp, ','); s->marks[i] = stoi(temp); }
            getline(ss, temp, ','); s->total = stoi(temp);
            getline(ss, temp, ','); s->percent = stof(temp);
            getline(ss, temp, ','); s->cgpa = stof(temp);
            getline(ss, s->grade, ',');
            s->next = head; head = s;
        } catch(...) { delete s; }
    }
    f.close();
}

void menu() {
    int ch;
    do {
        cout << "\n+================================+\n";
        cout << "|     STUDENT RESULT SYSTEM      |\n";
        cout << "+================================+\n";
        cout << "| 1. Add New Record              |\n";
        cout << "| 2. View Individual Marksheet   |\n";
        cout << "| 3. List All Records (Table)    |\n";
        cout << "| 4. Delete Record               |\n";
        cout << "| 5. Exit and Save               |\n";
        cout << "+--------------------------------+\n";
        cout << "  Choice: ";
        if(!(cin >> ch)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        switch(ch) {
            case 1: addStudent(); break;
            case 2: viewStudent(); break;
            case 3: listAllRecords(); break;
            case 4: deleteStudent(); break;
        }
    } while(ch != 5);
}

int main() {
    loadData();
    menu();
    return 0;
}
