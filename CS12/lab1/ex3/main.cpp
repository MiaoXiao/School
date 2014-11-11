#include <iostream>
#include <vector>

using namespace std;

vector<int> numbers;

//searches through the vector and returns position of number to find
int search(vector<int> &numbers, int numberToFind)
{
    int integer = -1;
    
    for (int count = 0; count < numbers.size(); count++)
    {
        if (numbers.at(count) == numberToFind)
        {
            integer = count;
            return integer;
        }
    }
    return integer;
}

//removes element from vector
void remove(vector<int> &numbers, int numberToFind)
{
    for (int count = 0; count < numbers.size(); count++)
    {
        if (numbers.at(count) == numberToFind)
        {
            numbers.erase(numbers.begin()+count);
            break;
        }
    }
}

int main()
{
    //user enters numbers they wish to input into the vector
    int input;
    //number to find is the number the user wishes to search and for
    int numberToFind;
    
    cout << "Please enter in integers (0 to stop): ";
    cin >> input;
    
    //logs in all numbers into vector
    if (input != 0);
    {
        do
        {
            numbers.push_back(input);
            cin >> input;
        } while (input != 0);
    }
    
    cout << "What number would you like to find and remove?: ";
    cin >> numberToFind;
    
    cout << "Found: " << search(numbers, numberToFind);
    cout << endl;
    
    //removes number form vector
    remove(numbers, numberToFind);
    
    //prints entire vector
    cout << "Result: ";
    for (int count = 0; count < numbers.size(); count++)
    {
        cout << numbers.at(count) << " ";
    }
    cout << endl;
    
}