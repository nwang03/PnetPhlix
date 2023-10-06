#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
      // pointers to user and movie databases, which the recommender class will need to access the info required to recommend movies to a user
      const UserDatabase* m_userDb;
      const MovieDatabase* m_movieDb;
};

#endif // RECOMMENDER_INCLUDED
