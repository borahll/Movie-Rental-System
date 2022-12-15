//
//  LinkedList.hpp
//  cs_hw3
//
//  Created by Bora Haliloglu on 30.11.2022.
//  22101852
//  Section 3

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <stdio.h>
#include <iostream>
using namespace std;


struct Movie;
struct User;
struct Transac;

template <typename T>
struct Node{
    T* item = nullptr;
    Node<T>* next = nullptr;
    ~Node<T>(){
        next = nullptr;
        delete item;
    };
    bool operator==(const T&);
};



template <typename T>
class LinkedList{
    public:
//        LinkedList(const LinkedList&);
        //LinkedList(int);
        LinkedList();
        ~LinkedList();
        void add(T*&); //Done Done
        Node<T> getItem(int); //Done
        Node<T>* get(T)const; // Done
        bool isEmpty();
        int getLenght();
        void replace(int , T& );
        void remove(int); // Done
        bool doesExist(T); // Done
        int getIndex(T);
        int getAppropiateIndex(T); //Done Done
        void show() const; //Done Done
        void showSpecific(T*, int) const;
        int getSpecific(T, int);
        void setItemCount();
        bool iterateUsersForMovie(Movie)const;
        bool iterateUsersForMovieVerbose(Movie)const;
        
//    private:
        Node<T>* head = nullptr;
        int itemCount;
};
template<>
bool Node<Movie>::operator==(const Movie&);
template<>
bool Node<User>::operator==(const User&);
template<>
bool Node<Transac>::operator==(const Transac&);
template<>
int LinkedList<Movie>::getAppropiateIndex(Movie);
template <>
int LinkedList<Transac>::getAppropiateIndex(Transac);
template <>
int LinkedList<User>::getAppropiateIndex(User);
template<>
bool LinkedList<Movie>::doesExist(Movie);
template<>
bool LinkedList<User>::doesExist(User);
template<>
bool LinkedList<Transac>::doesExist(Transac);

template <>
int LinkedList<User>::getIndex(User);
template <>
int LinkedList<Movie>::getIndex(Movie);
template <>
int LinkedList<Transac>::getIndex(Transac);
template<>
Node<Movie>* LinkedList<Movie>::get(Movie)const;
template<>
Node<User>* LinkedList<User>::get(User)const;
template<>
Node<Transac>* LinkedList<Transac>::get(Transac)const;
template <>
void LinkedList<Movie>::show() const;
template <>
void LinkedList<User>::show() const;
template <>
void LinkedList<Transac>::show() const;
template<>
void LinkedList<Movie>::showSpecific(Movie*, int ) const;
template<>
void LinkedList<Transac>::showSpecific(Transac*, int) const;
template <>
int LinkedList<Transac>::getSpecific(Transac, int);
template <>
bool LinkedList<User>::iterateUsersForMovie(Movie)const;
template <>
bool LinkedList<User>::iterateUsersForMovieVerbose(Movie)const;


template <class T>
LinkedList<T> :: LinkedList(){
    itemCount = 0;
    head = nullptr;
}


template <class T>
LinkedList<T> :: ~LinkedList(){
    if(this->itemCount > 0)
        while(itemCount > 0){
            remove(itemCount - 1);
        }
}
 
template <typename T>
bool Node<T>::operator==(const T& right){
    if(item == right){
        return 1;
    }
    return 0;
}
template <class T>
int LinkedList<T>::getAppropiateIndex(T a){ // returns the index for the last index for the closest smallest Node
    if(this->itemCount){
        return 0;
    }
    else{
        int ind = 0;
        Node<T>* point = head;
        while(!(point->next.item == a) || point->next != nullptr){
            point = point->next;
            ind++;
        }
        return ind;
    }
}
template <class T>
Node<T> LinkedList<T>::getItem(int a){
    Node<T>* ptr = head;
    if(ptr != nullptr){
        bool found = 0;
        int curr = 0;
        while(ptr->item != a && curr < itemCount){
            ptr = ptr->next;
            found = 0;
            curr++;
        }
        if(found){
            return *ptr;
        }
        else{
            cout << "Item not found." << endl;
        }
    }
    else{
        cout << "The list is null" << endl;
    }
}
 
