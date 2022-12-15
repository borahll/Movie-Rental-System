//
//  LinkedList.cpp
//  cs_hw3
//
//  Created by Bora Haliloglu on 30.11.2022.
//  22101852
//  Section 3
#include "MovieRentalSystem.h"
#include "LinkedList.hpp"
#include <iostream>
#include <string>


using namespace std;
template<>
bool Node<Movie>::operator==(const Movie& right){
    if(this->item->movieId == right.movieId){
        return 1;
    }
    return 0;
}
template<>
bool Node<User>::operator==(const User& right){
    if(this->item->id == right.id){
        return 1;
    }
    return 0;
}
template<>
bool Node<Transac>::operator==(const Transac& right){
    if(this->item->movieId == right.movieId && this->item->id == right.id){
        return 1;
    }
    return 0;
}
template <>
int LinkedList<Movie>::getAppropiateIndex(Movie a){ // returns the index for the last index for the closest smallest Node
    if(this->itemCount <= 0){
        return 0;
    }
    else{
        int ind = 0;
        Node<Movie>* point = head;
        while(point != nullptr  && !(point->item->movieId > a.movieId)){
            point = point->next;
            ind++;
        }
        return ind;
    }
}
template <>
int LinkedList<Transac>::getAppropiateIndex(Transac a){ // returns the index for the last index for the closest smallest Node
    if(this->itemCount <= 0){
        return 0;
    }
    else{
        int ind = 0;
        Node<Transac>* point = head;
        while(point != nullptr && !(point ->item->movieId > a.movieId )){
            point = point->next;
            ind++;
        }
        if(point->item->movieId == a.movieId){
            if(point->item->id < a.movieId){
                ind++;
            }
        }
        return ind;
    }
}
template <>
int LinkedList<User>::getAppropiateIndex(User a){ // returns the index for the last index for the closest smallest Node
    if(this->itemCount <= 0){
        return 0;
    }
    else{
        int ind = 0;
        Node<User>* point = head;
        while(point != nullptr && (point->item->id > a.id )){
            point = point->next;
            ind++;
        }
        return ind;
    }
}
template<>
bool LinkedList<Movie>::doesExist(Movie a){
    bool found = 0;
    Node<Movie>* ptr = head;
    while(ptr != nullptr  && ptr->item->movieId != a.movieId){
        ptr = ptr->next;
    }
    if(head == nullptr){
        found = 0;
    }
    else if(ptr == nullptr){
        found = 0;
    }
    else{
        found = (ptr->item->movieId == a.movieId) ? 1:0;
    }
    return found;
}
template<>
bool LinkedList<User>::doesExist(User a){
    bool found = 0;
    Node<User>* ptr = head;
    while(ptr != nullptr && ptr->item->id != a.id){
        ptr = ptr->next;
    }
    if(head == nullptr || ptr == nullptr){
        found = 0;
    }
    else{
        found = (ptr->item->id == a.id) ? 1:0;
    }
    return found;
}
template<>
bool LinkedList<Transac>::doesExist(Transac a){
    bool found = 0;
    Node<Transac>* ptr = head;
    while(ptr != nullptr && ptr->item->id != a.id){
        ptr = ptr->next;
    }
    if(head == nullptr || ptr == nullptr){
        found = 0;
    }
    else{
        found = (ptr->item->id == a.id) ? 1:0;
    }
    return found;
}

template <>
int LinkedList<User>::getIndex(User a){
    Node<User>* ptr = head;
    if(head == nullptr){
        return -1;
    }
    else{
        int index = 0;
        bool found = 0;
        while(ptr != nullptr && !((ptr->item->id) == a.id)){
            index++;
            ptr = ptr->next;
        }
        if(ptr == nullptr){
            return -1;
        }else{
            found = ((*ptr) == a) ? 1:0;
            if(found){
                return index;
            }
            else{
                return -1;
            }
        }
    }
}
template <>
int LinkedList<Movie>::getIndex(Movie a){
    Node<Movie>* ptr = head;
    if(head == nullptr){
        return -1;
    }
    int index = 0;
    bool found = 0;
    while(ptr != nullptr && !(ptr->item->movieId == a.movieId)){
        ptr = ptr->next;
        index++;
    }
    if(ptr == nullptr){
        return -1;
    }else{
        found = (ptr->item->movieId == a.movieId) ? 1:0;
        if(found){
            return index;
        }
        else{
            return -1;
        }
    }
}
template <>
int LinkedList<Transac>::getIndex(Transac a){
    Node<Transac>* ptr = head;
    if(head == nullptr){
        return -1;
    }
    int index = 0;
    bool found = 0;
    while(ptr != nullptr && !(ptr->item->movieId == a.movieId && ptr->item->id == a.id && ptr->item->isOpen == a.isOpen)){
        ptr = ptr->next;
        index++;
    }
    if(ptr == nullptr){
        return -1;
    }else{
        found = (ptr->item->movieId == a.movieId && ptr->item->id == a.id && ptr->item->isOpen == a.isOpen) ? 1:0;
        if(found){
            return index;
        }
        else{
            return -1;
        }
    }
}

