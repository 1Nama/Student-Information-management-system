#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Student {
    string name;
    string father_name;
    string mother_name; // New member for mother's name
    string stu_class;
    string roll_num;
    string dob;
    string sex;
    string phone_num;
    Student* next;
};

Student* head = nullptr;

void border_msg(string msg) {
    int row = msg.size();
    string m = "        +" + string(row, '-') + "+";
    cout << m << '\n' << "        |" + msg + "|" << '\n' << m << endl;
}

void display_menu() {
    border_msg(" Welcome To Student Information System ! ");
    cout << "\nCHOOSE AN OPTION :\n";
    cout << "[1] Add New Student\n";
    cout << "[2] View Students\n";
    cout << "[3] Search Student\n";
    cout << "[4] Update Student\n";
    cout << "[5] Delete Student\n";
    cout << "[6] Quit\n";
}

void clr_scr() {
    if (system("CLS")) system("clear");
}

void continue_msg() {
    cout << "\nPress Enter To Continue : ";
    cin.ignore();
    clr_scr();
}

void validate_name(const string &name) {
    if (any_of(name.begin(), name.end(), ::isdigit)) {
        cout << "\nName Is Invalid! It Should Not Have Digits!" << endl;
        exit(1);
    }
}

void validate_class(const string &value) {
    vector<string> valid_classes = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
    if (find(valid_classes.begin(), valid_classes.end(), value) == valid_classes.end()) {
        cout << "\nInvalid Class!" << endl;
        exit(1);
    }
}

void validate_rollnum(const string &rollnum) {
    try {
        stoi(rollnum);
    } catch (...) {
        cout << "\nRoll Number Must Be A Number!" << endl;
        exit(1);
    }
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool is_valid_date(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) days_in_month[1] = 29;

    return day <= days_in_month[month - 1];
}

void validate_dob(const string &dob) {
    if (dob.size() != 10 || dob[2] != '/' || dob[5] != '/') {
        cout << "\nIncorrect date! Valid Format Is (DD/MM/YYYY)" << endl;
        exit(1);
    }
    int day, month, year;
    try {
        day = stoi(dob.substr(0, 2));
        month = stoi(dob.substr(3, 2));
        year = stoi(dob.substr(6, 4));
    } catch (...) {
        cout << "\nIncorrect date! Valid Format Is (DD/MM/YYYY)" << endl;
        exit(1);
    }

    if (!is_valid_date(day, month, year)) {
        cout << "\nIncorrect date! Valid Format Is (DD/MM/YYYY)" << endl;
        exit(1);
    }
}

void validate_sex(const string &sex) {
    vector<char> valid_sexes = {'M', 'F', 'T', 'm', 'f', 't'};
    if (find(valid_sexes.begin(), valid_sexes.end(), sex[0]) == valid_sexes.end()) {
        cout << "\nInvalid Gender!" << endl;
        exit(1);
    }
}

void validate_phonenum(const string &phonenum) {
    if (phonenum.size() != 10 || any_of(phonenum.begin(), phonenum.end(), ::isalpha)) {
        cout << "\nPhone Number Must Contain 10 Digits and No Letters!" << endl;
        exit(1);
    }
}

