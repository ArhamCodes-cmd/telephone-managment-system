#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string fname, lname, phone_num;

void addContact();
void searchContact();
void help();
void self_exit();
bool check_digits(string);
bool check_numbers(string);
void delete_contact();
void editContact();

int main()
{
    short int choice;
    system("cls");
    system("color 8E");
    cout << "\n\n\n\t\t\tContact Management.";
    cout << "\n\n\t1. Add Contact\n\t2. Search Contact\n\t3. Help\n\t4. Exit\n\t5. Edit Contact\n\t6. Delete Contact\n\t> ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            addContact();
            break;
        case 2:
            searchContact();
            break;
        case 3:
            help();
            break;
        case 4:
            self_exit();
            break;
        case 5:
            editContact();
            break;
        case 6:
            delete_contact();
            break;
        default:
            cout << "\n\n\tInvalid Input !";
            cout << "\n\tPress Any Key To Continue..";
            cin.ignore();
            cin.get();
            main();
    }
    return 0;
}

void self_exit()
{
    system("cls");
    cout << "\n\n\n\t\tThank You For Using !";
    exit(1);
}

void help()
{
    cout << "This program is used to manage contacts in a simple contact management system.";
    cout << "\nYou can add, search, edit, or delete contacts using the options provided.";
    cout << "\n\n\tPress Any Key To Continue..";
    cin.ignore();
    cin.get();
    main();
}

void addContact()
{
    ofstream phone("number.txt", ios::app);
    system("cls");
    cout << "\n\n\tEnter First Name: ";
    cin >> fname;
    cout << "\n\tEnter Last Name: ";
    cin >> lname;
    cout << "\n\tEnter 11-Digit Phone Number: ";
    cin >> phone_num;

    if(check_digits(phone_num))
    {
        if(check_numbers(phone_num))
        {
            if(phone.is_open())
            {
                phone << fname << " " << lname << " " << phone_num << endl;
                cout << "\n\tContact Saved Successfully!";
            }
            else
            {
                cout << "\n\tError Opening File!";
            }
        }
        else
        {
            cout << "\n\tA Phone Number Must Contain Numbers Only!";
        }
    }
    else
    {
        cout << "\n\tA Phone Number Must Contain 11 Digits.";
    }
    phone.close();
    cout << "\n\tPress Any Key To Continue..";
    cin.ignore();
    cin.get();
    main();
}

void searchContact()
{
    system("cls");
    bool found = false;
    ifstream myfile("number.txt");
    string keyword;
    cout << "\n\tEnter Name To Search: ";
    cin >> keyword;
    while(myfile >> fname >> lname >> phone_num)
    {
        if(keyword == fname || keyword == lname)
        {
            system("cls");
            cout << "\n\n\n\t\tContact Details..";
            cout << "\n\n\tFirst Name : " << fname;
            cout << "\n\tLast Name : " << lname;
            cout << "\n\tPhone Number : " << phone_num;
            found = true;
            break;
        }
    }
    if(!found)
    {
        cout << "\n\tNo Such Contact Found";
    }
    myfile.close();
    cout << "\n\tPress Any Key To Continue..";
    cin.ignore();
    cin.get();
    main();
}

bool check_digits(string x)
{
    return x.length() == 11;
}

bool check_numbers(string x)
{
    for(char c : x)
    {
        if(!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

void delete_contact()
{
    system("cls");
    ifstream myfile("number.txt");
    ofstream tempfile("temp.txt");
    string keyword;
    bool found = false;

    if(!myfile.is_open() || !tempfile.is_open())
    {
        cout << "\n\tError Opening File!";
        return;
    }

    cout << "\n\tEnter Name To Search for Deletion: ";
    cin >> keyword;
    while(myfile >> fname >> lname >> phone_num)
    {
        if(keyword == fname || keyword == lname)
        {
            cout << "\n\n\tContact Found!";
            cout << "\n\n\tFirst Name : " << fname;
            cout << "\n\tLast Name : " << lname;
            cout << "\n\tPhone Number : " << phone_num;
            found = true;
        }
        else
        {
            tempfile << fname << " " << lname << " " << phone_num << endl;
        }
    }

    if(!found)
    {
        cout << "\n\tNo Such Contact Found";
    }
    else
    {
        cout << "\n\tContact Deleted Successfully!";
    }

    myfile.close();
    tempfile.close();
    remove("number.txt");
    rename("temp.txt", "number.txt");

    cout << "\n\tPress Any Key To Continue..";
    cin.ignore();
    cin.get();
    main();
}

void editContact()
{
    system("cls");
    ifstream myfile("number.txt");
    ofstream tempfile("temp.txt");
    string keyword;
    bool found = false;

    if(!myfile.is_open() || !tempfile.is_open())
    {
        cout << "\n\tError Opening File!";
        return;
    }

    cout << "\n\tEnter Name To Search for Editing: ";
    cin >> keyword;
    while(myfile >> fname >> lname >> phone_num)
    {
        if(keyword == fname || keyword == lname)
        {
            cout << "\n\n\tContact Found!";
            cout << "\n\n\tFirst Name : " << fname;
            cout << "\n\tLast Name : " << lname;
            cout << "\n\tPhone Number : " << phone_num;

            cout << "\n\n\tEnter New First Name: ";
            cin >> fname;
            cout << "\n\tEnter New Last Name: ";
            cin >> lname;
            cout << "\n\tEnter New 11-Digit Phone Number: ";
            cin >> phone_num;

            if(check_digits(phone_num) && check_numbers(phone_num))
            {
                tempfile << fname << " " << lname << " " << phone_num << endl;
                cout << "\n\tContact Edited Successfully!";
            }
            else
            {
                cout << "\n\tInvalid Phone Number!";
                tempfile << fname << " " << lname << " " << phone_num << endl;
            }

            found = true;
        }
        else
        {
            tempfile << fname << " " << lname << " " << phone_num << endl;
        }
    }

    if(!found)
    {
        cout << "\n\tNo Such Contact Found";
    }

    myfile.close();
    tempfile.close();
    remove("number.txt");
    rename("temp.txt", "number.txt");

    cout << "\n\tPress Any Key To Continue..";
    cin.ignore();
    cin.get();
    main();
}
