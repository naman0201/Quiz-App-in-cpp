#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>
#include "conio2.h"
#include "quiz.h"
#include <cstdlib>
#include <time.h>
using namespace std;

void mainScreen()
{
    textcolor(LIGHTGREEN);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    gotoxy(1, 3);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    textcolor(LIGHTRED);
    gotoxy(32, 2);
    cout << "Quiz Application";
    gotoxy(20, 10);
    textcolor(YELLOW);
    cout << "WELCOME TO TECH TEST - QUIZ APPLICATION";
    gotoxy(20, 14);
    textcolor(LIGHTGREEN);
    cout << "TEST YOUR SKILLS! IMPROVE YOUR KNOWLEDGE!";
    textcolor(WHITE);
    gotoxy(1, 20);
    cout << "Press any key to continue" << endl;
    getch();
}

void Admin::createAdmin(string userid, string password, string username)
{
    fstream fobj("../files/Admin.bin", ios::in | ios::binary);
    if (fobj.fail())
    {
        fobj.open("../files/Admin.bin", ios::out | ios::binary);
        Admin adminObj;
        adminObj.setUserDetails(userid, password, username);
        fobj.write((char *)&adminObj, sizeof(Admin));
    }
    fobj.close();
}

void User::setUserDetails(string userid, string pwd, string username)
{
    strcpy(this->userid, userid.c_str());
    strcpy(this->pwd, pwd.c_str());
    strcpy(this->username, username.c_str());
}

int User::input()
{
    clrscr();
    gotoxy(1, 1);
    textcolor(LIGHTGREEN);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    gotoxy(1, 3);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    textcolor(LIGHTRED);
    gotoxy(32, 2);
    cout << "Quiz Application";
    gotoxy(58, 4);
    textcolor(RED);
    cout << "Press 0 to Exit/Go Back";
    gotoxy(1, 8);
    textcolor(YELLOW);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    gotoxy(1, 17);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    gotoxy(32, 11);
    cout << "Enter userid: ";
    textcolor(WHITE);
    cin.getline(userid, 20);
    if (strcmp(userid, "0") == 0)
        return 0;
    textcolor(YELLOW);
    gotoxy(32, 13);
    cout << "Enter password: ";
    textcolor(WHITE);
    char ch;
    int i = 0;
    while (true)
    {
        ch = getch();
        if (ch == 13)
            break;
        if (ch == 8)
        {
            if (i == 0)
                continue;
            cout << "\b \b";
            i--;
            continue;
        }
        cout << ch;
        delay(200);
        cout << "\b*";
        pwd[i] = ch;
        i++;
    }
    pwd[i] = '\0';
    if (strcmp(pwd, "0") == 0)
        return 0;
    return 1;
}

int User::checkUserExist(string usertype)
{
    if (strcmp(userid, "") == 0 || strcmp(pwd, "") == 0)
    {
        gotoxy(28, 24);
        textcolor(LIGHTRED);
        cout << "BOTH THE FIELDS ARE MANDATORY";
        getch();
        return 0;
    }
    ifstream fin;
    User *uptr;
    if (usertype == "admin")
    {
        fin.open("../files/Admin.bin", ios::in | ios::binary);
        uptr = new Admin;
    }
    else if (usertype == "student")
    {
        fin.open("../files/Student.bin", ios::in | ios::binary);
        uptr = new Student;
    }
    else
    {
        gotoxy(28, 24);
        textcolor(LIGHTRED);
        cout << "WRONG USERTYPE PASSED";
        getch();
        return 0;
    }
    bool useridfound = 0, pwdfound = 0;
    while (1)
    {
        fin.read((char *)uptr, sizeof(*uptr));
        if (fin.eof())
            break;
        if (strcmp(userid, uptr->userid) == 0)
        {
            if (strcmp(pwd, uptr->pwd) == 0)
            {
                useridfound = pwdfound = 1;
                break;
            }
            useridfound = 1;
        }
    }
    bool result = 0;
    if (useridfound == 0)
    {
        gotoxy(28, 18);
        textcolor(LIGHTRED);
        cout << "No such user exists!";
        getch();
    }
    else if (pwdfound == 0)
    {
        gotoxy(28, 18);
        textcolor(LIGHTRED);
        cout << "Invalid password!";
        getch();
    }
    else
    {
        result = 1;
        strcpy(username, uptr->username);
    }
    fin.close();
    return result;
}

