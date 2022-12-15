//
//  MovieRentalSystem.hpp
//  cs_hw3
//
//  Created by Bora Haliloglu on 30.11.2022.
//  22101852
//  Section 3
#ifndef MovieRentalSystem_hpp
#define MovieRentalSystem_hpp

#include "LinkedList.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


class MovieRentalSystem {
public:
    MovieRentalSystem( const string movieInfoFileName, const string subscriberInfoFileName );
            MovieRentalSystem();
    ~MovieRentalSystem();
    void removeMovie( const int movieId ); // Done
    void addMovie( const int movieId, const int numCopies ); //Done
    void removeSubscriber( const int subscriberId ); // Done
    void rentMovie( const int subscriberId, const int movieId ); // Done
    void returnMovie( const int subscriberId, const int movieId ); // Done
    void showMoviesRentedBy( const int subscriberId ) const; // Done
    void showSubscribersWhoRentedMovie( const int movieId ) const; // Done
    void showAllMovies() const; // Done
    void showAllSubscribers() const; // Done
    void removeAllTransac(int id);
    void removeEveryMovie(int id);
            void addUser(int id);
private:
    LinkedList<Movie> movies;
    LinkedList<User> users;
//    LinkedList<Transac> transac;
};

#endif /* MovieRentalSystem_hpp */
