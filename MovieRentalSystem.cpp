//
//  MovieRentalSystem.cpp
//  cs_hw3
//
//  Created by Bora Haliloglu on 30.11.2022.
//  22101852
//  Section 3
#include "MovieRentalSystem.h"
#include <fstream>
#include <istream>
using namespace std;

MovieRentalSystem::MovieRentalSystem(){
}
void MovieRentalSystem::addUser(int id){
    User* m1 = new User;
    m1->id = id;
    users.add(m1);
}
MovieRentalSystem::MovieRentalSystem( const string movieInfoFileName, const string subscriberInfoFileName ){
    string movieFile = movieInfoFileName;
    string subFile = subscriberInfoFileName;
    int movie;
    int movie2;
    int sub1;
    int count1 = 0, count2 = 0;
    ifstream inMovieFile;
    ifstream inSubFile;
    
    inMovieFile.open(movieFile);
    inSubFile.open(subFile);
    if(!inMovieFile || !inSubFile){
        if(!inMovieFile && !inSubFile){
            cout << "Input file " << movieInfoFileName << " and " <<  subscriberInfoFileName << " does not exist" << endl;
        }
        else{
            cout << "Input file " << movieInfoFileName << " does not exist" << endl;
        }
    }
    else{
        if(inMovieFile.is_open() && inSubFile.is_open() ){ //gerek yokmus
            inMovieFile >> count1;
            while(inMovieFile.eof() == false){
                inMovieFile >> movie;
                inMovieFile >> movie2;
                Movie* temp = new Movie;
                temp->movieId = movie;
                temp->numberOfCopies = movie2;
                temp->allCopies = movie2;
                movies.add(temp);
        }
        //cout<<"After the movie file reading is done:\n"; //to debug
        //showAllMovies(); //to debug
            inSubFile >> count2;
        while(inSubFile.eof() == false){
            inSubFile >> sub1;
            User* s1 = new User;
            s1->id = sub1;
//            s1->l = nullptr;
            users.add(s1);
        }
        cout << count2 << " subscribers and " << count1 << " movies have been loaded" << endl;
    }
    }
}
MovieRentalSystem::~MovieRentalSystem(){
}