string User::getName()
{
    string USERNAME(username); // converted character array into string
    return USERNAME;
}
string User::getUserID()
{
    string USERID;
    USERID = userid;
    return USERID;
}
// Admin Module

void Admin::addQuestion()
{
    Question questObj;
    questObj.add();
    clrscr();
}

void Question::add()
{
    char uchoice;
    fstream fout("../files/Question.bin", ios::app | ios::binary | ios::in);
    fout.seekp(0, ios::end);
    string str;
    if (fout.tellg() == 0)
        quesid = 1;
    else
    {
        fout.seekp(-(signed long long int)sizeof(*this), ios::end);
        fout.read((char *)this, sizeof(*this));
        quesid++;
        fout.seekp(0, ios::end);
    }
    do
    {
        clrscr();
        textcolor(WHITE);
        gotoxy(58, 4);
        cout << "Press 0 to Exit/Go Back";
        textcolor(LIGHTGREEN);
        gotoxy(1, 1);
        for (int i = 0; i < 80; i++)
            cout << "*";
        gotoxy(37, 2);
        textcolor(LIGHTRED);
        cout << "QUIZ APP";
        textcolor(LIGHTGREEN);
        gotoxy(1, 3);
        for (int i = 0; i < 80; i++)
            cout << "*";
        textcolor(WHITE);
        gotoxy(25, 5);
        cout << "***** ADD QUESTION DETAILS *****";
        gotoxy(1, 8);
        textcolor(YELLOW);
        cout << "Enter question:";
        cin.ignore();
        textcolor(WHITE);
        getline(cin, str, '*');
        strncpy(ques, str.c_str(), 499);
        if (strcmp(ques, "0") == 0)
        {
            gotoxy(1, 24);
            textcolor(LIGHTRED);
            cout << "Closing add question" << endl;
            getch();
            return;
        }
        textcolor(LIGHTGREEN);
        cout << endl
             << "Carries Marks: " << endl;
        textcolor(YELLOW);
        cin >> tot_marks;
        textcolor(LIGHTGREEN);
        cout << endl
             << "OPTIONS" << endl
             << endl;
        textcolor(YELLOW);
        cout << "(a) ";
        cin.ignore();
        textcolor(WHITE);
        getline(cin, str);
        strncpy(op1, str.c_str(), 99);
        textcolor(YELLOW);
        cout << "(b) ";
        textcolor(WHITE);
        getline(cin, str);
        strncpy(op2, str.c_str(), 99);
        textcolor(YELLOW);
        cout << "(c) ";
        textcolor(WHITE);
        getline(cin, str);
        strncpy(op3, str.c_str(), 99);
        textcolor(YELLOW);
        cout << "(d) ";
        textcolor(WHITE);
        getline(cin, str);
        strncpy(op4, str.c_str(), 99);
        bool valid;
        do
        {
            gotoxy(1, 19);
            textcolor(YELLOW);
            cout << endl
                 << "Enter correct ans(a/b/c/d):  \b";
            textcolor(WHITE);
            cin >> ans;
            if (ans >= 'a' && ans <= 'd')
                valid = true;
            else
            {
                valid = false;
                gotoxy(24, 22);
                textcolor(LIGHTRED);
                cout << "Invalid option entered! please try again.";
                getch();
            }
        } while (valid == false);
        fout.write((char *)this, sizeof(*this));
        quesid++;
        gotoxy(24, 22);
        printf("\t\t\t\t\t\t");
        gotoxy(34, 22);
        textcolor(LIGHTGREEN);
        cout << "QUESTION ADDEDD SUCCESSFULLY";
        getch();
        gotoxy(1, 24);
        textcolor(LIGHTRED);
        cout << endl
             << "Do you want to add more questions(Y/N) :";
        textcolor(WHITE);
        cin >> uchoice;
    } while (uchoice == 'Y' || uchoice == 'y');
    fout.close();
}