template<>
Node<Movie>* LinkedList<Movie>::get(Movie a) const{
    Node<Movie>* ptr = head;
    if(head == nullptr){
        return nullptr;
    }
    bool found = 0;

    
    while(ptr != nullptr  && !(*ptr == a)){
        ptr = ptr -> next;
    }
    if(ptr == nullptr){
        return nullptr;
    }
    else{
        found = (ptr->item->movieId == a.movieId) ? 1:0;
        if(found){
            return ptr;
        }
        return nullptr;
    }
}
template<>
Node<User>* LinkedList<User>::get(User a) const{
    Node<User>* ptr = head;
    if(head == nullptr){
        return nullptr;
    }
    bool found = 0;

    
    while(ptr != nullptr && !(ptr->item->id == a.id)){
        ptr = ptr -> next;
    }
    if(ptr == nullptr){
        return nullptr;
    }
    else{
        found = (ptr->item->id == a.id) ? 1:0;
        if(found){
            return ptr;
        }
        return nullptr;
    }
}
template<>
Node<Transac>* LinkedList<Transac>::get(Transac a)const{
    Node<Transac>* ptr = head;
    if(head == nullptr){
        return nullptr;
    }
    bool found = 0;
    while(ptr != nullptr  && !(ptr->item->movieId == a.movieId && ptr->item->isOpen == a.isOpen && ptr->item->id == a.id)){
        ptr = ptr -> next;
    }
    if(ptr == nullptr){
        return nullptr;
    }
    else{
        found = (ptr->item->movieId == a.movieId && ptr->item->isOpen == a.isOpen && ptr->item->id == a.id) ? 1:0;
        if(found){
            return ptr;
        }
        return nullptr;
    }

}

template <>
void LinkedList<Movie>::show() const{
    if(itemCount <= 0){
        cout << "There are no movies" << endl;
    }
    else{
        Node<Movie>* ptr = head;
        // && ptr->next != nullptr
        while(ptr != nullptr){
            cout << ptr->item->movieId << " " << ptr->item->allCopies << endl;
            ptr = ptr->next;
        }
    }
}
template <>
void LinkedList<User>::show() const{
    if(itemCount <= 0){
        cout << "There are no movies" << endl;
    }
    else{
        Node<User>* ptr = head;
        // && ptr->next != nullptr
        while(ptr != nullptr){
            cout << ptr->item->id << endl;
            ptr = ptr->next;
        }
    }
}
template <>
void LinkedList<Transac>::show() const{
    if(itemCount <= 0){
        cout << "There are no movies" << endl;
    }
    else{
        cout << "Items:" << endl;
        Node<Transac>* ptr = head;
        // && ptr->next != nullptr
        while(ptr != nullptr){
            cout << ptr->item->movieId << " " << ptr->item->id << endl;
            ptr = ptr->next;
        }
    }
}

