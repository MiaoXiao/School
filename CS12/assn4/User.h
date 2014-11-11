#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
	private:
		string username;
		string password;
	public:
		//creates a user with empty name and password.
		User()
			:username(""), password(""){}
		// creates a user with given username and password.
		User(const string& uname, const string& pass)
			:username(uname), password(pass){}
		string get_username() const;
		bool check(const string &uname, const string &pass) const;
		void set_password(const string &newpass);
};

#endif