void Admin::viewQuestion()
{
    Question quesObj;
    quesObj.viewQuestion();
    clrscr();
}

void Question::viewQuestion()
{
    ifstream fin("../files/Question.bin", ios::in | ios::binary);
    if (!fin)
    {
        gotoxy(32, 18);
        textcolor(LIGHTRED);
        cout << "No questions have been added yet!";
        getch();
        return;
    }
    fin.seekg(0, ios::end);
    if (fin.tellg() == 0)
    {
        gotoxy(32, 18);
        textcolor(LIGHTRED);
        cout << "No questions present in the file!";
        getch();
        return;
    }
    clrscr();
    fin.seekg(0);
    while (1)
    {
        textcolor(LIGHTGREEN);
        gotoxy(1, 1);
        for (int i = 1; i <= 80; i++)
            cout << "*";
        gotoxy(1, 3);
        for (int i = 1; i <= 80; i++)
            cout << "*";
        gotoxy(32, 2);
        textcolor(LIGHTRED);
        cout << "QUIZ APP";
        gotoxy(25, 5);
        textcolor(WHITE);
        cout << "***** SHOW QUESTION DETAILS *****";
        gotoxy(1, 7);
        for (int i = 1; i <= 80; i++)
            cout << "*";
        fin.read((char *)this, sizeof(*this));
        if (fin.eof())
        {
            gotoxy(25, 12);
            textcolor(LIGHTBLUE);
            cout << "NO MORE QUESTIONS";
            getch();
            break;
        }
        else
        {
            show();
            getch();
            clrscr();
        }
    }
    fin.close();
}

void Question::show()
{
    gotoxy(1, 9);
    textcolor(YELLOW);
    cout << "Q. " << quesid << "      " << ques << endl;
    cout << "Carries Marks: " << tot_marks << endl;
    cout << "a. " << op1 << endl;
    cout << "b. " << op2 << endl;
    cout << "c. " << op3 << endl;
    cout << "d. " << op4 << endl
         << endl;
    textcolor(LIGHTGREEN);
    cout << "Correct Option : " << ans;
}

void Admin::removeQuestion()
{
    Question quesObj;
    quesObj.Remove();
    clrscr();
}

void Question::Remove()
{
    clrscr();
    textcolor(WHITE);
    gotoxy(58, 4);
    cout << "Press 0 to Exit/Go Back";
    textcolor(LIGHTGREEN);
    gotoxy(1, 1);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    gotoxy(1, 3);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    gotoxy(32, 2);
    textcolor(LIGHTRED);
    cout << "QUIZ APP";
    gotoxy(25, 5);
    textcolor(WHITE);
    cout << "***** REMOVE QUESTION DETAILS *****";

    ifstream fin("../files/Question.bin", ios::in | ios::binary);
    if (!fin)
    {
        gotoxy(35, 10);
        textcolor(LIGHTRED);
        cout << "Sorry! File cannot be opened";
        getch();
        return;
    }
    fin.seekg(0, ios::end);
    if (fin.tellg() == 0)
    {
        gotoxy(32, 18);
        textcolor(LIGHTRED);
        cout << "No questions available for deletion!";
        getch();
        fin.close();
        return;
    }
    gotoxy(1, 8);
    textcolor(YELLOW);
    cout << "Enter Question ID:";
    bool found = false, valid;
    int id;
    ofstream fout("../files/temp.bin", ios::out | ios::binary);
    if (!fout)
    {
        gotoxy(35, 10);
        textcolor(LIGHTRED);
        cout << "Sorry! Removal not possible";
        getch();
        fin.close();
        return;
    }
    fin.seekg(0);
    do
    {
        valid = true;
        cin >> id;
        if (id == 0)
        {
            fin.close();
            fout.close();
            remove("../files/temp.bin");
            return;
        }
        if (id < 0)
        {
            valid = false;
            gotoxy(1, 24);
            textcolor(LIGHTRED);
            cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\r Invalid Question ID";
            getch();
            gotoxy(19, 8);
            cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
            gotoxy(19, 8);
        }
        else
        {
            while (true)
            {
                fin.read((char *)this, sizeof(*this));
                if (fin.eof())
                    break;
                if (this->quesid == id)
                {
                    found = true;
                    continue;
                }
                else
                {
                    fout.write((char *)this, sizeof(*this));
                }
            }
            fin.close();
            fout.close();
            if (found)
            {
                textcolor(WHITE);
                gotoxy(1, 24);
                cout << "\t\t\t\t\t\t\t\t\t\t\t\rQuestion Removed Successfully";
                getch();
                remove("../files/Question.bin");
                rename("../files/temp.bin", "../files/Question.bin");
            }
            else
            {
                textcolor(LIGHTRED);
                gotoxy(1, 24);
                cout << "\t\t\t\t\t\t\t\t\t\t\t\rQuestion Id Not Found";
                remove("../files/temp.bin");
                getch();
            }
        }
    } while (valid == false);
}

