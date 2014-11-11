#ifndef INTLIST_H
#define INTLIST_H

struct IntNode
{
	int data;
	IntNode *next;
	IntNode(int data): data(data), next(0) {}
};

class IntList
{
	private:
		IntNode *head;
		IntNode *tail;
	public:
		IntList();
		~IntList();
		void display() const;
		void push_front(int value);
		void push_back(int value);
		void pop_front();
		void select_sort();
		void insert_sorted(int value);
		void remove_duplicates();
	private:
		int findSize();
};

#endif 