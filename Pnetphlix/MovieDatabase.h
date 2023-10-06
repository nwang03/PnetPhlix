#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
      // store all movies in a vector of movie pointers
      // because each movie has a corresponding ID, director list, actor list, and genre list
      // four treemultimaps are declared
      std::vector<Movie*> m_movies;
      // maps key->value as movie id -> index (in m_movies) of the movie the id corresponds to
      TreeMultimap<std::string, int> m_idDatabase;
      // maps key->value as director name -> index (in m_movies) of the movie(s) the director is in
      TreeMultimap<std::string, int> m_directorDatabase;
      // maps key->value as actor name->index(in m_movies) of the movie(s) the actor is in
      TreeMultimap<std::string, int> m_actorDatabase;
      // maps key->value as genre->index(in m_movies) of the movie(s) which as the genre
      TreeMultimap<std::string, int> m_genreDatabase;
      // boolean keeps track of whether this class loaded a database already or not
      bool loaded = false;
};

#endif // MOVIEDATABASE_INCLUDED