void Admin::addStudent()
{
    Student studobj;
    studobj.add();
    clrscr();
}

void Student::add()
{
    char uchoice;
    int id;
    char stuid[10];
    string str;
    fstream fobj("../files/Student.bin", ios::app | ios::binary | ios::in);
    fobj.seekp(0, ios::end);
    if (!fobj)
    {
        gotoxy(32, 18);
        textcolor(LIGHTRED);
        cout << "Sorry! File cannot be opened";
        getch();
        return;
    }
    fobj.seekg(0, ios::end);
    if (fobj.tellg() == 0)
        id = 1;
    else
    {
        fobj.seekp(-(signed long long int)sizeof(*this), ios::end);
        fobj.read((char *)this, sizeof(*this));
        char *pos = strchr(userid, '-');
        if (pos != NULL)
        {
            id = atoi(pos + 1);
            id++;
        }
        fobj.seekp(0, ios::end);
    }
    cout << "Next id is:" << id;
    getch();
    fobj.seekg(0, ios::end);
    do
    {
        clrscr();
        textcolor(WHITE);
        gotoxy(58, 4);
        cout << "Press 0 to Exit/Go Back";
        textcolor(LIGHTGREEN);
        gotoxy(1, 1);
        for (int i = 1; i <= 80; i++)
            cout << "*";
        gotoxy(1, 3);
        for (int i = 1; i <= 80; i++)
            cout << "*";
        gotoxy(32, 2);
        textcolor(LIGHTRED);
        cout << "QUIZ APP";
        gotoxy(25, 5);
        textcolor(WHITE);
        cout << "***** ADD STUDENTS DETAILS *****";
        gotoxy(1, 8);
        textcolor(YELLOW);
        cout << "Enter Student Name: ";
        cin.ignore();
        textcolor(WHITE);
        getline(cin, str);
        strncpy(username, str.c_str(), 19);
        if (strcmp(username, "0") == 0)
        {
            gotoxy(1, 24);
            textcolor(LIGHTRED);
            cout << "Closing add student" << endl;
            getch();
            fobj.close();
            return;
        }
        textcolor(YELLOW);
        cout << "Enter Student Password: ";
        textcolor(WHITE);
        getline(cin, str);
        strncpy(pwd, str.c_str(), 19);
        if (strcmp(pwd, "0") == 0)
        {
            gotoxy(1, 24);
            textcolor(LIGHTRED);
            cout << "Closing add student" << endl;
            getch();
            fobj.close();
            return;
        }
        sprintf(stuid, "STU-%d", id);
        strcpy(userid, stuid);
        fobj.write((char *)this, sizeof(*this));
        gotoxy(30, 15);
        textcolor(LIGHTGREEN);
        cout << "STUDENT ADDED SUCCESSFULL!";
        cout << endl
             << "STUDENT ID IS :" << userid;
        getch();
        gotoxy(1, 20);
        textcolor(LIGHTBLUE);
        cout << "Do you want to add more students (Y/N)";
        textcolor(WHITE);
        cin >> uchoice;
        id++;
    } while (uchoice == 'y' || uchoice == 'Y');
    fobj.close();
}

