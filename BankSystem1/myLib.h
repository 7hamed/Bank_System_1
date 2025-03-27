#pragma once


#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


namespace mystd
{

    int readNumber(string Message)
    {
        int num;

        cout << Message;
        cin >> num;

        while (cin.fail()) // validation number
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "EROR, " + Message;
            cin >> num;
        }

        return num;
    }


    int readPozitifNumber(string Message) // read from user a pozitif number
    {
        int num;

        do {
            cout << Message;
            cin >> num;

            while (cin.fail()) // validation number
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "EROR, " + Message;
                cin >> num;
            }

        } while (num < 0); // should be positive number

        return num;
    }


    int generateRandomNumber(int From = 10, int To = 99) // default parameters 10-99 random number
    {
        return rand() % (To - From + 1) + From;
    }


    bool checkPrimeNumber(int number) // check prime number 
    {
        for (int i = 2; i < floor(number / 2); i++)
        {
            if (number % i == 0)
                return false;
        }

        return true;
    }


    void swap(int& first, int& second) // swap numbers
    {
        int temp = first;
        first = second;
        second = temp;
    }


    int reverseNumber(int number)
    {
        int remainder = 0;
        int reverse = 0;

        while (number > 0)
        {
            remainder = number % 10;
            number = number / 10;
            reverse = reverse * 10 + remainder;
        }

        return reverse;
    }


    bool isPalindrom(int number)
    {
        return (number == reverseNumber(number));
    }


    string readString(string message)
    {
        string newLine;

        cout << message;
        getline(cin, newLine);

        return newLine;
    }

    bool isVowel(char c)
    {
        char letter = tolower(c);

        return (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u');
    }

    string trimLeft(string s)
    {
        short i = 0;
        while (s[i] == ' ')
            i++;

        return s.erase(0, i);
    }

    string trimRight(string s)
    {
        short i = s.length() - 1;
        while (s[i] == ' ')
            i--;

        return s.erase(i + 1, s.length());
    }

    string trim(string s)
    {
        return trimLeft(trimRight(s));
    }

    vector<string> splitString(string s, string delimiter)
    {
        short pos = 0;
        string word = "";
        vector<string> vWords;

        while ((pos = s.find(delimiter)) != string::npos)
        {
            word = s.substr(0, pos);
            if (word != "")
            {
                vWords.push_back(word);
            }

            s = s.erase(0, pos + delimiter.length());
        }

        // print the last word
        if (s != "")
        {
            vWords.push_back(s);
        }

        return vWords;
    }

    // join string overloading
    string joinString(vector<string> vWords, string delimiter)
    {
        string line = "";

        for (string& word : vWords)
        {
            line = line + word + delimiter;
        }

        return line.substr(0, line.length() - delimiter.length());
    }

    string joinString(string* s, short length, string delimiter)
    {
        string line = "";

        for (short i = 0; i < length; i++)
        {
            line = line + s[i] + delimiter;
        }

        return line.substr(0, line.length() - delimiter.length());
    }

    string reverseWord(string s, string delimiter = " ")
    {
        string line = "";

        vector<string> vWords = mystd::splitString(s, delimiter);

        vector<string>::iterator iter = vWords.end(); // iter -> pointer of vecter
        while (iter != vWords.begin())
        {
            iter--;
            line = line + *iter + delimiter;
        }

        return line.substr(0, line.length() - delimiter.length());
    }

}

namespace myarray
{

    void readArrayAndLength(int* arr, int& length) // read length and array
    {
        length = mystd::readPozitifNumber("how much elements you want ? : ");

        for (int i = 0; i < length; i++) {
            arr[i] = mystd::readPozitifNumber("enter array[ " + to_string(i + 1) + " ] : ");
            // arr[i] = mystd::ReadNumber("enter array[ " + to_string(i+1) + " ] : ");   for pozitif and negatif
        }
    }

    void readLengthforRandomArray(int* arr, int& length) // read length and random array
    {
        length = mystd::readPozitifNumber("how much elements you want ? : ");

        for (int i = 0; i < length; i++) {
            arr[i] = mystd::generateRandomNumber(10, 99);
        }
    }


    void printIntArray(string message, int* arr, int length) // print array by pointer and length
    {
        cout << message;
        for (int i = 0; i < length; i++)
        {
            cout << arr[i] << ", ";
        }
        cout << endl;
    }


    void shuffleArray(int* arr, int length) // shuffle the array ; mix the array index
    {
        int randomNum;
        for (int i = 0; i < length; i++)
        {
            randomNum = mystd::generateRandomNumber(0, length - 1);

            swap(arr[i], arr[randomNum]);
        }
    }


    int searchNumberInArray(const int searchingNumber, const int* arr, int length) // search number in array
    {
        for (int i = 0; i < length; i++)
        {
            if (searchingNumber == arr[i])
            {
                return i;
            }
        }

        return -999;
    }

    bool isNumberInArray(const int searchingNumber, const int* arr, int length) // is number in array, by using searchNumberInArray
    {
        return searchNumberInArray(searchingNumber, arr, length) != -999;
    }


    void addNumberInArray(int addNumber, int* arr, int position)
    {
        arr[position] = addNumber;
    }


}

namespace mystring
{

    string lowerAllString(string s)
    {
        for (short i = 0; i < s.length(); i++)
        {
            s[i] = tolower(s[i]);
        }

        return s;
    }

    string upperAllString(string s)
    {
        for (short i = 0; i < s.length(); i++)
        {
            s[i] = toupper(s[i]);
        }

        return s;
    }

    string replaceWord(string s, string stringToReplace, string replaceTo)
    {
        short pos = 0;
        while ((pos = s.find(stringToReplace)) != string::npos)
        {
            s.replace(pos, stringToReplace.length(), replaceTo);
            // replace [(int)index, (int)sizeof word, (string)new word]
        }

        return s;
    }
}

namespace myvector
{

    void printVector(vector<string> v, string message = "")
    {
        cout << message;

        short i = 1;
        for (string& word : v)
        {
            cout << i++ << ':' << word << "   ";
        }

        return;
    }

}

namespace myfile
{
    void loadFileToVector(string filePath, vector <string>& vFileContent)
    {
        fstream file;
        file.open(filePath, ios::in);

        if (file.is_open())
        {
            string line;

            while (getline(file, line))
                vFileContent.push_back(line);

            file.close();
        }

        return;
    }

    void saveVectorToFile(string filePath, vector <string>& vFileContent)
    {
        fstream file;
        file.open(filePath, ios::out); // open the file

        if (file.is_open())
        {
            for (string& line : vFileContent)
            {
                file << line << endl;
            }
        }

        return;
    }

    bool wirteInFile(string fileAdress, string content)
    {
        fstream newFile;

        newFile.open(fileAdress, ios::out | ios::app);

        if (newFile.is_open())
        {
            newFile << content;
            newFile << endl;

            newFile.close();

            return true;
        }

        return false;
    }

}