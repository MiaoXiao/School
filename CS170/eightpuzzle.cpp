//references:
//http://www.aiai.ed.ac.uk/~gwickler/eightpuzzle-uninf.html
//http://ldc.usb.ve/~gpalma/ci2693sd08/puzzleFactible.txt
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

//indexes of blank space in default puzzle
#define BLANKX 0
#define BLANKY 1

//values of default puzzle
//first row
#define FIRST 4
#define SECOND 9
#define THIRD 3
//second row
#define FOURTH 7
#define FIFTH 1 
#define SIXTH 5
//third row
#define SEVENTH 8
#define EIGHTH 2
#define BLANK 6

//specifies what heuristic to use
enum HeuristicType{NONE, MISPLACED, MANHATTEN};

//store default pussle
vector<vector <int> > puzzledefault;
vector<int> puzzledefaultvalues;
//store custom key
vector<vector <int> > puzzlecustom;
//9 is the blank spot
vector<vector <int> > puzzlegoal;

//index in 2d vector
struct Index
{
		unsigned int x;
		unsigned int y;
};

//holds data about one puzzle, and its parent in a tree
struct State
{
	State() 
	{
		depth = 0;
		heuristic = 0;
		parent = -1;
		pos = 0;
		message = "Initital state.";
	}
	//current puzzle
	vector<vector<int> > puzzle;
	//index of 9
	Index blank;
	
	//g(n)
	int depth;
	//f(n)
	int heuristic;
	
	//movement message
	string message;
	
	//this state's position in tree
	int pos;
	//parent of next state (for calculating answer path)
	int parent;
	
	//swap two elements in puzzle
	void swap(int x1, int y1, int x2, int y2)
	{
		int temp = puzzle[x1][y1];
		puzzle[x1][y1] = puzzle[x2][y2];
		puzzle[x2][y2] = temp;
	}
};

//for priority queue
struct Compare
{
	bool operator()(const State& lhs, const State& rhs)
	{
		return (lhs.depth + lhs.heuristic) > (rhs.depth + rhs.heuristic);
	}
};

//holds all possible states
struct Tree
{
	vector<State> list;
};

//displays an 8 puzzle
void displayPuzzle(vector<vector<int> > s)
{
	//cout << "size: " << s.size() << endl;
	//cout << "element: " << s[0][0] << endl;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
				cout << s[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//initalize puzzle vectors
void initVectors()
{
	vector<int> v;
	
	for (unsigned int i = 0; i < 3; ++i)
	{
		puzzledefault.push_back(v);
		puzzlecustom.push_back(v);
		puzzlegoal.push_back(v);
	}
	
	//first row
	puzzledefaultvalues.push_back(FIRST);
	puzzledefaultvalues.push_back(SECOND);
	puzzledefaultvalues.push_back(THIRD);
	//second row
	puzzledefaultvalues.push_back(FOURTH);
	puzzledefaultvalues.push_back(FIFTH);
	puzzledefaultvalues.push_back(SIXTH);
	//third row
	puzzledefaultvalues.push_back(SEVENTH);
	puzzledefaultvalues.push_back(EIGHTH);
	puzzledefaultvalues.push_back(BLANK);
	
	int spot = 0;
	int value = 1;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//cout << "spot: " << spot << endl;
			//cout << "value: " << puzzledefaultvalues[value - 1] << endl;
			puzzledefault[spot].push_back(puzzledefaultvalues[value - 1]);
			puzzlegoal[spot].push_back(value);
			value++;
			puzzlecustom[i].push_back(0);
		}
		spot++;
	}
}

//checks to see if goal state is reached
bool checkGoalState(vector<vector<int> > s)
{
	//this is the goal state!
	if (s == puzzlegoal) return true;
	return false;
}

//display answer
void displayAnswer(Tree tree)
{
	//put reversed path in stack, to correct the order
	int nextIndex = tree.list.size() - 1;
	stack<State> temp;
	while (nextIndex != -1)
	{
		temp.push(tree.list[nextIndex]);
		nextIndex = tree.list[nextIndex].parent;
	}
	//display correct path to puzzle
	for (unsigned int i = 1; !temp.empty(); ++i)
	{
		cout << i << ": " << endl;
		cout << temp.top().message << endl;
		displayPuzzle(temp.top().puzzle);
		temp.pop();
	}
}