void Admin::viewStudent()
{
    Student studObj;
    studObj.showStudentDetails();
    clrscr();
}

void Student::showStudentDetails()
{
    ifstream fin("../files/Student.bin", ios::in | ios::binary);
    if (!fin)
    {
        gotoxy(32, 18);
        textcolor(LIGHTRED);
        cout << "No Students have been added yet!";
        getch();
        return;
    }
    fin.seekg(0, ios::end);
    if (fin.tellg() == 0)
    {
        gotoxy(32, 18);
        textcolor(LIGHTRED);
        cout << "No students present in the file!";
        getch();
        return;
    }
    clrscr();
    fin.seekg(0);
    while (1)
    {
        textcolor(LIGHTGREEN);
        gotoxy(1, 1);
        for (int i = 1; i <= 80; i++)
            cout << "*";
        gotoxy(1, 3);
        for (int i = 1; i <= 80; i++)
            cout << "*";
        gotoxy(32, 2);
        textcolor(LIGHTRED);
        cout << "QUIZ APP";
        gotoxy(25, 5);
        textcolor(WHITE);
        cout << "***** SHOW STUDENT DETAILS *****";
        gotoxy(1, 7);
        for (int i = 1; i <= 80; i++)
            cout << "*";
        fin.read((char *)this, sizeof(*this));
        if (fin.eof())
        {
            gotoxy(25, 12);
            textcolor(LIGHTBLUE);
            cout << "NO MORE STUDENTS PRESENT!";
            getch();
            break;
        }
        else
        {
            show();
            getch();
            clrscr();
        }
    }
    fin.close();
}
void User::show()
{
    gotoxy(1, 9);
    textcolor(YELLOW);
    cout << "User Id:";
    textcolor(LIGHTGREEN);
    cout << userid << endl;

    textcolor(YELLOW);
    cout << "User Name:";
    textcolor(LIGHTGREEN);
    cout << username << endl;

    textcolor(YELLOW);
    cout << "Password:";
    textcolor(LIGHTGREEN);
    cout << pwd << endl;
}

void Admin::removeStudent()
{
    Student stdObj;
    stdObj.Remove();
    clrscr();
}

void Student::Remove()
{
    clrscr();
    textcolor(WHITE);
    gotoxy(58, 4);
    cout << "Press 0 to Exit/Go Back";
    textcolor(LIGHTGREEN);
    gotoxy(1, 1);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    gotoxy(1, 3);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    gotoxy(32, 2);
    textcolor(LIGHTRED);
    cout << "QUIZ APP";
    gotoxy(25, 5);
    textcolor(WHITE);
    cout << "***** REMOVE STUDENT DETAILS *****";

    ifstream fin("../files/Student.bin", ios::in | ios::binary);
    if (!fin)
    {
        gotoxy(35, 10);
        textcolor(LIGHTRED);
        cout << "Sorry! File cannot be opened";
        getch();
        return;
    }
    fin.seekg(0, ios::end);
    if (fin.tellg() == 0)
    {
        gotoxy(32, 18);
        textcolor(LIGHTRED);
        cout << "No student available for deletion!";
        getch();
        fin.close();
        return;
    }
    gotoxy(1, 8);
    textcolor(YELLOW);
    cout << "Enter Student ID:";
    bool found = false;
    string id;
    ofstream fout("../files/temp.bin", ios::out | ios::binary);
    if (!fout)
    {
        gotoxy(35, 10);
        textcolor(LIGHTRED);
        cout << "Sorry! Removal not possible";
        getch();
        fin.close();
        return;
    }
    fin.seekg(0, ios::beg);
    cin.ignore();
    getline(cin, id);
    if (strcmp(id.c_str(), "0") == 0)
    {
        fin.close();
        fout.close();
        remove("../files/temp.bin");
        return;
    }
    else
    {
        while (true)
        {
            fin.read((char *)this, sizeof(*this));
            if (fin.eof())
                break;
            if (strcmp(userid, id.c_str()) == 0)
            {
                found = true;
                continue;
            }
            else
            {
                fout.write((char *)this, sizeof(*this));
            }
        }
        fin.close();
        fout.close();
        if (found)
        {
            textcolor(WHITE);
            gotoxy(1, 24);
            cout << "\t\t\t\t\t\t\t\t\t\t\t\rStudent Removed Successfully";
            remove("../files/Student.bin");
            rename("../files/temp.bin", "../files/Student.bin");
            getch();
        }
        else
        {
            textcolor(LIGHTRED);
            gotoxy(1, 24);
            cout << "\t\t\t\t\t\t\t\t\t\t\t\rStudent Id Not Found";
            remove("../files/temp.bin");
            getch();
        }
    }
}

