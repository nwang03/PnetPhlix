#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{
}
// loop through m_users vector to deallocate the User classes
UserDatabase::~UserDatabase()
{
    for (int i = 0; i < m_users.size(); i++)
        delete m_users[i];
}

bool UserDatabase::load(const string& filename)
{
    // only read file if class has never loaded file yet
    if (!loaded)
    {
        ifstream infile(filename);
        if (!infile)
        {
            return false;
        }
        string input;
        string name;
        string email;
        int count = 0;
        int index = 0;
        while (getline(infile, input))
        {
            // skip any blank lines that appear
            if (input != "")
            {
                name = input;
                getline(infile, email);
                infile >> count;
                infile.ignore(10000, '\n');
                // loop for the next count lines which are guaranteed to be movie IDs that the user has watched
                vector<string> list;
                for (int i = 0; i < count; i++)
                {
                    getline(infile, input);
                    list.push_back(input);
                }
                // dynamically allocate new User with corresponding name, email, and watchlist and assign it to the vector of user pointers
                m_users.push_back(new User(name, email, list));
                // insert the key-value pair of email and the index the user is at in the m_users vector
                m_database.insert(email, index);
                index++;
                getline(infile, input);
            }
        }
        loaded = true;
        return true;
    }
    else
        return false;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    // using the database find method, get the right iterator spot of where a user is based off their email
    TreeMultimap<string, int>::Iterator i = m_database.find(email);
    // if the iterator is at a valid spot in the map, return a pointer to that user, otherwise return nullptr
    if (i.is_valid())
        return m_users.at(i.get_value());
    else
        return nullptr;
}