bool student_exists(const string &stu_class, const string &roll_num) {
    Student* temp = head;
    while (temp != nullptr) {
        if (temp->stu_class == stu_class && temp->roll_num == roll_num) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void add_student() {
    cout << "\n";
    border_msg(" Add A New Student's Information To Database ");
    cout << "\n";
    string stu_name, stu_father, stu_mother, stu_class, roll_num, stu_dob, stu_sex, phone_num;
    cout << "Student's Name : ";
    getline(cin, stu_name);
    validate_name(stu_name);
    cout << "Father's Name : ";
    getline(cin, stu_father);
    validate_name(stu_father);
    cout << "Mother's Name : "; // New input
    getline(cin, stu_mother);
    validate_name(stu_mother);
    cout << "Class (1-12) : ";
    getline(cin, stu_class);
    validate_class(stu_class);
    cout << "Roll No : ";
    getline(cin, roll_num);
    validate_rollnum(roll_num);
    if (student_exists(stu_class, roll_num)) {
        cout << "\nStudent with this Class and Roll Number already exists!" << endl;
        continue_msg();
        return;
    }
    cout << "DOB (DD/MM/YYYY) : ";
    getline(cin, stu_dob);
    validate_dob(stu_dob);
    cout << "Sex (M/F/T) : ";
    getline(cin, stu_sex);
    validate_sex(stu_sex);
    cout << "Phone No (+91) : ";
    getline(cin, phone_num);
    validate_phonenum(phone_num);

    Student* new_student = new Student{stu_name, stu_father, stu_mother, stu_class, roll_num, stu_dob, stu_sex, phone_num, nullptr};

    if (!head) {
        head = new_student;
    } else {
        Student* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_student;
    }

    cout << "\nData Saved Successfully!" << endl;
    continue_msg();
}

void view_students() {
    cout << "\n";
    border_msg(" Student's Record In Our Information System ");
    if (!head) {
        cout << "\nNo Records Found!" << endl;
        continue_msg();
        return;
    }

    cout << left << setw(20) << "Name" << setw(20) << "Father's Name" << setw(20) << "Mother's Name" << setw(10) << "Class"
         << setw(10) << "Roll No" << setw(15) << "DOB" << setw(5) << "Sex" << setw(15) << "Phone No" << endl;
    cout << string(120, '-') << endl;

    Student* temp = head;
    while (temp) {
        cout << left << setw(20) << temp->name << setw(20) << temp->father_name << setw(20) << temp->mother_name
             << setw(10) << temp->stu_class << setw(10) << temp->roll_num << setw(15) << temp->dob << setw(5) << temp->sex
             << setw(15) << temp->phone_num << endl;
        temp = temp->next;
    }
    continue_msg();
}

void search_student() {
    cout << "\n";
    border_msg(" Search For A Student Inside Database ");
    cout << "\nEnter Class and Roll No. To Search : ";
    string stu_class, roll;
    cout << "Class : ";
    getline(cin, stu_class);
    validate_class(stu_class);
    cout << "Roll No : ";
    getline(cin, roll);
    validate_rollnum(roll);

    if (!head) {
        cout << "\nNo Records To Search!" << endl;
        continue_msg();
        return;
    }

    Student* temp = head;
    bool found = false;
    while (temp) {
        if (temp->stu_class == stu_class && temp->roll_num == roll) {
            found = true;
            cout << "\nStudent Found!" << endl;
            cout << "Name : " << temp->name << endl;
            cout << "Father's Name : " << temp->father_name << endl;
            cout << "Mother's Name : " << temp->mother_name << endl;
            cout << "Class : " << temp->stu_class << endl;
            cout << "Roll No : " << temp->roll_num << endl;
            cout << "DOB : " << temp->dob << endl;
            cout << "Sex : " << temp->sex << endl;
            cout << "Phone No : " << temp->phone_num << endl;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "\nNo Student Found With Class " << stu_class << " And Roll No. " << roll << endl;
    }
    continue_msg();
}

void update_student() {
    cout << "\n";
    border_msg(" Update A Student's Information Inside Database ");
    cout << "\nEnter Class and Roll No. To Update : ";
    string stu_class, roll;
    cout << "Class : ";
    getline(cin, stu_class);
    validate_class(stu_class);
    cout << "Roll No : ";
    getline(cin, roll);
    validate_rollnum(roll);

    if (!head) {
        cout << "\nNo Records To Update!" << endl;
        continue_msg();
        return;
    }

    Student* temp = head;
    bool found = false;
    while (temp) {
        if (temp->stu_class == stu_class && temp->roll_num == roll) {
            found = true;
            cout << "\nStudent Found! Enter New Details :\n";
            cout << "[1] Name\n";
            cout << "[2] Father's Name\n";
            cout << "[3] Mother's Name\n";
            cout << "[4] Class\n";
            cout << "[5] DOB\n";
            cout << "[6] Sex\n";
            cout << "[7] Phone No\n";
            cout << "[8] Cancel\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    cout << "New Name : ";
                    getline(cin, temp->name);
                    validate_name(temp->name);
                    break;
                case 2:
                    cout << "New Father's Name : ";
                    getline(cin, temp->father_name);
                    validate_name(temp->father_name);
                    break;
                case 3:
                    cout << "New Mother's Name : ";
                    getline(cin, temp->mother_name);
                    validate_name(temp->mother_name);
                    break;
                case 4:
                    cout << "New Class (1-12) : ";
                    getline(cin, temp->stu_class);
                    validate_class(temp->stu_class);
                    break;
                case 5:
                    cout << "New DOB (DD/MM/YYYY) : ";
                    getline(cin, temp->dob);
                    validate_dob(temp->dob);
                    break;
                case 6:
                    cout << "New Sex (M/F/T) : ";
                    getline(cin, temp->sex);
                    validate_sex(temp->sex);
                    break;
                case 7:
                    cout << "New Phone No (+91) : ";
                    getline(cin, temp->phone_num);
                    validate_phonenum(temp->phone_num);
                    break;
                case 8:
                    cout << "\nUpdate Cancelled!" << endl;
                    continue_msg();
                    return;
                default:
                    cout << "\nInvalid Choice!" << endl;
                    continue_msg();
                    return;
            }
            cout << "\nData Updated Successfully!" << endl;
            continue_msg();
            return;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "\nNo Student Found With Class " << stu_class << " And Roll No. " << roll << endl;
    }
    continue_msg();
}

void delete_student() {
    cout << "\n";
    border_msg(" Delete A Student's Information Inside Database ");
    cout << "\nEnter Class and Roll No. To Delete : ";
    string stu_class, roll;
    cout << "Class : ";
    getline(cin, stu_class);
    validate_class(stu_class);
    cout << "Roll No : ";
    getline(cin, roll);
    validate_rollnum(roll);

    if (!head) {
        cout << "\nNo Records To Delete!" << endl;
        continue_msg();
        return;
    }

    Student* temp = head;
    Student* prev = nullptr;
    while (temp) {
        if (temp->stu_class == stu_class && temp->roll_num == roll) {
            if (prev) {
                prev->next = temp->next;
            } else {
                head = temp->next;
            }
            delete temp;
            cout << "\nRecord Deleted Successfully!" << endl;
            continue_msg();
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "\nNo Student Found With Class " << stu_class << " And Roll No. " << roll << endl;
    continue_msg();
}

int main() {
    while (true) {
        display_menu();
        cout << "Enter Choice : ";
        int choice;
        cin >> choice;
        cin.ignore();
        clr_scr();
        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                view_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                update_student();
                break;
            case 5:
                delete_student();
                break;
            case 6:
                cout << "\nThank you for using the Student Information System!" << endl;
                exit(0);
            default:
                cout << "\nInvalid Choice!" << endl;
        }
    }
    return 0;
}