// Student Module

void Student::quiz()
{
    Question quesObj;
    quesObj.startQuiz(userid);
}

void Question::startQuiz(string id)
{
    ifstream fin("../files/Question.bin", ios::in | ios::binary);
    if (!fin)
    {
        gotoxy(28, 20);
        textcolor(LIGHTRED);
        cout << "No Questions Have Been Added Yet!";
        getch();
        return;
    }
    vector<Question> vecQues;
    while (true)
    {
        fin.read((char *)this, sizeof(*this));
        if (fin.eof())
            break;
        vecQues.push_back(*this);
    }
    fin.close();
    vector<int> vecRand;
    srand((unsigned int)time(NULL));
    int randno;
    while (true)
    {
        randno = rand() % vecQues.size();
        if (!isPresent(vecRand, randno))
        {
            vecRand.push_back(randno);
        }
        if (vecQues.size() == vecRand.size())
            break;
    }
    int count = 0;
    int local_marks = 0;
    int local_tot_marks = 0;
    User userObj;
    string name = userObj.getName(id);
    for (int i = 0; i < (int)vecQues.size(); i++)
    {
        int index = vecRand.at(i);
        *this = vecQues.at(index);
        clrscr();
        gotoxy(37, 2);
        textcolor(LIGHTRED);
        cout << "QUIZ APP";
        textcolor(YELLOW);
        gotoxy(1, 4);
        for (int j = 0; j < 80; j++)
            cout << "*";
        textcolor(WHITE);
        gotoxy(50, 5);
        cout << name;
        gotoxy(10, 5);
        cout << "TOTAL QUESTION: " << vecQues.size() << endl;
        gotoxy(1, 6);
        textcolor(YELLOW);
        for (int j = 0; j < 80; j++)
            cout << "*";
        textcolor(GREEN);
        gotoxy(1, 8);
        count++;
        cout << count << ")";
        gotoxy(4, 8);
        cout << this->ques << endl
             << endl;
        textcolor(LIGHTGRAY);
        cout << "a." << this->op1 << endl
             << endl;
        cout << "b." << this->op2 << endl
             << endl;
        cout << "c." << this->op3 << endl
             << endl;
        cout << "d." << this->op4 << endl
             << endl;
        bool valid;
        char uans;
        do
        {
            textcolor(YELLOW);
            cout << "Enter your option(a/b/c/d):  \b";
            cin >> uans;

            if (uans >= 'a' && uans <= 'd')
                valid = true;
            else
            {
                valid = false;
                gotoxy(24, 22);
                textcolor(LIGHTRED);
                cout << "Invalid option entered. Try again";
                getch();
                gotoxy(24, 22);
                cout << "\t\t\t\t\t\t\t\t\t";
                gotoxy(1, 18);
            }
        } while (!valid);
        local_tot_marks += this->tot_marks;
        if (uans == this->ans)
            local_marks += this->tot_marks;
    }
    clrscr();
    gotoxy(37, 2);
    textcolor(LIGHTRED);
    cout << "QUIZ APP";
    textcolor(YELLOW);
    gotoxy(1, 4);
    for (int i = 1; i <= 80; i++)
        cout << "*";
    gotoxy(32, 10);
    textcolor(LIGHTRED);
    cout << "** TEST FINISHED **";
    gotoxy(22, 12);
    cout << "PRESS ANY KEY TO GO BACK TO MAIN MENY";
    getch();
    StudentPerformance sp;
    sp.setMarksDetails(id, local_marks, local_tot_marks);
    fin.close();
}

