#include <bits/stdc++.h>
using namespace std;
typedef vector<string> vs;
typedef fstream File;
typedef string s;

const string fileName = "StudentData.txt";
const string tempFName = "temp.txt";

File StudentsDataFile;

/***
 *  NEW FUNCTIONS
 *  1. stoi : converts from string to int.
 *  2. istringtream : splits sentence into sepeparate words.
 *  3. Common bugs:
 *   i. Core dumped : consider not reading the empty line. eg: if(ln != "")
 *   ii. Make sure you remember to close the file after opening it.
 ***/
class Student
{
public:
    string names;
    int age = 0;
    int id = 0;
    Student(){};
    Student(int id, string names, int age)
    {
        names = names;
        age = age;
        id = id;
    }

    void printStdDetails()
    {
        cout << "\t\t\t--------------------------------\n\n";
        cout << "\t\t\t----------STUDENT'S DETAILS----------------------\n\n";
        printSingleStdDetails();
    }

    void printSingleStdDetails()
    {
        cout << "Student ID: " << id << endl;
        cout << "Student Name: " << names << endl;
        cout << "Age: " << age << endl;
    }
    void enterSdtDetails()
    {

        int counter = 0;

    fillId:
        cout << "Enter the student's ID: ";
        cin >> id;
        if (id <= 0)
            goto fillId;

        cout << "Enter the student's Names: ";
        cin >> names;

        cout << "Enter the student's Age: ";
        cin >> age;
    }

    string writeInFile()
    {
        return to_string(id) + " " + names + " " + to_string(age) + "\n";
    }

    void setId(int id)
    {
        this->id = id;
    }
};

/*** UTIL FUNCTIONS ****/
/******************************/

/** function to extract words from the line. */
vs findWrdsInLn(string sentence)
{
    istringstream iss(sentence);

    s wd;
    vs words;
    while (iss >> wd)
    {
        words.push_back(wd);
    }
    return words;
}

/** function to open file in different formats*/
bool openFile(string mode)
{
    if (mode == "a")
    {
        StudentsDataFile.open(fileName, ios::app);
    }
    else if (mode == "w")
    {
        StudentsDataFile.open(fileName, ios::out);
    }
    else if (mode == "r")
    {
        StudentsDataFile.open(fileName, ios::in);
    }

    return StudentsDataFile.is_open();
}

/** File to close the file */
void handleCloseFile()
{
    StudentsDataFile.close();
}

/** function to copy contents from the temp file into the main file */
void copyFromTemp()
{
    File tmpF;
    tmpF.open(tempFName, ios::in);
    remove("StudentData.txt");

    if (openFile("a"))
    {
        string ln;
        while (getline(tmpF, ln))
        {
            if (ln != "")
                StudentsDataFile << ln << "\n";
        }
        handleCloseFile();
        tmpF.close();
    }

    remove("temp.txt");
}

/*** OPERATION HANDLING  FUNCTIONS ****/
/******************************/

bool handleAddStudent(Student student)
{
    if (openFile("a"))
    {
        StudentsDataFile << student.writeInFile();
        handleCloseFile();
        return true;
    }
    return false;
}

bool handleUpdateStudent(Student student, int ID)
{
    File NewFile;

    NewFile.open(tempFName, ios::app);

    if (openFile("r"))
    {
        s ln;
        while (getline(StudentsDataFile, ln))
        {
            if (ln != "")
            {
                if (findWrdsInLn(ln)[0] == to_string(ID))
                {
                    NewFile << student.writeInFile() << "\n";
                }
                else
                {
                    NewFile << ln << "\n";
                }
            }
        }
        handleCloseFile();
        NewFile.close();

        copyFromTemp();
        return true;
    }

    return false;
}

Student handleFindStudent(int id)
{
    Student std;
    if (openFile("r"))
    {
        string ln;
        while (getline(StudentsDataFile, ln))
        {
            if (ln != "")
            {
                vs words = findWrdsInLn(ln);
                if (words[0] == to_string(id))
                {
                    std.id = stoi(words[0]);
                    std.names = words[1];
                    std.age = stoi(words[2]);
                    handleCloseFile();
                    return std;
                }
            }
        }
        handleCloseFile();
    }

    return std;
}

void handleReadAllStudents()
{
    if (openFile("r"))
    {
        s ln;
        Student std;
        while (getline(StudentsDataFile, ln))
        {
            if (ln != "")
            {
                vs words = findWrdsInLn(ln);
                std.id = stoi(words[0]);
                std.names = words[1];
                std.age = stoi(words[2]);

                std.printSingleStdDetails();
            }
        }
        handleCloseFile();
    }
}
bool handleDeleteStudent(int id)
{
    File tempF;
    tempF.open(tempFName, ios::app);

    if (openFile("r"))
    {
        string ln;
        while (getline(StudentsDataFile, ln))
        {
            if (findWrdsInLn(ln)[0] != to_string(id))
            {
                tempF << ln;
            }
        }
        tempF.close();
        handleCloseFile();
        copyFromTemp();

        return true;
    }
    return false;
}


/*** RECEIVING THE PREREQUISITES NEEDED BY HANDLING FUNCTIONS ****/
/******************************/


void readAllStudents()
{
    handleReadAllStudents();
}

bool addStudent()
{
    Student std;
    std.enterSdtDetails();
    return handleAddStudent(std);
}

void findStudent()
{
    int id;
    cout << "Enter the stuedent's ID: ";
    cin >> id;
    Student std = handleFindStudent(id);
    std.printStdDetails();
}

bool updateStudent()
{
    Student std;
    std.enterSdtDetails();

    return handleUpdateStudent(std, std.id);
}


bool deleteStudent()
{
    int id;
    cout << " Enter the student's ID: ";
    cin >> id;
    return handleDeleteStudent(id);
}


void getOptions()
{
    cout << " --------------------------------\n\n"
         << " STUDENT MANAGEMENT SYSTEM \n\n"
         << " --------------------------------\n"
         << " 1. ADD NEW STUDENT \n"
         << " 2. FIND STUDENT \n"
         << " 3. READ ALL STUDENTS \n"
         << " 4. UPDATE STUDENT \n"
         << " 5. DELETE STUDENT \n"
         << " --------------------------------\n";

    int option;
    cin >> option;
    switch (option)
    {
    case 1:
        if (addStudent())
            cout << "ADDED SUCCESSFULLY ";
        else
            cout << "ERROR OCCURED TRY AGAIN\n";
        break;
    case 2:
        findStudent();
        break;
    case 3:
        readAllStudents();
        break;
    case 4:
        if (updateStudent())
        {
            cout << "UPDATED SUCCESSFULLY \n\n";
        }
        else
        {
            cout << "SORRY TRY AGAIN ERROR OCCURED";
        }
        break;
    case 5:
        if (deleteStudent())
        {
            cout << "DELETED SUCCESSFULLY ";
        }
        else
        {
            cout << "SORRY TRY AGAIN ERROR OCCURED";
        }
        break;
    default:
        cout << "INVALID TRY AGAIN";
    }
}

int main()
{
    while (1)
    {
        getOptions();
    }

    return 0;
}