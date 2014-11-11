#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


 // given the coordinates of a point (x,y) computes if the point is inside the circle 

 // centered at origin with radius R. Returns 'true' if it is inside, 'false' otherwise.

 // square = 4R^2
 // circle = PiR^2

bool is_inside(float x, float y, float R)
{
    float circle = sqrt(x * x + y * y);
    
    if (circle <= R)
    {
        return true;
    }
    else
    {
        return false;
    }
}

 // given the side,s, of a square that is centered at origin, 

 // choses a random coordinates inside the square, and calls is_inside function 

 // to test if the point is inside the circe or not.

bool throw_dart(int s)
{
    int x, y; 
    
     // assign x and y to two random numbers between -s/2 and s/2
    x = rand() % (s) - (s/2);
    y = rand() % (s) - (s/2);
    
    //tests x and y
    //cout << "x is" << x << endl;
    //cout << "y is" << y << endl;
    
     // see the previous exersice to see an example. 
    
     //Call the is_inside function and return its output.
    if (is_inside(x, y, 500))
    {
        //cout << "True!"<< endl;
        return true;
    }
    else
    {
        //cout << "False!"<< endl;
        return false;
    }
    
     //You do not have to cast x,y to floats, it is done automatically.
}

int main()
{
    //generates numbers;
    srand(time(0));
    
    int side = 1000; // this is the side of the square and is also our resolution. 
    int tries; // this is the number of tries.
    
     //Ask the user for the number of tries using cout.
    cout << "How many tries? ";
    cin >> tries;
    cout << endl;
     
     //Get the users input using cin.
    int in_count = 0; //counter to track number of throws that fall inside
    
    for(int i = 0; i < tries; i++)
    {
         //throw a dart using throw_dart method and increment the counter depending on
         //its output.
        if (throw_dart(side))
        {
            in_count++;
        }
    }
    
     //Compute and display the estimated value of PI. Make sure you are not doing
     //integer division
    
     // Pi = 4 x (Number of Darts in Circle) / (Number of Darts in Square)
     
    cout << 4 * (static_cast<float>(in_count) / 
    static_cast<float>(tries));
    cout << endl; 
    
    return 0;

}