template<>
void LinkedList<Movie>::showSpecific(Movie* a, int decide) const{
    Node<Movie>* ptr = head;
    if(head == nullptr){
        delete a;
        return;
    }

    while(ptr != nullptr){
        if(ptr->item->movieId == a->movieId && ptr->item->numberOfCopies == a->numberOfCopies){
            cout << ptr->item->movieId << " " << ptr->item->numberOfCopies << endl;
        }
        ptr = ptr -> next;
    }
}
template<>
void LinkedList<Movie>::add(Movie*& aNode){
    if(doesExist(*aNode)){
        delete aNode;
    }
    else{
        Node<Movie>* newNode = new Node<Movie>;
        newNode->item = aNode;
        newNode->next = nullptr;
        if(isEmpty()){ // element number == 0
            head = newNode; 
        }
        else{
            Node<Movie>* tempLeft = head;
            Node<Movie>* tempRight = head->next;
            if(tempLeft->item->movieId > aNode->movieId){ //first element is larger
                // aNodeID < currentHead->ID  insert at the beginning
                newNode->next = tempLeft;
                head = newNode;            
            }
            else{
                while(tempRight != nullptr && tempRight->item->movieId < aNode->movieId){ //multiple elements
                    tempLeft = tempRight;
                    tempRight = tempRight->next;
                }
                tempLeft->next = newNode;
                newNode->next = tempRight;
            }
        }
        itemCount++;
    }
}
template<>
void LinkedList<Transac>::add(Transac*& aNode){
        Node<Transac>* newNode = new Node<Transac>;
        newNode->item = aNode;
        newNode->next = nullptr;
        if(isEmpty()){ // element number == 0
            head = newNode; 
        }
        else{
            Node<Transac>* tempLeft = head;
            Node<Transac>* tempRight = head->next;
            if(tempLeft->item->movieId > aNode->movieId){ //first element is larger
                // aNodeID < currentHead->ID  insert at the beginning
                newNode->next = tempLeft;
                head = newNode;            
            }
            else{
                while(tempRight != nullptr && tempRight->item->movieId < aNode->movieId){ //multiple elements
                    tempLeft = tempRight;
                    tempRight = tempRight->next;
                }
                while(tempRight != nullptr && tempRight->item->movieId == aNode->movieId && tempRight->item->isOpen < aNode->isOpen){
                    tempLeft = tempRight;
                    tempRight = tempRight->next;
                }
                tempLeft->next = newNode;
                newNode->next = tempRight;
            }
        }
        itemCount++;
}
template<>
void LinkedList<User>::add(User*& aNode){
    if(doesExist(*aNode)){
        delete aNode;
    }
    else{
        Node<User>* newNode = new Node<User>;
        newNode->item = aNode;
        newNode->next = nullptr;
        if(isEmpty()){ // element number == 0
            head = newNode; 
        }
        else{
            Node<User>* tempLeft = head;
            Node<User>* tempRight = head->next;
            if(tempLeft->item->id > aNode->id){ //first element is larger
                // aNodeID < currentHead->ID  insert at the beginning
                newNode->next = tempLeft;
                head = newNode;            
            }
            else{
                while(tempRight != nullptr && tempRight->item->id < aNode->id){ //multiple elements
                    tempLeft = tempRight;
                    tempRight = tempRight->next;
                }
                tempLeft->next = newNode;
                newNode->next = tempRight;
            }
        }
        itemCount++;
    }
}
template<>
void LinkedList<Transac>::showSpecific(Transac* a, int decide) const{
    Node<Transac>* ptr = head;
    if(head == nullptr){
        delete a;
        return;
    }
    while(ptr != nullptr){
        if(ptr->item->movieId == a->movieId && decide == 1 ){ // for showing the movie specific
            if(ptr->item->isOpen == 0){
                cout << ptr->item->id << " returned" << endl;
            }
            else{
                cout << ptr->item->id << " not returned" << endl;
            }
        }
        if(ptr->item->id == a->id && decide == 0){ // for showing the user specific
            if(ptr->item->isOpen == 0){
                cout << ptr->item->movieId << " returned" << endl;
            }
            else{
                cout << ptr->item->movieId << " not returned" << endl;
            }
        }
        ptr = ptr -> next;
    }
    delete a;
}
template <>
int LinkedList<Transac>::getSpecific(Transac a, int dest){
    Node<Transac>* ptr = head;
    if(head == nullptr){
        return -1;
    }
    int index = 0;
    while(ptr != nullptr){
        if(ptr->item->isOpen == 1 && ptr->item->id == a.id && dest == 2){
            return 1;
        }
        if(ptr->item->movieId == a.movieId && dest == 1){
            return index;
        }
        else if(ptr->item->id == a.id && dest == 0){
            return index;
        }
        ptr = ptr->next;
        index++;
    }
    return -1;
}
template<>
bool LinkedList<User>::iterateUsersForMovie(Movie a)const{
    Node<User>* ptr = head;
    if(ptr == nullptr){
        return 0;
    }
    else{
        while(ptr != nullptr){
            Transac a1;
            a1.movieId = a.movieId;
            a1.id = -1;
            a1.isOpen = -1;
            if(ptr->item->l.getSpecific(a1, 1) >= 0){
                if(ptr->item->l.getIndex(a1) >= 0){
                    return true;
                }
                else{
                    return true;
                }
            }
            ptr = ptr -> next;
        }
        return false;
    }
}
template<>
bool LinkedList<User>::iterateUsersForMovieVerbose(Movie a)const{
    Node<User>* ptr = head;
    if(ptr == nullptr){
        return 0;
    }
    else{
        Transac a1;
        a1.movieId = a.movieId;
        a1.isOpen = 1;
        a1.id = -1;
        while(ptr != nullptr){
            // go over every users transaction linkedlist
                if(ptr->item->l.getSpecific(a1, 1) >= 0){
                    Node<Transac>* ptr2 = ptr->item->l.head;
                    while(ptr2 != nullptr){// checks if there is that specific movie in that linked list
                        if(ptr2->item->isOpen == 1 && ptr2->item->movieId == a.movieId){
                            cout << ptr->item->id << " not returned" << endl;
                        }
                        else if(ptr2->item->isOpen == 0 && ptr2->item->movieId == a.movieId){
                            cout << ptr->item->id << " returned" << endl;
                        }
                        ptr2 = ptr2->next;
                    }
                }
                ptr = ptr -> next;
            }
        }
        return true;
    }