bool isPresent(vector<int> &vec, int r)
{
    for (int i = 0; i < (int)vec.size(); i++)
    {
        if (vec.at(i) == r)
        {
            return true;
        }
    }
    return false;
}

void StudentPerformance::setMarksDetails(string id, int marks, int tot_marks)
{
    strcpy(studid, id.c_str());
    this->marks = marks;
    this->tot_marks = tot_marks;
    saveMarksDetails();
}

void StudentPerformance::saveMarksDetails()
{
    ofstream fout("../files/Performance.bin", ios::app | ios::binary);
    if (!fout)
    {
        cout << "Error in creating/opening file";
        getch();
        return;
    }
    fout.write((char *)this, sizeof(*this));
    fout.close();
}

string User::getName(string id)
{
    ifstream fin("../files/Student.bin", ios::in | ios::binary);
    while (1)
    {
        fin.read((char *)this, sizeof(User));
        if (fin.eof())
        {
            cout << "No match of record found";
            break;
        }
        int result = strcmp(this->getUserID().c_str(), id.c_str());
        if (result == 0)
        {
            fin.close();
            return this->username;
        }
    }
    fin.close();
    return NULL;
}

void Student::viewPerformance()
{
    StudentPerformance studPerObj;
    studPerObj.viewDetails(userid);
}
void StudentPerformance::viewDetails(string id)
{
    ifstream fin("../files/Performance.bin", ios::in | ios::binary);
    if (!fin)
    {
        gotoxy(28, 20);
        textcolor(LIGHTRED);
        cout << "No Attempts Have Been Made Yet!";
        getch();
        return;
    }
    int attempts = 0;
    User userObj;
    string name = userObj.getName(id);
    bool found = false;
    while (true)
    {
        clrscr();
        gotoxy(37, 2);
        textcolor(LIGHTRED);
        cout << "QUIZ APP";
        textcolor(YELLOW);
        gotoxy(1, 4);
        for (int j = 0; j < 80; j++)
            cout << "*";
        textcolor(WHITE);
        gotoxy(50, 5);
        cout << name;
        attempts++;
        gotoxy(10, 5);
        cout << "ATTEMPT: " << attempts << endl;
        gotoxy(1, 6);
        textcolor(YELLOW);
        for (int j = 0; j < 80; j++)
            cout << "*";

        fin.read((char *)this, sizeof(*this));
        if (fin.eof())
        {
            clrscr();
            gotoxy(25, 12);
            textcolor(LIGHTBLUE);
            cout << "NO MORE ATTEMPTS RECORD PRESENT!";
            getch();
            break;
        }
        else if (strcmp(id.c_str(), this->studid) == 0)
        {
            found = true;
            show();
            getch();
            clrscr();
        }
    }
    if (!found)
    {
        gotoxy(28, 13);
        textcolor(LIGHTRED);
        cout << "PLEASE ATTEMPT TEST FIRST";
        getch();
    }
    fin.close();
}

void StudentPerformance::show()
{
    textcolor(YELLOW);
    gotoxy(1, 8);
    cout << "Marks Obtained:";
    textcolor(LIGHTGREEN);
    cout << marks << endl
         << endl;

    textcolor(YELLOW);
    cout << "Total Marks :";
    textcolor(LIGHTGREEN);
    cout << tot_marks;
}