//find correct indexes of where number n piece should be
//replaces ifinal and jfinal with the correct index
void findCorrectPos(int n, int &ifinal, int &jfinal)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//once correct index found, return
			if (n == puzzlegoal[i][j])
			{
				ifinal = i;
				jfinal = j;
				return;
			}
		}
	}
}

//returns estimated cost of moving piece to correct spot
//type specifies what heuristic to use if any
int getHeuristic(vector<vector<int> > currentstate, int type)
{
	if (type == NONE) return 0;
	int total = 0;
	int ifinal = 0;
	int jfinal = 0;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//if spots do not match, find manhatten distance
			if (currentstate[i][j] != 9 && currentstate[i][j] != puzzlegoal[i][j])
			{
				if (type == MISPLACED) total++;
				else if (type == MANHATTEN) 
				{
					findCorrectPos(currentstate[i][j], ifinal, jfinal);
					total += abs(i - ifinal) + abs(j - jfinal);
				}
			}
		}
	}
	return total;
}

//returns false if this check is already in list
bool checkStates(vector<State> list, vector<vector<int> > check)
{
	for (unsigned int i = 0; i < list.size(); ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			for (unsigned int k = 0; k < 3; ++k)
			{
				cout << "comparing" << list[i].puzzle[j][k] << " and " << check[j][k] << endl;
				if (list[i].puzzle[j][k] != check[j][k]) return true;
			}
		}
	}
	return false;
}

//assign operator's new parent, current pos in list, and message
void assignNewOperator(const State checking, State &next, Tree &tree, priority_queue<State, vector<State>, Compare> &avaliableStates, string message, int h)
{
	//assign heurstic if not uniform
	if (h != NONE) next.heuristic = getHeuristic(next.puzzle, h);

	//increase depth
	next.depth++;
	//assign message
	next.message = message;
	//assign parent
	next.parent = checking.pos;
	tree.list.push_back(next);
	//assign new pos
	next.pos = tree.list.size() - 1;
	avaliableStates.push(next);
}

//check if puzzle is even possible
bool checkInversions(vector<vector<int > > p)
{
	//put 2d vector into just 1 vector
	vector<int> straight;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			straight.push_back(p[i][j]);
		}
	}
	//compare every element with the elements in front, to check for inversions
	int numbOfInversions = 0;
	for (int i = 0; i < straight.size(); ++i)
	{
		for (unsigned int j = i + 1; j < straight.size(); ++j)
		{
			if (straight[i] != 9 && straight[j] != 9 &&
				straight[j] > straight[i]) 
			{
				numbOfInversions++;
			}
		}
	}
	//cout << "Numb of inversions: " << numbOfInversions << endl;
	//if inversions are even, puzzle is solvable
	if (numbOfInversions % 2 == 0) return true;
	return false;
}

