#ifndef BBOARD_H
#define BBOARD_H

#include <string>
#include <vector>

#include "User.h"
#include "Message.h"

using namespace std;

class BBoard
{
	private:
		string title;
		vector<User> user_list;
		User current_user;
		vector<Message> message_list;
	public:
		BBoard();
		BBoard(const string &ttl);
		void setup (const string &input_file);
		void login();
		void run();
	private:
		void add_user(const string &name, const string &pass);
		bool user_exists(const string &name, const string &pass) const;
		User get_user(const string &name) const;
		void display() const;
		void add_message();
};

#endif