#include <iostream>
#include <sstream>

using namespace std;



string to_formatted_string()// New !!
{
	
	//final complete string
	string finalString = "<begin_topic>";
	//buffer to turn int to string
	ostringstream intString;
	
	//convert int id to string
	intString << 4;
	
	finalString += "\n:id: " + intString.str();
	finalString += "\n:subject: Rica";
	finalString += "\n:from: John";
	
	//check if children exist and append if so
	// if (child_list.size() != 0)
	// {
		// finalString += '\n' + ":children: ";
		// for (int i = 0; i < child_list.size(); i++)
		// {
			// //convert child id to string
			// intString << child_list[i]->get_id();
			// finalString += intString.str() + " ";
		// }
	// }
	
	finalString += "\n:body: Hello my name is Rica\n<end>";
	
	return finalString;
}

int main()
{
	cout << to_formatted_string() << endl;
}