#ifndef QUIZ_H_INCLUDED
#define QUIZ_H_INCLUDED
#include <string>
#include <vector>
using namespace std;
class User
{
protected:
    char userid[20];
    char pwd[20];
    char username[50];

public:
    void setUserDetails(string, string, string);
    string getName(string);
    string getName();
    string getUserID();
    int checkUserExist(string);
    void show();
    int input();
};

class Student : public User
{
public:
    void add();
    void Remove();
    void showStudentDetails();
    void quiz();
    void viewPerformance();
};

class Admin : public User
{
public:
    static void createAdmin(string, string, string);
    void addStudent();
    void removeStudent();
    void viewStudent();
    void addQuestion();
    void removeQuestion();
    void viewQuestion();
};

class Question
{
private:
    int quesid;
    int tot_marks;
    char ques[500];
    char op1[100];
    char op2[100];
    char op3[100];
    char op4[100];
    char ans;

public:
    void add();
    void Remove();
    void setQuestionDetails(int, string, string, string, string, string, char);
    void show();
    void viewQuestion();
    void startQuiz(string);
    int quesCount();
};

class StudentPerformance
{
private:
    char studid[20];
    int marks;
    int tot_marks;

public:
    void setMarksDetails(string, int, int);
    void saveMarksDetails();
    void viewDetails(string);
    void show();
};

void mainScreen();
bool isPresent(vector<int> &, int);
#endif // QUIZ_H_INCLUDED
