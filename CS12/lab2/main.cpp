#include <iostream>

using namespace std;

//declare test arrays
char destination[] = {"Rica is "};
char source[] = {"lazy but funny"};

void displayArray(char destination[], int size)
{
    for (int count = 0; count < size; count++)
    {
        cout << destination[count];
    }
    cout << endl;
}

//connect source array to destination array
void mystrcat(char destination[], const char source[])
{
    //find where the null character in destination is
    int destinationStart = -1;
    do
    {
        destinationStart++;
    } while (destination[destinationStart] != '\0');

    //attach source to destination
    for (int count = 0; source[count] != '\0'; count++)
    {
        destination[destinationStart + count] = source[count];
        //adds the null terminator at the end of the phrase
        destination[destinationStart + count + 1] = '\0';
    }
    
}

int main()
{
    mystrcat(destination, source);
    //displayArray(destination, 23);
    
    return 0;
}
