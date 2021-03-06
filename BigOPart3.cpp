#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#include<vector>
#include<cassert>
#include<cmath>
#include<ctime>
#include<cstdlib>

#define INFILE "file.txt"
#include "DynamicArray.h"

struct Class
{
    string subjectCode;
    int count;
};

int main()
{
    cout << "Programmer: Kristina Fout\n";
    cout << "Programmer ID: 1866884\n";
    cout << "file: " << __FILE__ << "\n\n";
    
    int i;
    string name;
    srand(time(0)); rand();
    rand(); // seed the RNG (we'll need it)
        // programmer customizations go here
    int n = 1000; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
    //const int reps = n / 100;
    string bigOh = "O(n squared)"; // YOUR PREDICTION: O(n),
    // O(n log n), or O(n squared)
    cout.setf(ios::fixed);
    cout.precision(4);
    double elapsedSecondsNorm = 0;
    double expectedSeconds = 0;
    
    int counter = 0; // how many lines are read
    int d = 0; // how many duplicate records
    int subjects = 0; // index for subjectCount array
    int total = 0;
    bool duplicate;
    bool stored;
    
    
    char* token;
    char buf[1000];
    const char* const tab = "\t";
    
    for (int cycle = 0; cycle < 4; cycle++, n*=2)
    {
        DynamicArray<Class> sub;
        DynamicArray<string> nonDuplicateClass(100);
        DynamicArray<string> subjectCount(100);
        vector<string> names(n); // problem setup goes here -- create a data structure of size n
        for (int i = 0; i < n; i++) names[i] = rand();
        
        assert(names.size() == n); // assert(a.size( ) == n); // or something like that...
        
        ifstream openFile;
        openFile.open(INFILE);
        // do something where n is the "size" of the problem
        for(i = 0; i < n; i++) // EOF loop to read n names from the file and store it in an array
        {       // This is a for loop instead of while EOF loop,
            if(openFile)       // as we need to validate that n names has been read from file or not
        {
            
            getline(openFile,name);
                total++;
            names[i]=name;
            strcpy(buf, name.c_str());
            
            if (buf[0] == 0) continue;
            
            const string term(token = strtok(buf, tab));
            const string section((token = strtok(0, tab)) ? token : "");
            const string course((token = strtok(0, tab)) ? token : "");
            const string instructor((token = strtok(0, tab)) ? token : "");
            const string whenWhere((token = strtok(0, tab)) ? token : "");
            if (course.find('-') == string::npos) continue;
            const string subjectCode(course.begin(), course.begin() + course.find('-'));
            string classCode = term + "." + section;
            
            int i = 0; // better to do it outside
            for (i = 0; i < counter; i++) // classIndex because its the condition of how many non-duplicated class codes
            {
                if (nonDuplicateClass[i] == term && subjectCount[i] == section)
                {
                    d++;
                    duplicate = true;
                    break;
                }
            }
            if (duplicate == true)
                continue;
            nonDuplicateClass[counter] = term;
            subjectCount[counter] = section;
            counter++;
            
            for(int i = 0; i < subjects; i++)
            {
                if(sub[i].subjectCode == subjectCode)
                {
                    sub[i].count++;
                    stored = true;
                    break;
                }
            }
            if (stored == true)
                continue;
            Class class1;
            class1.subjectCode = subjectCode;
            class1.count = 1;
            sub[subjects] = class1;
            subjects++;
        }
        else
        {
        // if the ifilestream object 'if' reaches the End Of File before reading 'n' names
        break;
        }
    }
    openFile.close();

    clock_t startTime = clock(); // start the timer, do something, and stop the timer
            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if (names[j] < names[i])
                    {
                        swap(names[i], names[j]);
                    }
                }
            }
            for (int i = 1; i < n; i++)
                assert (names[i-1] <= names[i]);
        
    clock_t endTime = clock();
        
// compute timing results
    double elapsedSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double factor = pow(2.0, double(cycle));
    if (cycle == 0)
        elapsedSecondsNorm = elapsedSeconds;
    else if (bigOh == "O(n)")
        expectedSeconds = factor * elapsedSecondsNorm;
    else if (bigOh == "O(n log n)")
        expectedSeconds = factor * log(double(n)) / log(n / factor) * elapsedSecondsNorm;
    else if (bigOh == "O(n squared)")
        expectedSeconds = factor * factor * elapsedSecondsNorm;
        
        // reporting block
            cout << elapsedSeconds;
        if (cycle == 0)
            cout << " (expected " << bigOh << ')';
        else
            cout << " (expected " << expectedSeconds << ')';
            cout << " for n = " << n << endl;
    }
    return 0;
}