void MovieRentalSystem::removeMovie(const int movieId){
    Movie temp;
    temp.movieId = movieId;
    temp.numberOfCopies = -1;
    temp.allCopies = -1;
    int index = movies.getIndex(temp);
    if(index >= 0){
//        removeEveryMovie(movieId); //removed every movie after deleting it
        if(users.iterateUsersForMovie(temp)){
            cout << "Movie " << movieId << " cannot be removed -- at least one copy has not been returned" << endl;
        }
        else{
            movies.remove(index);
            cout << "Movie " << movieId << " has been removed" << endl;
        }
    }
    else{
        cout << "Movie " << movieId << " does not exist" << endl;
    }
}
void MovieRentalSystem::addMovie(const int movieId, const int numCopies){
    Movie* temp = new Movie;
    temp->movieId = movieId;
    temp->numberOfCopies = numCopies;
    temp->allCopies = numCopies;
    movies.add(temp);//add movie w specialized template
    if(temp != nullptr){
        cout << "Movie " << movieId << " has been added" << endl;
    }
}
void MovieRentalSystem::removeSubscriber(const int subscriberId){
    User temp;
    temp.id = subscriberId;
//    temp.l = nullptr;
    int index = users.getIndex(temp);
    if(index >= 0){
        Transac temp1;
        temp1.movieId = -1;
        temp1.id = subscriberId;
        temp1.isOpen = 1;
        if(users.get(temp)->item->l.getSpecific(temp1, 2) > 0){
            cout << "Subscriber " << subscriberId << " cannot be removed -- at least one movie has not been returned" << endl;
            return;
        }
        users.remove(index);//remove user
        cout << "Subscriber " << subscriberId << " has been removed" << endl;
    }
    else{
        cout << "There is no such user" << endl;
    }
}
void MovieRentalSystem::rentMovie(const int subscriberId, const int movieId){
    Movie temp;
    User tempU;
    temp.allCopies = -1;
    temp.movieId = movieId;
    temp.numberOfCopies = -1;
    tempU.id = subscriberId;
    if(movies.doesExist(temp) && users.doesExist(tempU)){
        if(movies.get(temp)->item->numberOfCopies != 0){
            movies.get(temp)->item->numberOfCopies--;
            //add a transaction to the linked list
            Transac* newT = new Transac;
            newT->movieId =movieId;
            newT->id = subscriberId;
            newT->isOpen = 1;
            users.get(tempU)->item->l.add(newT);
            cout << "Movie " << newT->movieId << " has been rented by subscriber " << newT->id << endl;
        }
        else{
            cout << "Movie " << movieId << " has no available copy for renting" << endl;
        }
    }
    else{
        if(!movies.doesExist(temp) && !users.doesExist(tempU)){
            cout << "Subscriber " << subscriberId << " and movie " << movieId << " do not exist" << endl;
        }
        else if(!movies.doesExist(temp)){
            cout << "Movie " << movieId << " does not exist" << endl;
        }
        else if(!users.doesExist(tempU)){
            cout << "Subscriber " << subscriberId << " does not exist" << endl;
        }
    }
}
void MovieRentalSystem::returnMovie(const int subscriberId, const int movieId){
    Transac temp;
    Movie tempM;
    tempM.allCopies = -1;
    tempM.numberOfCopies = -1;
    temp.movieId = movieId;
    temp.id = subscriberId;
    tempM.movieId = movieId;
    temp.isOpen = 1;
    User tempU;
    tempU.id = subscriberId;
    if(users.get(tempU)->item->l.get(temp) != nullptr){
        if(users.get(tempU)->item->l.get(temp)->item->isOpen == 1){
            users.get(tempU)->item->l.remove(users.get(tempU)->item->l.getIndex(*(users.get(tempU)->item->l.get(temp)->item))); // get(temp)->item->isOpen = 0;
            movies.get(tempM)->item->numberOfCopies++;
            Transac* newT = new Transac;
            newT->movieId = movieId;
            newT->id = subscriberId;
            newT->isOpen = 0;
            users.get(tempU)->item->l.add(newT);
            cout << "Movie " << movieId << " has been returned by subscriber " << subscriberId << endl;
        }
        else{
            cout << "No rental transaction for subscriber " << subscriberId << " and movie " << movieId << endl;
        }
    }
    else{
        cout << "No rental transaction for subscriber " << subscriberId << " and movie " << movieId << endl;
    }
}
void MovieRentalSystem::showMoviesRentedBy(const int subscriberId) const{
    User tempU;
    tempU.id = subscriberId;
//    tempU.l = nullptr;
    Transac* temp = new Transac;
    temp->id = subscriberId;
    temp->movieId = -1;
    temp->isOpen = -1;
    if( users.get(tempU) == nullptr){
        cout << "Subscriber " << subscriberId << " does not exist" << endl;
        delete temp;
    }
    else{
        if(users.get(tempU)->item->l.head != nullptr){
            cout << "Subscriber " << subscriberId << " has rented the following movies:" << endl;
            users.get(tempU)->item->l.showSpecific(temp, 0);
        }
        else{
            cout << "Subscriber " << subscriberId << " has not rented any movies" << endl;
            delete temp;
        }
    }
}
void MovieRentalSystem::showSubscribersWhoRentedMovie(const int movieId) const{
    User tempU;
    Movie m;
    m.movieId = movieId;
    m.allCopies = -1;
    m.numberOfCopies = -1;
    Transac* temp = new Transac;
    temp->movieId = movieId;
    temp->id = -1;
    temp->isOpen = -1;
    if(!users.iterateUsersForMovie(m) && movies.get(m) != nullptr){
        cout << "Movie " << movieId << " has not been rented by any subscriber" << endl;
    }
    else if(!users.iterateUsersForMovie(m) && movies.get(m) == nullptr){
        cout << "Movie " << movieId << " does not exist" << endl;
    }
    else{
        cout << "Movie " << movieId << " has been rented by the following subscribers:" << endl;
        users.iterateUsersForMovieVerbose(m);
    }
    delete temp;
}
void MovieRentalSystem::showAllMovies() const{
    cout << "Movies in the movie rental system:" << endl;
    movies.show();
}
void MovieRentalSystem::showAllSubscribers() const{
    cout << "Subscribers in the movie rental system:" << endl;
    users.show();
}
