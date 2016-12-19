#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Node.hpp"

using namespace std;

template <class T> 
class LinkedList {
    private:
        /* pointer to the first node */
        Node<T>* front;
        /* pointer to the last node */
        Node<T>* back;

    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* returns the first node of the linked list */
        Node<T>& getFront() const;
        /* returns the last node of the linked list */
        Node<T>& getBack() const;
        /* returns the node in given "pos"ition of the linked list */
        Node<T>& getNodeAt(int pos) const;
        /* returns the pointer of the node in given 
           "pos"ition of the linked list */
        Node<T>* getNodePtrAt(int pos) const;
        
        /* inserts a new node containing "data" 
           after the node "prev" 
           */
        void insert(Node<T>* prev, const T& data);
        /* inserts a new node containing "data" 
           at "pos"ition in the linked list 
           */
        void insertAt(int pos, const T& data);
        /* erases the given "node" from the linked list */
        void erase(Node<T>* node);
        /* erases the node in given "pos"ition from the linked list */
        void eraseFrom(int pos);
        /* clears the contents of the linked list */
        void clear();

        /* inserts a new node containing "data" 
           to the front of the linked list 
           */
        void pushFront(const T& data);
        /* inserts a new node containing "data" 
           to the back of the linked list
           */
        void pushBack(const T& data);

        /* removes the first node */
        void popFront();
        /* removes the last node */
        void popBack();

        /* returns true if the list is empty, false otherwise */
        bool isEmpty() const;
        /* returns the number of items in the list */
        size_t getSize() const;
        /* prints the contents of the linked list 
           one node data per line
           assumes the objects in the node have operator<< overloaded 
           */
        void print() const;

};


template <class T>
LinkedList<T>::LinkedList(){
  front=NULL;
  back=NULL;
}

//COPY AND ASSIGMENT
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll){
  //*this=ll;
  front=NULL;
  back=NULL;
  Node<T>* temp=ll.getNodePtrAt(0);
  while(temp!=NULL){
    pushBack(temp->getData());
    temp=(temp->getNext());
  }
}
template<class T>
LinkedList<T>&  LinkedList<T>::operator=(const LinkedList<T>& ll){
  clear();
  Node<T>* temp=ll.getNodePtrAt(0);
  while(temp!=NULL){
    pushBack(temp->getData());
    temp=(temp->getNext());
  }
  return *this;
}
template<class T>
LinkedList<T>::~LinkedList(){
  clear();
}

template <class T>
Node<T>& LinkedList<T>::getFront() const{
  return *front;
}
template <class T>
Node<T>& LinkedList<T>::getBack() const{
  return *back;
}
template <class T>
Node<T>& LinkedList<T>::getNodeAt(int pos) const{
  if(pos<0 or pos>getSize()){
    throw out_of_range("Bad Input get node at");
  }  
  Node<T>* retval=front;
  for(int i=0;i<pos;i++){
        retval=retval->getNext();
  }
  return *retval;
}
template <class T>
Node<T>* LinkedList<T>::getNodePtrAt(int pos) const{
  if(pos<0 or pos>getSize()){
    throw out_of_range("Bad Input get node ptr at");
  }
  Node<T>* retval=front;
  for(int i=0;i<pos;i++){
        retval=retval->getNext();
  }
  return retval;
}

template <class T>
void LinkedList<T>::insert(Node<T>* prev,const T& data){
  if(prev==NULL){
    pushFront(data);
  }
  else if(prev==back){
    pushBack(data);
  }
  else{
    Node<T>* newNode=new Node<T>();
    newNode->setData(data);
    prev->getNext()->setPrev(newNode);
    newNode->setNext(prev->getNext());
    newNode->setPrev(prev);
    prev->setNext(newNode);
    }
}
template <class T>
void LinkedList<T>::insertAt(int pos,const T& data){
  if(pos<0 or pos>getSize()){
    throw out_of_range("bad input at insertAt");
  }
  if(pos==0){
    pushFront(data);
  }
  else if(pos==getSize()){
    pushBack(data);
  }
  else{
    Node<T>* tmp=getNodePtrAt(pos);
    Node<T>* newNode=new Node<T>();
    newNode->setData(data);
    tmp->getPrev()->setNext(newNode);
    newNode->setNext(tmp);
    newNode->setPrev(tmp->getPrev());
    tmp->setPrev(newNode);
  }
  
}


template <class T>
void LinkedList<T>::pushFront(const T& data){
  Node<T>* newNode=new Node<T>();
  newNode->setData(data);
  if(front==NULL){
    front=newNode;
    back=newNode;
  }
  else {
    newNode->setNext(front);
    front->setPrev(newNode);
    front=newNode;
    newNode->setPrev(NULL);
  }
}

template <class T>
void LinkedList<T>::pushBack(const T& data){
  Node<T>* newNode=new Node<T>();
  newNode->setData(data);
  if(front==NULL){
    front=newNode;
    back=newNode;
  }
  else {
    newNode->setPrev(back);
    back->setNext(newNode);
    back=newNode;
    newNode->setNext(NULL);
  }

}

template <class T>
void LinkedList<T>::erase(Node<T>* node){
  if(node==front){

    popFront();
  }
  else if(node==back){
    popBack();
  }
  else {
    node->getNext()->setPrev(node->getPrev());
    node->getPrev()->setNext(node->getNext());
    node->setNext(NULL); node->setPrev(NULL);
    delete node;
  }

}
template <class T>
void LinkedList<T>::eraseFrom(int pos){
if(pos<0 or pos>getSize()){
  throw out_of_range("bad input at eraseFrom");
}
Node<T>* tmp=getNodePtrAt(pos);
erase(tmp);
}

template <class T>
void LinkedList<T>::clear(){
  while(!isEmpty()){
    popFront();
  }
}


template <class T>
void LinkedList<T>::popFront(){
  Node<T>* tmp;
  tmp=front;
  if(front==back){
    front=NULL;
    back=NULL;
  }
  else{
    front=front->getNext();
    front->setPrev(NULL);
  }
  delete tmp;
}
template <class T>
void LinkedList<T>::popBack(){
  Node<T>* tmp;
  tmp=back;
  if(front==back){
    front=NULL;
    back=NULL;
  }
  else {
    back=back->getPrev();
    back->setNext(NULL);
  }
  delete tmp;
}

template <class T>
bool LinkedList<T>::isEmpty() const{
  return front==NULL;
}
template <class T>
size_t LinkedList<T>::getSize() const{
  if(front==NULL){
    return 0;
  }
  size_t size=1;
  Node<T>* current=front;
  while(current->getNext()!=NULL){
    size++;
    current=current->getNext();
  }
  return size;
}

template <class T>
void LinkedList<T>::print() const{
  Node<T>* current=front;
  if(front!=NULL){
    while(current->getNext()!=NULL){
        cout << current->getData() << endl;
        current=current->getNext();
    }
    cout << current->getData() << endl;
  }
}

#endif