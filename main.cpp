// Programming Assignment 3
// Programming Fundamentals II (COSC 1437)
// Author: Ezeanyinabia Arodiwe
// Description: Reads employee records from a file, writes a formatted
// payroll report, then demonstrates stream-inspection
// functions and input-failure handling.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    // ---------- PART 1: PAYROLL FILE PROCESSOR ----------

    // TODO B: declare inFile (ifstream) and outFile (ofstream)
    ifstream inFile;
    ofstream outFile;

    // TODO C: open payrollData.txt and payrollReport.txt
    // then check that the input file opened successfully.
    // If it failed, print an error and return 1.
    inFile.open("payrollData.txt");
    outFile.open("payrollReport.txt");

    if (inFile.fail())
    {
        cout << "Error: Could not open input file 'payrollData.txt'." << endl;
        return 1;
    }

    // Variables for one employee's data
    string firstName, lastName, department;
    double grossSalary, bonusPercent, taxPercent;
    double distance, travelTime;
    double paycheck, averageSpeed;

    outFile << fixed << showpoint << setprecision(2);

    // TODO D: loop while the input stream still reads a first name.
    // Inside the loop, read the rest of each employee's data.
    while (inFile >> firstName)
    {
        // read the remaining fields for this employee
        inFile >> lastName >> department;
        inFile >> grossSalary >> bonusPercent >> taxPercent;
        inFile >> distance >> travelTime;

        // TODO E: compute paycheck and averageSpeed
        paycheck = grossSalary + (grossSalary * bonusPercent / 100.0) - (grossSalary * taxPercent / 100.0);
        averageSpeed = distance / travelTime;

        // TODO F: write the formatted report block for this employee
        // remember fixed/showpoint/setprecision are already set,
        // and use setw at least once.
        outFile << "Name: " << firstName << " " << lastName << ", Department: " << department << endl;
        outFile << "Monthly Gross Salary: $" << grossSalary 
                << ", Bonus: " << bonusPercent << "%, Taxes: " << taxPercent << "%" << endl;
        outFile << "Paycheck: $" << paycheck << endl;
        outFile << "Distance Traveled: " << distance << " miles, Travel Time: " << travelTime << " hours" << endl;
        
        // Deliberate use of setw(5) to right-align the average speed output column
        outFile << "Average Speed: " << setw(5) << averageSpeed << " miles per hour" << endl;
        outFile << endl; // Blank line separating employees
    }

    // TODO G: close both files
    inFile.close();
    outFile.close();


    // ---------- PART 2: STREAM INSPECTOR ----------
    // (reads from the keyboard)

    // TODO H: peek at the first character, report digit vs letter,
    // then read and echo the full line.
    // (Note on putback(): describe one use case in a comment.)
    
    /* USE CASE FOR putback():
       When parsing user input where data types are mixed (like a product ID "A123"), 
       you might use peek() or get() to inspect the first character 'A'. If your program 
       needs to pass the entire unbroken string "A123" to a separate processing function 
       or object constructor later, you would use putback('A') to return it to the stream.
    */
    
    cout << "\n--- Part 2: Stream Inspector ---\n";
    cout << "Enter a line of text starting with a letter or a digit: ";
    
    char firstChar = cin.peek();
    if (isalpha(firstChar))
    {
        cout << "The first character is a letter." << endl;
    }
    else if (isdigit(firstChar))
    {
        cout << "The first character is a digit." << endl;
    }
    else
    {
        cout << "The first character is neither a letter nor a digit." << endl;
    }
    
    string fullLine;
    getline(cin, fullLine);
    cout << "Echoed Line: " << fullLine << endl;


    // TODO I: read an int, use cin.ignore(), then getline a description.
    int itemNumber;
    string description;
    
    cout << "\nEnter an integer (item number): ";
    cin >> itemNumber;
    
    cin.ignore(); // Discards the leftover trailing newline character '\n' from cin >>
    
    cout << "Enter a full-line description: ";
    getline(cin, description);
    
    cout << "Item: " << itemNumber << ", Description: " << description << endl;


    // TODO J: prompt for a number; if cin.fail(), clear and ignore,
    // then report invalid input.
    double validNumber;
    cout << "\nEnter a valid numeric value: ";
    cin >> validNumber;
    
    if (cin.fail())
    {
        cin.clear(); // Resets the stream error flags
        cin.ignore(1000, '\n'); // Flushes the bad characters out of the input buffer
        cout << "Error: The input provided was invalid. Stream recovered." << endl;
    }
    else
    {
        cout << "Successfully read number: " << validNumber << endl;
    }

    return 0;
}
