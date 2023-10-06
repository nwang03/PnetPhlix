#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include "treemm.h"
#include <string>
#include <vector>

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
      // vector of user pointers for all the users in the database
      std::vector<User*> m_users;
      // stores user emails as keys, the values are integers which contain the index of the corresponding user in the above vector m_users
      TreeMultimap<std::string, int> m_database;
      bool loaded = false;
};

#endif // USERDATABASE_INCLUDED
