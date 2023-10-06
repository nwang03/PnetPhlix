#include <chrono>
#include <iostream>
using namespace std;

#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to close this window . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif


#include "UserDatabase.h"
#include "User.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "treemm.h"
#include "Recommender.h"
#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "Pnetphlix/users.txt";
const string MOVIE_DATAFILE = "Pnetphlix/movies.txt";

void findMatches(const Recommender& r,
	const MovieDatabase& md,
	const string& user_email,
	int num_recommendations) {

	vector<MovieAndRank> recommendations =
		r.recommend_movies(user_email, num_recommendations);
	if (recommendations.empty())
		cout << "We found no movies to recommend :(.\n";
	else {
		for (int i = 0; i < recommendations.size(); i++) {
			const MovieAndRank& mr = recommendations[i];
			Movie* m = md.get_movie_from_id(mr.movie_id);
			cout << i << ". " << m->get_title() << " ("
				<< m->get_release_year() << ")\n Rating: "
				<< m->get_rating() << "\n Compatibility Score: "
				<< mr.compatibility_score << "\n";
		}
	}
}

int main()
{
	/****************************TESTING USERDB********************************/
	//UserDatabase udb;
	//if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	//{
	//	cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
	//	return 1;
	//}
	//for (;;)
	//{
	//	cout << "Enter user email address (or quit): ";
	//	string email;
	//	getline(cin, email);
	//	if (email == "quit")
	//		return 0;
	//	User* u = udb.get_user_from_email(email);
	//	if (u == nullptr)
	//		cout << "No user in the database has that email address." << endl;
	//	else
	//		cout << "Found " << u->get_full_name() << endl;
	//}

	/****************************TESTING USER********************************/
	//vector<string> list1 = { "a", "b", "c" };
	//string x = "hi";
	//string y = "bye";
	//User u(x, y, list1);
	//cout << u.get_full_name() << " " << u.get_email() << endl;
	//x = "asdf";
	//y = "fdas";
	//cout << u.get_full_name() << " " << u.get_email() << endl;
	//vector<string> list2 = u.get_watch_history();
	//cout << "list2:" << endl;
	//for (int i = 0; i < 3; i++) {
	//	cout << list2[i] << endl;
	//}
	//cout << "list2:" << endl;
	//list2[0] = "d";
	//for (int i = 0; i < 3; i++) {
	//	cout << list2[i] << endl;
	//}
	//cout << "list3:" << endl;
	//vector<string> list3 = u.get_watch_history();
	//for (int i = 0; i < 3; i++) {
	//	cout << list3[i] << endl;
	//}
	//u.get_watch_history()[1] = "3";
	//cout << u.get_watch_history()[1] << endl;
	//list1[0] = "0";
	//cout << "list1:" << endl;
	//for (int i = 0; i < 3; i++) {
	//	cout << list1[i] << endl;
	//}
	//cout << "list5:" << endl;
	//vector<string> list5 = u.get_watch_history();
	//for (int i = 0; i < 3; i++) {
	//	cout << list5[i] << endl;
	//}
	//u.get_watch_history().push_back("hi");
	//cout << u.get_watch_history().size();

	/****************************TESTING MOVIEDB********************************/
	//MovieDatabase udb;
	//if (!udb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
	//{
	//	cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
	//	return 1;
	//}
	//for (;;)
	//{
	//	cout << "Enter movie id (or quit): ";
	//	string email;
	//	getline(cin, email);
	//	if (email == "quit")
	//		return 0;
	//	Movie* u = udb.get_movie_from_id(email);
	//	if (u == nullptr)
	//		cout << "No user in the database has that email address." << endl;
	//	else {
	//		cout << "Found " << u->get_id() << endl;
	//		cout << "Found " << u->get_title() << endl;
	//		cout << "Found " << u->get_release_year() << endl;
	//		vector<string> list = u->get_directors();
	//		for (int i = 0; i < list.size(); i++)
	//			cout << list[i] << "   ";
	//		cout << endl;
	//		list = u->get_actors();
	//		for (int i = 0; i < list.size(); i++)
	//			cout << list[i] << "   ";
	//		cout << endl;
	//		list = u->get_genres();
	//		for (int i = 0; i < list.size(); i++)
	//			cout << list[i] << "   ";
	//		cout << endl;
	//		cout << "Found " << u->get_rating() << endl;
	//	}
	//}

	//MovieDatabase udb;
	//if (!udb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
	//{
	//	cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
	//	return 1;
	//}
	//for (;;)
	//{
	//	cout << "Enter movie director (or quit): ";
	//	string email;
	//	getline(cin, email);
	//	if (email == "quit")
	//		return 0;
	//	vector<Movie*> u = udb.get_movies_with_director(email);
	//	if (u.size() == 0)
	//		cout << "No user in the database has that email address." << endl;
	//	else {
	//		for (int i = 0; i < u.size(); i++)
	//			cout << u.at(i)->get_title() << "   ";
	//		cout << endl;
	//	}
	//}

	//MovieDatabase udb;
	//if (!udb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
	//{
	//	cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
	//	return 1;
	//}
	//for (;;)
	//{
	//	cout << "Enter movie actor (or quit): ";
	//	string email;
	//	getline(cin, email);
	//	if (email == "quit")
	//		return 0;
	//	vector<Movie*> u = udb.get_movies_with_actor(email);
	//	if (u.size() == 0)
	//		cout << "No user in the database has that email address." << endl;
	//	else {
	//		for (int i = 0; i < u.size(); i++)
	//			cout << u.at(i)->get_title() << "   ";
	//		cout << endl;
	//	}
	//}

	//MovieDatabase udb;
	//if (!udb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
	//{
	//	cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
	//	return 1;
	//}
	//for (;;)
	//{
	//	cout << "Enter movie genre (or quit): ";
	//	string email;
	//	getline(cin, email);
	//	if (email == "quit")
	//		return 0;
	//	vector<Movie*> u = udb.get_movies_with_genre(email);
	//	if (u.size() == 0)
	//		cout << "No user in the database has that email address." << endl;
	//	else {
	//		for (int i = 0; i < u.size(); i++)
	//			cout << u.at(i)->get_title() << "   ";
	//		cout << endl;
	//	}
	//}

	/****************************TESTING TREEMM********************************/
	//TreeMultimap<std::string, int> tmm;
	//tmm.insert("carey", 5);
	//tmm.insert("carey", 6);
	//tmm.insert("carey", 7);
	//tmm.insert("david", 25);
	//tmm.insert("david", 425);
	//TreeMultimap<std::string, int>::Iterator it = tmm.find("carey");
	//// prints 5, 6, and 7 in some order
	//while (it.is_valid()) {
	//	std::cout << it.get_value() << std::endl;
	//	it.advance();
	//}
	//it = tmm.find("laura");
	//if (!it.is_valid())
	//std::cout << "laura is not in the multimap!\n";

	/****************************TESTING RECOMMENDER********************************/
	
	UserDatabase udb;
	MovieDatabase mdb;
	auto start = chrono::steady_clock::now();
	udb.load("users.txt");
	auto stop = chrono::steady_clock::now();
	cout << "User database took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
	start = chrono::steady_clock::now();
	mdb.load("movies.txt");
	stop = chrono::steady_clock::now();
	cout << "Movie database took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
	
	Recommender r(udb, mdb);
	start = chrono::steady_clock::now();
	findMatches(r, mdb, "ACumm512@aim.com", 1000);
	stop = chrono::steady_clock::now();

	cout << "Recommending took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
}

