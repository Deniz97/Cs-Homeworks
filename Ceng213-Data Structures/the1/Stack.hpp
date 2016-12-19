#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T> 
class Stack {

    private:
        /* array keeping the items of the stack */
        T* items;
        /* number of items in the stack */
        size_t size;
        /* capacity of the stack */
        size_t capacity;

        /*** You can add other private members ***/

        void arrayCopy(T* a1,T* a2,int size);
    public:
        /*** Do not modify the interface ***/

        /* Creates a stack of given "capacity" 
           defult is 8 items
           */
        Stack(int capacity=8);

        /* Copy constructor, Assignment operator, Destructor*/
        Stack(const Stack<T>& stack);
        Stack<T>& operator=(const Stack<T>& stack);
        ~Stack();

        /* pushes the "item" to the top of the stack 
           increases the capacity as needed
           doubles the capacity when full
           */
        void push(const T& item);
        /* pops the item at the top of the stack and returns 
           decreases the capacity when needed
           halves the capacity when less then 1/3 full
           */
        T pop();
        /* returns the item at the top of the stack witout modifiying the stack 
           (take a look at the top item) 
           */
        const T& top() const;
        /* clears the contents of the stack */
        void clear();
        /* returns true if the stack is empty, false otherwise */
        bool isEmpty() const;
        /* returns the number of items in the stack */
        size_t getSize() const;
        /* returns the capacity the stack */
        size_t getCapacity() const;
        /* prints the contents of the stack 
           from top to bottom, one item per line
           assumes the objects in the stack have operator<< overloaded 
           */
        void print() const;
        /* prints the contents of the stack 
           from bottom to top, one item per line
           assumes the objects in the stack have operator<< overloaded 
           */
        void printReversed() const;

        /*** Do not modify the interface ***/
};


/* TO-DO: method implementations here */
template <class T>
Stack<T>::Stack(int capacity){
      this->capacity=capacity;
      this->size=0;
      this->items=new T[capacity];
}
//copy,assign,destruct
  template <class T>
  Stack<T>::Stack(const Stack<T>& stack){
    capacity = stack.capacity;
    size=stack.size;
    items = new T[stack.capacity];
    arrayCopy(stack.items,items,size);
  }

  template <class T>
  Stack<T>& Stack<T>::operator=(const Stack<T>& stack){
    delete[] items; 
    capacity = stack.capacity;
    size=stack.size;
    items = new T[stack.capacity];
    arrayCopy(stack.items,items,size);
    return *this;
  }

  template <class T>
  Stack<T>::~Stack(){
    delete[] items;
  }

template <class T>
void Stack<T>::push(const T& item){
      if(capacity==size){
              T* tempArray = new T[capacity*2];
              arrayCopy(items,tempArray,size);
              delete[] items;
              items=tempArray;
              capacity*=2;
      }
      items[size]=item;
      size++;
}

template <class T>
T Stack<T>::pop(){
      if(size<=0){
        throw out_of_range("empty stack");
      }
      if(size*3< capacity && capacity>=16  ){
        T* tempArray = new T[capacity/2];
        arrayCopy(items,tempArray,size);
        if(items!=NULL){
            delete[] items;
        }
        items=tempArray;
        //if(capacity/2<8){
         // capacity=8;}
        //else {
         // capacity/=2;
        //}
        capacity=capacity/2;

      }
      size--;
      return items[size];
}

template <class T>
const T& Stack<T>::top() const{
      if(size<=0){
        throw out_of_range("empty stack");
      }      
      return items[size-1];
}

template <class T>
void Stack<T>::clear(){
      delete[] items;
      items = new T[8];
      size=0;
}

template <class T>
bool Stack<T>::isEmpty() const{
      return size==0;
}

template <class T>
size_t Stack<T>::getSize() const{
      return size;
}

template <class T>
size_t Stack<T>::getCapacity() const{
      return capacity;
}

template <class T>
void Stack<T>::printReversed() const{
      for(int i=0;i<size;i++){
        cout << items[i] << endl;
      }
}

template <class T>
void Stack<T>::print() const {
      for (int i = size-1; i>=0; i--){
            cout << items[i] << endl;
      }

}
template <class T>
void Stack<T>::arrayCopy(T* full, T*empty,int size){
      for(int i=0;i<size;i++){
              empty[i]=full[i];
      }
}
#endif