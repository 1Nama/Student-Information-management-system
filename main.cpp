#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    string father_name;
    string mother_name;
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

void validate_name(string &name) {
    while (any_of(name.begin(), name.end(), ::isdigit)) {
        cout << "\nName is invalid! It should not have digits. Please enter again: ";
        getline(cin, name);
    }
}

void validate_class(string &value) {
    vector<string> valid_classes = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
    while (find(valid_classes.begin(), valid_classes.end(), value) == valid_classes.end()) {
        cout << "\nInvalid class! Please enter again: ";
        getline(cin, value);
    }
}

void validate_rollnum(string &rollnum) {
    while (true) {
        try {
            stoi(rollnum);
            break;
        } catch (...) {
            cout << "\nRoll number must be a number! Please enter again: ";
            getline(cin, rollnum);
        }
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

void validate_dob(string &dob) {
    while (true) {
        if (dob.size() != 10 || dob[2] != '/' || dob[5] != '/') {
            cout << "\nIncorrect date! Valid format is (DD/MM/YYYY). Please enter again: ";
            getline(cin, dob);
            continue;
        }
        int day, month, year;
        try {
            day = stoi(dob.substr(0, 2));
            month = stoi(dob.substr(3, 2));
            year = stoi(dob.substr(6, 4));
        } catch (...) {
            cout << "\nIncorrect date! Valid format is (DD/MM/YYYY). Please enter again: ";
            getline(cin, dob);
            continue;
        }

        if (!is_valid_date(day, month, year)) {
            cout << "\nIncorrect date! Valid format is (DD/MM/YYYY). Please enter again: ";
            getline(cin, dob);
        } else {
            break;
        }
    }
}

void validate_sex(string &sex) {
    vector<char> valid_sexes = {'M', 'F', 'T', 'm', 'f', 't'};
    while (find(valid_sexes.begin(), valid_sexes.end(), sex[0]) == valid_sexes.end()) {
        cout << "\nInvalid gender! Please enter (M/F/T): ";
        getline(cin, sex);
    }
}

void validate_phonenum(string &phonenum) {
    while (phonenum.size() != 10 || any_of(phonenum.begin(), phonenum.end(), ::isalpha)) {
        cout << "\nPhone number must contain 10 digits and no letters! Please enter again: ";
        getline(cin, phonenum);
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
    cout << "Mother's Name : "; 
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
    border_msg(" List of Students ");
    cout << "\n";
    Student* temp = head;
    if (!temp) {
        cout << "No students found!" << endl;
    } else {
        cout << left << setw(15) << "Name" << setw(15) << "Class" << setw(15) << "Roll No" << setw(15) << "DOB" << setw(15) << "Sex" << setw(15) << "Phone" << endl;
        cout << string(90, '-') << endl;
        while (temp) {
            cout << left << setw(15) << temp->name << setw(15) << temp->stu_class << setw(15) << temp->roll_num << setw(15) << temp->dob << setw(15) << temp->sex << setw(15) << temp->phone_num << endl;
            temp = temp->next;
        }
    }
    continue_msg();
}

void search_student() {
    cout << "\n";
    border_msg(" Search Student ");
    cout << "\n";
    string stu_class, roll_num;
    cout << "Enter Class : ";
    getline(cin, stu_class);
    validate_class(stu_class);
    cout << "Enter Roll No : ";
    getline(cin, roll_num);
    validate_rollnum(roll_num);

    Student* temp = head;
    bool found = false;
    while (temp) {
        if (temp->stu_class == stu_class && temp->roll_num == roll_num) {
            cout << "\nStudent Found!" << endl;
            cout << "Name       : " << temp->name << endl;
            cout << "Father's Name : " << temp->father_name << endl;
            cout << "Mother's Name : " << temp->mother_name << endl;
            cout << "Class      : " << temp->stu_class << endl;
            cout << "Roll No    : " << temp->roll_num << endl;
            cout << "DOB        : " << temp->dob << endl;
            cout << "Sex        : " << temp->sex << endl;
            cout << "Phone No   : " << temp->phone_num << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "\nStudent Not Found!" << endl;
    }
    continue_msg();
}

void update_student() {
    cout << "\n";
    border_msg(" Update Student Information ");
    cout << "\n";
    string stu_class, roll_num;
    cout << "Enter Class : ";
    getline(cin, stu_class);
    validate_class(stu_class);
    cout << "Enter Roll No : ";
    getline(cin, roll_num);
    validate_rollnum(roll_num);

    Student* temp = head;
    while (temp) {
        if (temp->stu_class == stu_class && temp->roll_num == roll_num) {
            cout << "\nEnter New Data (Leave blank to keep current value):\n";
            string new_name, new_father, new_mother, new_dob, new_sex, new_phone;
            cout << "Name (" << temp->name << "): ";
            getline(cin, new_name);
            if (!new_name.empty()) {
                validate_name(new_name);
                temp->name = new_name;
            }
            cout << "Father's Name (" << temp->father_name << "): ";
            getline(cin, new_father);
            if (!new_father.empty()) {
                validate_name(new_father);
                temp->father_name = new_father;
            }
            cout << "Mother's Name (" << temp->mother_name << "): ";
            getline(cin, new_mother);
            if (!new_mother.empty()) {
                validate_name(new_mother);
                temp->mother_name = new_mother;
            }
            cout << "DOB (" << temp->dob << "): ";
            getline(cin, new_dob);
            if (!new_dob.empty()) {
                validate_dob(new_dob);
                temp->dob = new_dob;
            }
            cout << "Sex (" << temp->sex << "): ";
            getline(cin, new_sex);
            if (!new_sex.empty()) {
                validate_sex(new_sex);
                temp->sex = new_sex;
            }
            cout << "Phone No (" << temp->phone_num << "): ";
            getline(cin, new_phone);
            if (!new_phone.empty()) {
                validate_phonenum(new_phone);
                temp->phone_num = new_phone;
            }
            cout << "\nStudent Data Updated Successfully!" << endl;
            continue_msg();
            return;
        }
        temp = temp->next;
    }
    cout << "\nStudent Not Found!" << endl;
    continue_msg();
}

void delete_student() {
    cout << "\n";
    border_msg(" Delete Student ");
    cout << "\n";
    string stu_class, roll_num;
    cout << "Enter Class : ";
    getline(cin, stu_class);
    validate_class(stu_class);
    cout << "Enter Roll No : ";
    getline(cin, roll_num);
    validate_rollnum(roll_num);

    if (!head) {
        cout << "\nNo students to delete!" << endl;
        continue_msg();
        return;
    }

    if (head->stu_class == stu_class && head->roll_num == roll_num) {
        Student* to_delete = head;
        head = head->next;
        delete to_delete;
        cout << "\nStudent Deleted Successfully!" << endl;
        continue_msg();
        return;
    }

    Student* temp = head;
    while (temp->next && (temp->next->stu_class != stu_class || temp->next->roll_num != roll_num)) {
        temp = temp->next;
    }

    if (temp->next) {
        Student* to_delete = temp->next;
        temp->next = temp->next->next;
        delete to_delete;
        cout << "\nStudent Deleted Successfully!" << endl;
    } else {
        cout << "\nStudent Not Found!" << endl;
    }
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