//uniform cost search. returns true if success, returns false if impossible
//specify heuristic type
bool generalSearch(State initial, int h)
{
	//total nodes expanded
	int totalNodesExpanded = 0;
	//max depth of tree
	int maxNodesInQueue = 0;
	//depth of foal node
	int goalDepth = 0;
	
	//tree
	Tree tree;
	//push first state
	tree.list.push_back(initial);
	
	//check if initial state is goal
	if (checkGoalState(initial.puzzle)) return true;
	//check if puzzle is even possible
	if (!checkInversions(initial.puzzle)) return false;
	
	//container for all valid states to check. push initial state.
	priority_queue<State, vector<State>, Compare> avaliableStates;
	avaliableStates.push(initial);
	
	//set to true when puzzle is solved
	bool puzzleSolved = false;
	
	//start loop
	while (!avaliableStates.empty())
	{
		//pop the node to check
		State checking = avaliableStates.top();
		avaliableStates.pop();
		
		cout << "Expanding the next best node: " << endl;
		cout << "Depth + Heuristic = Total" << endl;
		cout << checking.depth << " + " << checking.heuristic  << " = " << checking.depth + checking.heuristic << endl << endl;
		displayPuzzle(checking.puzzle);
		
		//check operation moving 9 left
		if (checking.blank.y != 0)
		{
			State next = checking;
			totalNodesExpanded++;
			
			//swap elements
			next.swap(next.blank.x, next.blank.y, next.blank.x, next.blank.y - 1);
			next.blank.y--;
			
			assignNewOperator(checking, next, tree, avaliableStates, "Moved blank left.", h);
			if (checkGoalState(next.puzzle))
			{
				puzzleSolved = true;
				goalDepth = next.depth;
			}
		}
		//check operation moving 9 up
		if (!puzzleSolved && checking.blank.x != 0)
		{
			State next = checking;
			totalNodesExpanded++;
			
			//swap elements
			next.swap(next.blank.x, next.blank.y, next.blank.x - 1, next.blank.y);
			next.blank.x--;
			
			assignNewOperator(checking, next, tree, avaliableStates, "Moved blank up.", h);
			if (checkGoalState(next.puzzle))
			{
				puzzleSolved = true;
				goalDepth = next.depth;
			}
		}
		//check operation moving 9 right
		if (!puzzleSolved && checking.blank.y != 2)
		{
			State next = checking;
			totalNodesExpanded++;
			
			//swap elements
			next.swap(next.blank.x, next.blank.y, next.blank.x, next.blank.y + 1);
			next.blank.y++;
			
			assignNewOperator(checking, next, tree, avaliableStates, "Moved blank right.", h);
			if (checkGoalState(next.puzzle))
			{
				puzzleSolved = true;
				goalDepth = next.depth;
			}
		}
		//check operation moving 9 down
		if (!puzzleSolved && checking.blank.x != 2)
		{
			State next = checking;
			totalNodesExpanded++;
			
			//swap elements
			next.swap(next.blank.x, next.blank.y, next.blank.x + 1, next.blank.y);
			next.blank.x++;
			
			assignNewOperator(checking, next, tree, avaliableStates, "Moved blank down.", h);
			if (checkGoalState(next.puzzle))
			{
				puzzleSolved = true;
				goalDepth = next.depth;
			}
		}
		
		//check max size of queue
		if (avaliableStates.size() > maxNodesInQueue) maxNodesInQueue = avaliableStates.size();
		
		//when puzzle is solved, display answer path
		if (puzzleSolved)
		{
			displayAnswer(tree);
			cout << "Total Nodes Expanded: " << totalNodesExpanded << endl;
			cout << "Max Nodes in Queue: " << maxNodesInQueue << endl;
			cout << "Depth of Goal: " << goalDepth << endl;
			return true;
		}
	}
	cout << "Total Nodes Expanded: " << totalNodesExpanded << endl;
	cout << "Max Nodes in Queue: " << maxNodesInQueue << endl;
	cout << "Depth of Goal: " << goalDepth << endl;
	cout << "All nodes exploded. Puzzle is not solvable." << endl;
	return false;
}

int main()
{
	State initial;
	//init vectors
	initVectors();
	
	cout << endl << "Default puzzle: " << endl;
	displayPuzzle(puzzledefault);
	
	int puzzletype;
	cout << "Welcome to Rica's eight-puzzle solver." << endl;
	cout << "Type '1' to use default puzzle, type anything else to use custom puzzle." << endl;
	cin >> puzzletype;
	cout << endl;
	
	if (puzzletype == 1) //default puzzle
	{
		initial.puzzle = puzzledefault;
		initial.blank.x = BLANKX;
		initial.blank.y = BLANKY;
		
	}
	else //custom puzzle
	{
		int spot;
		cout << "Enter in 9 numbers, 1 - 9, seperated by spaces, which will fill in the eight puzzle." << endl;
		cout << "The eight-puzzle will be filled in from left to right, from the first row to the last row. " << endl;
		cout << "Make sure to only enter digits; entering a 9 will represent the blank space." << endl;
		cout << "No repeating digits allowed." << endl;
		for (unsigned int i = 0; i < 3; ++i)
		{
			for (unsigned int j = 0; j < 3; ++j)
			{
				cin >> spot;
				if (spot == 9)
				{
					initial.blank.x = i;
					initial.blank.y = j;
				}
				puzzlecustom[i][j] = spot;
			}
		}
		initial.puzzle = puzzlecustom;
	}
	initial.depth = 0;
	
	int algorithm;
	cout << "Which algorithm to use?" << endl;
	cout << "0: Uniform Cost Search " << endl;
	cout << "1: A* with Misplaced Tile Heuristic " << endl;
	cout << "2: A* with Misplaced Distance Heuristic" << endl;
	cin >> algorithm;
	
	if (algorithm < 0 || algorithm > 2)
	{
		cout << "Not a valid algorithm." <<endl;
		exit(1);
	}
	
	generalSearch(initial, algorithm);
}
