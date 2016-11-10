// Implementation of the templated Vector class
// ECE4893/8893 lab 3
// Jai Chauhan

#include <iostream> // debugging
#include "Vector.h"

// Your implementation here
// Fill in all the necessary functions below
using namespace std;

// Default constructor
template <typename T>
Vector<T>::Vector()
{
  count = 0;
  elements = (T*) malloc(1 * sizeof(T));
  reserved = 1;
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rhs)
{
  count = rhs.Size();
  elements = (T*) malloc(count * sizeof(T));
  reserved = count;
  VectorIterator<T> it = rhs.Begin();
  VectorIterator<T> end = rhs.End();
  int i = 0;
  while(it != end) { 
    new (&elements[i]) T(*it);
    ++it;
    i++; 
  }
}

// Assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
  /*
  if (&rhs != this) {
    for (int i = 0; i < count; i++) {
      elements[i].~T();
    }
    free(elements);
    count = rhs.Size();
    reserved = count;
    elements = (T*) malloc(count * sizeof(T));
    for (int i = 0; i < count; i++) {
      new (&elements[i]) T(rhs[i]);
    }
    return *this;
  }
  */
}


#ifdef GRAD_STUDENT

// Other constructors
template <typename T>
Vector<T>::Vector(size_t nReserved)
{ // Initialize with reserved memory
}

template <typename T>
Vector<T>::Vector(size_t n, const T& t)
{ // Initialize with "n" copies of "t"
}

template <typename T>
void Vector<T>::Reserve(size_t n)
{ // Reserve extra memory

}

#endif

// Destructor 
template <typename T>
Vector<T>::~Vector()
{
  
  if(count != 0) {
    for(int i = 0; i < count; i++) {
      elements[i].~T();
    } 
  }
  if(reserved != 0) {
     free(elements);
  } 
}

// Add and access front and back
template <typename T>
void Vector<T>::Push_Back(const T& rhs)
{
  if(count == reserved) {
    //resize and copy over
    T* temp = elements;
    //VectorIterator<T> it = Begin();
    elements = (T*) malloc((count + 4) * sizeof(T));
    reserved = reserved + 4;
    for (int i = 0; i < count; i++) {
      new (&elements[i]) T(temp[i]);
      temp[i].~T();
    }
    free(temp); 
  }
  //get end pointer
  T* lastelement = &elements[count];
  new (lastelement) T(rhs);
  //cout << (elements[count]) << endl;
  count++;
}

template <typename T>
void Vector<T>::Push_Front(const T& rhs)
{
    if(count == reserved) {
    //resize and copy over
    T* temp = elements;
    elements = (T*) malloc((count + 4) * sizeof(T));
    reserved = reserved + 4;
    for (int i = 0; i < count; i++) {
      new (&elements[i]) T(temp[i]);
      temp[i].~T();
    }
    free(temp); 
    }
    //shift Right
    for (int i = count; i > 0 ; i--) {
      new (&elements[i]) T(elements[i-1]);
      elements[i-1].~T();
    }
    new (elements) T(rhs);
    count++;
}

template <typename T>
void Vector<T>::Pop_Back()
{ // Remove last element
  elements[count - 1].~T();
  count--;
}

template <typename T>
void Vector<T>::Pop_Front()
{ // Remove first element
  //shift left 
  elements[0].~T(); 
  for(int i = 0; i < count - 1; i++) {
    new (&elements[i]) T(elements[i + 1]);
    elements[i + 1].~T();
  }
  count--;
}

// Element Access
template <typename T>
T& Vector<T>::Front() const
{
  return *elements;
}

// Element Access method
template <typename T>
T& Vector<T>::Back() const
{
  return elements[count - 1];
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const
{ // const element access
  //cout << "In const access" << endl;
  return elements[i];
}

template <typename T>
T& Vector<T>::operator[](size_t i)
{//nonconst element access
  //cout << "In nonconst access" << endl;
  return elements[i];
}

template <typename T>
size_t Vector<T>::Size() const
{
  return count;
}

template <typename T>
bool Vector<T>::Empty() const
{
  return count == 0; 
}

// Implement clear
template <typename T>
void Vector<T>::Clear()
{
  for(int i = 0; i < count; i++) {
    elements[i].~T();
  }
  free(elements); 
  count = 0;
  reserved = 0;
}

// Iterator access functions
template <typename T>
VectorIterator<T> Vector<T>::Begin() const
{
  return VectorIterator<T>(elements);
}

template <typename T>
VectorIterator<T> Vector<T>::End() const
{
  return VectorIterator<T>(&elements[count]);
}

#ifdef GRAD_STUDENT
// Erase and insert
template <typename T>
void Vector<T>::Erase(const VectorIterator<T>& it)
{
}

template <typename T>
void Vector<T>::Insert(const T& rhs, const VectorIterator<T>& it)
{
}
#endif

// Implement the iterators

// Constructors
template <typename T>
VectorIterator<T>::VectorIterator()
{
  current = NULL;
}

template <typename T>
VectorIterator<T>::VectorIterator(T* c)
{
  current = c;
}

// Copy constructor
template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator<T>& rhs)
{
  current = rhs.current;
}

// Iterator defeferencing operator
template <typename T>
T& VectorIterator<T>::operator*() const
{
  return *current;
}

// Prefix increment
template <typename T>
VectorIterator<T>  VectorIterator<T>::operator++()
{
  return (++current);
}

// Postfix increment
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int)
{
  return (current++);
}

// Comparison operators
template <typename T>
bool VectorIterator<T>::operator !=(const VectorIterator<T>& rhs) const
{
  return current != rhs.current;
}

template <typename T>
bool VectorIterator<T>::operator ==(const VectorIterator<T>& rhs) const
{
  return current == rhs.current;
}





