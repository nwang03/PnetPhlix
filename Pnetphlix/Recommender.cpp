#include "Recommender.h"
#include "User.h"
#include "Movie.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
    const MovieDatabase& movie_database)
    : m_userDb(&user_database), m_movieDb(&movie_database)
{
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    // return an empty vector
    if(movie_count <= 0)
        return vector<MovieAndRank>();
    // declare hash table to store movie ids and their compatability scores
    unordered_map<string, int> compatabilityList;
    unordered_map<string, int>::iterator iter;
    // get a pointer to the user which corresponds to the user email through user database's method
    User* u = m_userDb->get_user_from_email(user_email);
    // get the watch history of that user
    vector<string> watchHistory = u->get_watch_history();

    // loop through each movie in the user's watch history
    Movie* currentMovie;
    for (int i = 0; i < watchHistory.size(); i++)
    {
        // get the current movie the watch history id refers to by looking through the movie database
        currentMovie = m_movieDb->get_movie_from_id(watchHistory[i]);
        // get the directors from the current movie
        vector<string> directorList = currentMovie->get_directors();
        // loop through all these directors and construct a vector of all the movies that have each director
        vector<Movie*> moviesWithDirector;
        for (int j = 0; j < directorList.size(); j++)
        {
            string director = directorList[j];
            // use movie database to search for all movies that have the current director
            moviesWithDirector = m_movieDb->get_movies_with_director(director);
            // loop through all these movies and add them to the compatability list
            // if the movie already exists in the compatability list, increment its score by 20
            // otherwise push a new movie into the compatability list
            for (Movie* m : moviesWithDirector)
            {
                iter = compatabilityList.find(m->get_id());
                if (iter == compatabilityList.end())
                {
                    compatabilityList[m->get_id()] = 20;
                }
                else
                {
                    iter->second += 20;
                }
            }
        }
        
        // get a vector of all the actors the current move has
        vector<string> actorList = currentMovie->get_actors();
        // loop thorugh each actor one by one
        for (int j = 0; j < actorList.size(); j++)
        {
            string actor = actorList[j];
            // use movie database to generate a list of all movies that has the current actor
            vector<Movie*> moviesWithActor = m_movieDb->get_movies_with_actor(actor);
            // loop through all these movies and add them to the compatability list
            // if the movie already exists in the compatability list, increment its score by 30
            // otherwise push a new movie into the compatability list
            for (Movie* m : moviesWithActor)
            {
                iter = compatabilityList.find(m->get_id());
                if (iter == compatabilityList.end())
                {
                    compatabilityList[m->get_id()] = 30;
                }
                else
                {
                    iter->second += 30;
                }
            }
        }

        // get a vector of all the genres the current movie has
        vector<string> genreList = currentMovie->get_genres();
        // loop through each genre one by one
        for (int j = 0; j < genreList.size(); j++)
        {
            string genre = genreList[j];
            // use movie database to generate a list of all movies that has this genre
            vector<Movie*> moviesWithGenre = m_movieDb->get_movies_with_genre(genre);
            // loop through all these movies and add them to the compatability list
            // if the movie already exists in the compatability list, increment its score by 1
            // otherwise push a new movie into the compatability list
            for (Movie* m : moviesWithGenre)
            {
                iter = compatabilityList.find(m->get_id());
                if (iter == compatabilityList.end())
                {
                    compatabilityList[m->get_id()] = 1;
                }
                else
                {
                    iter->second++;
                }
            }
        }
    }
    // generate a vector containing MovieAndRank structs, pulling each corresponding movie id/compatability score from the original compatabilityList hash table
    vector<MovieAndRank> m_compatibilityList;
    for (iter = compatabilityList.begin(); iter != compatabilityList.end(); iter++)
        m_compatibilityList.push_back(MovieAndRank(iter->first, iter->second));
    // loop through the compatibility list and remove any movies that the user has already watched
    vector<MovieAndRank>::iterator i = m_compatibilityList.begin();
    bool found = false;
    while (i != m_compatibilityList.end())
    {
        // loop thorugh the user's watch list to check for already watched recommendations
        for (int j = 0; j < watchHistory.size(); j++)
        {
            // set both movie titles to lower case for case insensitive searching
            string temp1 = "";
            for (char c : watchHistory[j])
                temp1 += tolower(c);
            string temp2 = "";
            for (char c : i->movie_id)
                temp2 += tolower(c);
            // erase movie from list if already watched
            if (temp1 == temp2)
            {
                i = m_compatibilityList.erase(i);
                found = true;
                break;
            }
        }
        // only increment iterator if this movie hasn't been watched yet
        if (!found)
            i++;
        found = false;
    }
    // sort the compatability list vector by compatability score
    // the lambda function returns true if movie1 comes BEFORE movie2 (either bigger score, higher rating, or alphabetically smaller title)
    sort(m_compatibilityList.begin(), m_compatibilityList.end(), [&](const MovieAndRank& m1, const MovieAndRank& m2)
        {
            if (m1.compatibility_score > m2.compatibility_score)
                return true;
            else if (m1.compatibility_score < m2.compatibility_score)
                return false;
            else
            {
                if (m_movieDb->get_movie_from_id(m1.movie_id)->get_rating() > m_movieDb->get_movie_from_id(m2.movie_id)->get_rating())
                    return true;
                else if (m_movieDb->get_movie_from_id(m1.movie_id)->get_rating() < m_movieDb->get_movie_from_id(m2.movie_id)->get_rating())
                    return false;
                else
                {
                    return m_movieDb->get_movie_from_id(m1.movie_id)->get_title() < m_movieDb->get_movie_from_id(m2.movie_id)->get_title();
                }
            }
        });
    
    // generate one final list, pulling corresponding movies from the compatability list vector up into either the compatability list has run out or we've reached the amount of movies specified from movie_count
    vector<MovieAndRank> finalList;
    for (int i = 0; i < m_compatibilityList.size() && i < movie_count; i++)
        finalList.push_back(m_compatibilityList.at(i));

    return finalList;
}