template <class T>
void LinkedList<T>::remove(int index){
    if(head == nullptr){
        return;
    }
    else if(index >= itemCount || index < 0){
        cout << "Invalid index" << endl;
    }
    else{
        if(index == 0){
            //Node<T>* newRight = head-> next;
            Node<T>* ptr = head;
            if(itemCount > 0){
                head = head->next;
            }
            delete ptr;
        }
        else{
            Node<T>* ptr = head;
            int a = 0;
            while(ptr->next != nullptr && a < index - 1){
                ptr = ptr->next;
                a++;
            }
            if(index == itemCount - 1){
                delete ptr->next;
                ptr->next = nullptr;
            }
            else{
                Node<T>* right = ptr->next->next;
                delete ptr->next;
                ptr->next = right;
            }
        }
        itemCount--;
    }
}
 
template <class T>
bool LinkedList<T>::isEmpty(){
    return itemCount<=0;
}

template <class T>
int LinkedList<T>::getLenght(){
    return itemCount;
}
//template <typename T>
//void LinkedList<T>::insert


template <class T>
void LinkedList<T>::replace(int index, T& a){
    if(index >= itemCount || index < 0){
        cout << "Index error" << endl;
    }
    else{
        Node<T>* ptr = head;
        for(int a = 0; a < index; a++){
            ptr = ptr->next;
        }
        ptr->item = a;
    }
}
 
template <class T>
bool LinkedList<T>::doesExist(T a){
    Node<T>* ptr = head;
    if(head == nullptr){
        return 0;
    }
    Node<T> temp;
    temp.item = &a;
    bool found = 0;
    while(ptr->next != nullptr){
        if(*ptr == a){
            found = 1;
        }
    }
    return found;
}
template <typename T>
int LinkedList<T>:: getIndex(T a){
    Node<T>* ptr = head;
    Node<T> temp;
    temp.item = a;
    int index = 0;
    bool found = 0;
    while(!((ptr->item) == temp.item)){
        index++;
    }
    found = ((ptr->item) == temp.item) ? 0:1;
    if(found){
        return index;
    }
    else{
        cout << "No such element" << endl;
        return -1;
    }
}
template <typename T>
Node<T>* LinkedList<T>::get(T a)const{
    Node<T>* ptr = head;
    bool found = 0;
    while(ptr->next != nullptr && ptr->item != a){
        ptr = ptr -> next;
    }
    found = (ptr->item == a) ? 1:0;
    if(found){
        return ptr;
    }
    else{
        return nullptr;
    }
}
template <typename T>
void LinkedList<T>::show() const{
    cout << "Items:" << endl;
    Node<T>* ptr = head;
    while(ptr->next != nullptr){
        cout << ptr->item << endl;
        ptr = ptr->next;
    }
}
template <typename T>
void LinkedList<T>::showSpecific(T* a, int decide) const{
    Node<T>* ptr = head;
    while(ptr->next != nullptr){
        if(ptr->item == a){
            cout << ptr->item << endl;
        }
        ptr = ptr -> next;
    }
    delete a;
}
template <typename T>
int LinkedList<T>::getSpecific(T a, int dest){
    return get(a);
}
template <typename T>
void LinkedList<T>::setItemCount(){
    this->itemCount = 0;
}

struct Movie{
    int movieId;
    int numberOfCopies;
    int allCopies;
    ~Movie(){};
};
struct Transac{
    int movieId;
    int id;
    int isOpen = 0;
    ~Transac(){};
};
struct User{
    int id;
    LinkedList<Transac> l;
    ~User(){};
};
#endif /* LinkedList_hpp */
