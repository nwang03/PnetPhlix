#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

MovieDatabase::MovieDatabase()
{
}

MovieDatabase::~MovieDatabase()
{
    // deallocate all the movies that the m_movies vector points to
    for (int i = 0; i < m_movies.size(); i++)
        delete m_movies[i];
}
bool MovieDatabase::load(const string& filename)
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
        int count = 0;
        // while file has lines, read in the line
        while (getline(infile, input))
        {
            // declare variables/vectors that will be used in the file input
            string id, name, year, director = "", actor = "", genre = "", line;
            vector<string> directorList, actorList, genreList;
            float rating = 0;
            // skip empty lines
            if (input != "")
            {
                // assign the first line read to movie id
                id = input;
                // convert id to lowercase (to allowe for case insensitive searching)
                for (int i = 0; i < id.size(); i++)
                    id[i] = tolower(id[i]);
                // insert the key value pair of id and count
                // count keeps track of the current iteration of the movie
                // so the first movie will have an index of 0 in the m_movies vector, so all these maps will point to 0 accordingly and so on
                m_idDatabase.insert(id, count );

                getline(infile, name);
                getline(infile, year);
                getline(infile, line);
                // loop through the line which contains all the directors, processing each character
                // if the character is a comma, then the director name is done and we push it into the director list (list of directors the corresponding movie will have) and director database (key-value, so director will refer to this movie by index)
                // if the character is not a comma, add the character to the directors name, lowercased to preserve case insensitivity
                for (char c : line)
                {
                    if (c == ',')
                    {
                        directorList.push_back(director);
                        m_directorDatabase.insert(director, count );
                        director = "";
                    }
                    else
                    {
                        director += tolower(c);
                    }
                }
                // push the last director name, or only name if there are no commas
                directorList.push_back(director);
                m_directorDatabase.insert( director, count );
                director = "";

                getline(infile, line);
                // loop through the line which contains all the actors, processing each character
                // if the character is a comma, then the actor name is done and we push it into the actor list (list of actors the corresponding movie will have) and actor database (key-value, so actor will refer to this movie by index)
                // if the character is not a comma, add the character to the actors name, lowercased to preserve case insensitivity
                for (char c : line)
                {
                    if (c == ',')
                    {
                        actorList.push_back(actor);
                        m_actorDatabase.insert( actor, count );
                        actor = "";
                    }
                    else
                    {
                        actor += tolower(c);
                    }
                }
                // push the last actor name, or only name if there are no commas
                actorList.push_back(actor);
                m_actorDatabase.insert(actor, count );
                actor = "";

                getline(infile, line);

                // loop through the line which contains all the genres, processing each character
                // if the character is a comma, then the genre is done and we push it into the genre list (list of genres the corresponding movie will have) and genre database (key-value, so this genre will refer to this movie by index)
                // if the character is not a comma, add the character to the genre's name, lowercased to preserve case insensitivity
                for (char c : line)
                {
                    if (c == ',')
                    {
                        genreList.push_back(genre);
                        m_genreDatabase.insert(genre, count );
                        genre = "";
                    }
                    else
                    {
                        genre += tolower(c);
                    }
                }
                // push the last genre name, or only name if there are no commas
                genreList.push_back(genre);
                m_genreDatabase.insert(genre, count);
                genre = "";

                infile >> rating;
                infile.ignore(10000, '\n');
                // now that we finally read all our data, we can dynamically allocate a new movie and pass its pointer to m_movies
                m_movies.push_back(new Movie(id, name, year, directorList, actorList, genreList, rating));
                count++;                
                getline(infile, input);
            }
        }
        loaded = true;
        return true;
    }
    else
        return false;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    // convert id parameter to lowercase to enable case insensitive searching
    string temp = "";
    for (int i = 0; i < id.size(); i++)
        temp += tolower(id[i]);
    // idDatabase maps movie ids to the index where the corresponding movie is at in the m_movies vector
    // if the iterator is at a valid location (assigned to a valid Node which has the same key as specified in the parameter) then return
    // a pointer to that movie by first getting the value that the key is paired with (which is the index), and then accessing m_movies
    TreeMultimap<string, int>::Iterator i = m_idDatabase.find(temp);
    if (i.is_valid())
        return m_movies.at(i.get_value());
    else
        return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    // convert director parameter to lowercase to enable case insensitive searching
    string temp = "";
    for (int i = 0; i < director.size(); i++)
        temp += tolower(director[i]);
    // directorDatabase maps directors to a vector of indices of which movies have this director
    // if the iterator is at a valid location (assigned to a valid Node which has the same key as specified in the parameter and is in bounds of the value vector) then push
    // a pointer to that movie in a temporary vector by first getting the value that the key is paired with (which is the index), and then accessing m_movies
    // then the iterator will advance to the next duplicate key and grab the next value
    TreeMultimap<string, int>::Iterator i = m_directorDatabase.find(temp);
    vector<Movie*> list;
    while (i.is_valid())
    {
        list.push_back(m_movies.at(i.get_value()));
        i.advance();
    }
    return list;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    // convert actor parameter to lowercase to enable case insensitive searching
    string temp = "";
    for (int i = 0; i < actor.size(); i++)
        temp += tolower(actor[i]);
    // actorDatabase maps actors to a vector of indices of which movies have this actor
    // if the iterator is at a valid location (assigned to a valid Node which has the same key as specified in the parameter and is in bounds of the value vector) then push
    // a pointer to that movie in a temporary vector by first getting the value that the key is paired with (which is the index), and then accessing m_movies
    // then the iterator will advance to the next duplicate key and grab the next value
    TreeMultimap<string, int>::Iterator i = m_actorDatabase.find(temp);
    vector<Movie*> list;
    while (i.is_valid())
    {
        list.push_back(m_movies.at(i.get_value()));
        i.advance();
    }
    return list;
}
vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    // convert genre parameter to lowercase to enable case insensitive searching
    string temp = "";
    for (int i = 0; i < genre.size(); i++)
        temp += tolower(genre[i]);
    // genreDatabase maps genres to a vector of indices of which movies have this genres
    // if the iterator is at a valid location (assigned to a valid Node which has the same key as specified in the parameter and is in bounds of the value vector) then push
    // a pointer to that movie in a temporary vector by first getting the value that the key is paired with (which is the index), and then accessing m_movies
    // then the iterator will advance to the next duplicate key and grab the next value
    TreeMultimap<string, int>::Iterator i = m_genreDatabase.find(temp);
    vector<Movie*> list;
    while (i.is_valid())
    {
        list.push_back(m_movies[i.get_value()]);
        i.advance();
    }
    return list;
}
