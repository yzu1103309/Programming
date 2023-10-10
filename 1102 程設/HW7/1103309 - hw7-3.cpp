// HugeInteger test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstring>
using std::strlen;

template< typename BidIt >
class ReverseIterator // wrap iterator to run it backwards
{
public:
   using value_type = typename BidIt::value_type;
   using difference_type = typename BidIt::difference_type;
   using pointer = typename BidIt::pointer;
   using reference = typename BidIt::reference;

   // construct with value-initialized wrapped iterator
   ReverseIterator() = default;

   // construct wrapped iterator from right
   ReverseIterator( BidIt right )
      : current( right )
   {
   }

   ReverseIterator( const ReverseIterator &right )
      : current( right.current ) // initialize with compatible base
   {
   }

   // assign from compatible base
   ReverseIterator& operator=( const ReverseIterator &right )
   {
      current = right.current;
      return *this;
   }

   BidIt base() const // return wrapped iterator
   {
      return current;
   }

   reference operator*() const // return designated value
   {
      BidIt tmp = current;
      return *--tmp;
   }

   pointer operator->() const // return pointer to class object
   {
      BidIt tmp = current;
      --tmp;
      return tmp.operator->();
   }

   ReverseIterator& operator++() // preincrement
   {
      --current;
      return *this;
   }

   ReverseIterator operator++( int ) // postincrement
   {
      ReverseIterator tmp = *this;
      --current;
      return tmp;
   }

   ReverseIterator& operator--()	// predecrement
   {
      ++current;
      return *this;
   }

   ReverseIterator operator--( int ) // postdecrement
   {
      ReverseIterator tmp = *this;
      ++current;
      return tmp;
   }

   // increment by integer
   ReverseIterator& operator+=( const difference_type off )
   {
      current -= off;
      return *this;
   }

   // return this + integer
   ReverseIterator operator+( const difference_type off ) const
   {
      return ReverseIterator( current - off );
   }

   // decrement by integer
   ReverseIterator& operator-=( const difference_type off )
   {
      current += off;
      return *this;
   }

   // return this - integer
   ReverseIterator operator-( const difference_type off ) const
   {
      return ReverseIterator( current + off );
   }

   // subscript
   reference operator[]( const difference_type off ) const
   {
      return current[ static_cast< difference_type >( -off - 1 ) ];
   }

protected:
   BidIt current{}; // the wrapped iterator
};

template< typename BidIt1, typename BidIt2 >
bool operator==( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return left.base() == right.base();
}

template< typename BidIt1, typename BidIt2 >
bool operator!=( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return !( left == right );
}

template< typename BidIt1, typename BidIt2 >
bool operator<( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return right.base() < left.base();
}

template< typename BidIt1, typename BidIt2 >
bool operator>( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return right < left;
}

template< typename BidIt1, typename BidIt2 >
bool operator<=( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return !( right < left );
}

template< typename BidIt1, typename BidIt2 >
bool operator>=( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return !( left < right );
}


// CLASS TEMPLATE VectorConstIterator
template< typename MyVec >
class VectorConstIterator
{
public:
   using value_type = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer = typename MyVec::const_pointer;
   using reference = const value_type &;
   using TPtr = typename MyVec::pointer;

   VectorConstIterator()
      : ptr()
   {
   }

   VectorConstIterator( TPtr parg )
      : ptr( parg )
   {
   }

   reference operator*() const
   {
      return *ptr;
   }

   pointer operator->() const
   {
      return ptr;
   }

   VectorConstIterator& operator++()
   {
      ++ptr;
      return *this;
   }

   VectorConstIterator operator++( int )
   {
      VectorConstIterator temp = *this;
      ++ *this;
      return temp;
   }

   VectorConstIterator& operator--()
   {
      --ptr;
      return *this;
   }

   VectorConstIterator operator--( int )
   {
      VectorConstIterator temp = *this;
      -- *this;
      return temp;
   }

   VectorConstIterator& operator+=( const difference_type off )
   {
      ptr += off;
      return *this;
   }

   VectorConstIterator operator+( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp += off;
   }

   VectorConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   VectorConstIterator operator-( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp -= off;
   }

   difference_type operator-( const VectorConstIterator &right ) const
   {
      return ptr - right.ptr;
   }

   reference operator[]( const difference_type off ) const
   {
      return *( *this + off );
   }

   bool operator==( const VectorConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VectorConstIterator &right ) const
   {
      return !( *this == right );
   }

   bool operator<( const VectorConstIterator &right ) const
   {
      return ptr < right.ptr;
   }

   bool operator>( const VectorConstIterator &right ) const
   {
      return right < *this;
   }

   bool operator<=( const VectorConstIterator &right ) const
   {
      return !( right < *this );
   }

   bool operator>=( const VectorConstIterator &right ) const
   {
      return !( *this < right );
   }

   TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorIterator
template< typename MyVec >
class VectorIterator
{
public:
   using value_type = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer = typename MyVec::const_pointer;
   using reference = value_type &;
   using TPtr = typename MyVec::pointer;

   VectorIterator()
      : ptr()
   {
   }

   VectorIterator( TPtr parg )
      : ptr( parg )
   {
   }

   reference operator*() const
   {
      return *ptr;
   }

   pointer operator->() const
   {
      return ptr;
   }

   VectorIterator& operator++()
   {
      ++ptr;
      return *this;
   }

   VectorIterator operator++( int )
   {
      VectorIterator temp = *this;
      ++ *this;
      return temp;
   }

   VectorIterator& operator--()
   {
      --ptr;
      return *this;
   }

   VectorIterator operator--( int )
   {
      VectorIterator temp = *this;
      -- *this;
      return temp;
   }

   VectorIterator& operator+=( const difference_type off )
   {
      ptr += off;
      return *this;
   }

   VectorIterator operator+( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp += off;
   }

   VectorIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   VectorIterator operator-( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp -= off;
   }

   difference_type operator-( const VectorIterator &right ) const
   {
      return ptr - right.ptr;
   }

   reference operator[]( const difference_type off ) const
   {
      return *( *this + off );
   }

   bool operator==( const VectorIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VectorIterator &right ) const
   {
      return !( *this == right );
   }

   bool operator<( const VectorIterator &right ) const
   {
      return ptr < right.ptr;
   }

   bool operator>( const VectorIterator &right ) const
   {
      return right < *this;
   }

   bool operator<=( const VectorIterator &right ) const
   {
      return !( right < *this );
   }

   bool operator>=( const VectorIterator &right ) const
   {
      return !( *this < right );
   }

   TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   VectorVal()
      : myFirst(),
      myLast(),
      myEnd()
   {
   }

   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
   using value_type = Ty;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = Ty &;
   using const_reference = const Ty &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

private:
   using ScaryVal = VectorVal< Ty >;

public:
   using iterator = VectorIterator< ScaryVal >;
   using const_iterator = VectorConstIterator< ScaryVal >;
   using reverse_iterator = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   vector()
      : myData()
   {
   }

   vector( const size_type count )
      : myData()
   {
       myData.myFirst = new value_type[count];
       myData.myEnd = &myData.myFirst[count];
       myData.myLast = &myData.myFirst[count];

       for (size_type t = 0; t < count; t++) {
           myData.myFirst[t] = 0;
       }
   }

   vector( const vector &right )
      : myData()
   {
       size_type count = right.size();
       myData.myFirst = new value_type[count];
       myData.myEnd = &myData.myFirst[count];
       myData.myLast = &myData.myFirst[count];

       for (size_type t = 0; t < count; t++) {
           myData.myFirst[t] = right.myData.myFirst[t];
       }
   }

   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   void push_back( const Ty &val )
   {
      size_type originalSize = size();
      resize( originalSize + 1 );
      myData.myFirst[ originalSize ] = val;
   }

   vector& operator=( const vector &right )
   {
       if (this != &right) // avoid self-assignment
       {
           resize(right.size());
           for (size_type t = 0; t < right.size(); t++) {
               myData.myFirst[t] = right[t];
           }
       }
       return *this; // enables x = y = z, for example
   }

   void resize( const size_type newSize )
   {
       size_type originalSize = size();
       if (newSize > originalSize)
       {
           if (newSize > capacity())
           {
               size_type newCapacity = capacity() * 3 / 2;
               if (newCapacity < newSize)
                   newCapacity = newSize;

               pointer tempPtr = myData.myFirst;
               myData.myFirst = new value_type[newCapacity];
               myData.myEnd = &myData.myFirst[newCapacity];
               myData.myLast = &myData.myFirst[newSize];
               for (size_type t = 0; t < originalSize; t++) {
                   myData.myFirst[t] = tempPtr[t];
               }
               for (size_type t = originalSize; t < size(); t++) {
                   myData.myFirst[t] = 0;
               }
               delete[] tempPtr;
           }
           else
           {
               myData.myLast = &myData.myFirst[newSize];
               for (size_type t = originalSize; t < newSize; t++) {
                   myData.myFirst[t] = 0;
               }
           }
       }
       else
       {
           myData.myLast = &myData.myFirst[newSize];
       }
   }

   void pop_back()
   {
      if( size() > 0 )
         --myData.myLast;
   }

   void clear()
   {
      myData.myLast = myData.myFirst;
   }

   iterator begin()
   {
      return iterator( myData.myFirst );
   }

   iterator end()
   {
      return iterator( myData.myLast );
   }

   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   value_type& front()
   {
      return *myData.myFirst;
   }

   const value_type& front() const
   {
      return *myData.myFirst;
   }

   value_type& back()
   {
      return myData.myLast[ -1 ];
   }

   const value_type& back() const
   {
      return myData.myLast[ -1 ];
   }

private:

   ScaryVal myData;
};

// determine if two vectors are equal and return true, otherwise return false
template< typename Ty >
bool operator==( vector< Ty > &left, vector< Ty > &right )
{
    if (left.size() != right.size())
        return false; // vectors of different number of elements

    typename vector< Ty >::iterator it1 = left.begin();
    typename vector< Ty >::iterator it2 = right.begin();
    for (; it1 != left.end(); ++it1, ++it2)
        if (*it1 != *it2)
            return false; // vector contents are not equal

    return true; // vector contents are equal
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( vector< Ty > &left, vector< Ty > &right )
{
   return !( left == right );
}


// CLASS TEMPLATE ListConstIterator
template< typename MyList >
class ListConstIterator
{
public:
   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::const_pointer;
   using reference = const value_type &;

   ListConstIterator()
      : ptr()
   {
   }

   ListConstIterator( nodePtr pNode )
      : ptr( pNode )
   {
   }

   reference operator*() const
   {
      return ptr->myVal;
   }

   ListConstIterator& operator++()
   {
      ptr = ptr->next;
      return *this;
   }

   ListConstIterator operator++( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->next;
      return temp;
   }

   ListConstIterator& operator--()
   {
      ptr = ptr->prev;
      return *this;
   }

   ListConstIterator operator--( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->prev;
      return temp;
   }

   bool operator==( const ListConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListConstIterator &right ) const
   {
      return !( *this == right );
   }

   nodePtr ptr; // pointer to node
};


// CLASS TEMPLATE ListIterator
template< typename MyList >
class ListIterator
{
public:
   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::const_pointer;
   using reference = value_type &;

   ListIterator()
      : ptr()
   {
   }

   ListIterator( nodePtr pNode )
      : ptr( pNode )
   {
   }

   reference operator*() const
   {
      return ptr->myVal;
   }

   ListIterator& operator++()
   {
      ptr = ptr->next;
      return *this;
   }

   ListIterator operator++( int )
   {
      ListIterator temp = *this;
      ptr = ptr->next;
      return temp;
   }

   ListIterator& operator--()
   {
      ptr = ptr->prev;
      return *this;
   }

   ListIterator operator--( int )
   {
      ListIterator temp = *this;
      ptr = ptr->prev;
      return temp;
   }

   bool operator==( const ListIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListIterator &right ) const
   {
      return !( *this == right );
   }

   nodePtr ptr; // pointer to node
};

template< typename ValueType >
struct ListNode // list node
{
   using nodePtr = ListNode *;

   nodePtr next; // successor node, or first element if head
   nodePtr prev; // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
      mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = ListIterator< ScaryVal >;
   using const_iterator = ListConstIterator< ScaryVal >;
   using reverse_iterator = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   explicit list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      if( count > 0 )
         for( size_type i = 0; i < count; ++i )
            //            insert( cend(), Ty() );
            push_back( Ty() );
   }

   list( const list &right )
      : myData()
   {
       myData.myHead = new node;
       myData.myHead->myVal = Ty();
       myData.myHead->prev = myData.myHead->next = myData.myHead;

       *this = right;
   }

   ~list()
   {
      clear();
      delete myData.myHead;
   }

   list& operator=( const list &right )
   {
       if (this != &right)
       {
           resize(right.size());
           iterator tmp = begin();
           iterator tmp2 = right.myData.myHead->next; //this will call the constructor!
           while (tmp != end()) {
               *tmp = *tmp2;
               tmp++;
               tmp2++;
           }
       }
       return *this;
   }

   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   iterator end()
   {
      return iterator( myData.myHead );
   }

   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   void resize( size_type newSize )
   {
      if( myData.mySize < newSize ) // pad to make larger
      {
         size_type difference = newSize - myData.mySize;
         for( size_type i = 0; i < difference; i++ ) // create newSize - myData.mySize elements
            push_back( Ty() );
      }
      else
      {
         while( newSize < myData.mySize )
            pop_back();
      }
   }

   size_type size() const
   {
      return myData.mySize;
   }

   bool empty() const
   {
      return myData.mySize == 0;
   }

   reference front()
   {
      return myData.myHead->next->myVal;
   }

   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   void push_back( const Ty &val )
   {
       nodePtr tmp = myData.myHead->prev;
       myData.myHead->prev = new node;
       nodePtr newN = myData.myHead->prev;
       newN->myVal = val;

       newN->next = myData.myHead;
       newN->prev = tmp;
       tmp->next = newN;
       myData.mySize++;
   }

   void pop_back()
   {
      if( myData.mySize > 0 )
      {
          nodePtr deleting = myData.myHead->prev;
          myData.myHead->prev = deleting->prev;
          deleting->prev->next = myData.myHead;
          delete deleting;
          myData.mySize--;
      }
   }

   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
          nodePtr cur = begin().ptr->next;
          while (myData.myHead->next != myData.myHead->prev) {
              cur->prev = cur->prev->prev;
              delete begin().ptr;
              myData.myHead->next = cur;
              cur = cur->next;
          }
          myData.mySize = 0;
      }
   }

private:
   ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( list< Ty > &left, list< Ty > &right )
{
    if (left.size() != right.size()) {
        return false;
    }
    else {
        typename list<Ty>::iterator tmp = left.begin();
        typename list<Ty>::iterator tmp2 = right.begin();
        while (tmp != left.end())
        {
            if (*tmp == *tmp2) {
                tmp++;
                tmp2++;
            }
            else {
                return false;
            }

        }
    }
    return true;
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( list< Ty > &left, list< Ty > &right )
{
   return !( left == right );
}


template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;

   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   // constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const T &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   bool operator==( HugeInteger &right ); // less than or equal to

   bool operator<( HugeInteger &right );  // less than

   bool operator<=( HugeInteger &right ); // less than or equal to

   HugeInteger square( value_type powerTwo ); // the square of HugeInteger
   HugeInteger squareRoot( value_type powerTwo ); // the square root of HugeInteger

   bool isZero();           // return true if and only if all digits are zero
private:
   T integer;
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const T &integerToCopy )
   : integer( integerToCopy )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( HugeInteger &right )
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger &right )
{
    if (right.integer.size() > integer.size())
    {
        return true;
    }
    else if (right.integer.size() == integer.size())
    {
        typename T::reverse_iterator it1 = integer.rbegin();
        typename T::reverse_iterator it2 = right.integer.rbegin();
        for (; it1 != integer.rend(); it1++, it2++)
        {
            if (*it1 > *it2)
            {
                return false;
            }
            else if (*it1 < *it2)
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
} // end function operator<

// function that tests if one HugeInteger is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger &right )
{
   return ( *this == right || *this < right );
}

template< typename T >
HugeInteger< T > HugeInteger< T >::square( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_t squareSize = 2 * integer.size();
   HugeInteger square( squareSize );

   typename T::iterator it1, it2, it3;
   size_type count = 0;

   for (it1 = integer.begin(); it1 != integer.end(); it1++) {
       it3 = square.integer.begin();
       for (size_type t = 0; t < count; t++) {
           it3++;
       }
       for (it2 = integer.begin(); it2 != integer.end(); it2++, it3++) {
           *it3 += *it1 * *it2;
       }
       count++;
   }

   for (it1 = square.integer.begin(); it1 != square.integer.end(); it1++) {
       if (*it1 >= powerTwo) {
           it2 = it1;
           ++it2;
           *it2 += *it1 / powerTwo;
           *it1 %= powerTwo;
       }
   }

   typename T::reverse_iterator it = square.integer.rbegin();
   if (*it == 0) {
       square.integer.pop_back();
   }

   return square;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_type sqrtSize = ( integer.size() + 1 ) / 2;
   HugeInteger sqrt( sqrtSize );

   typename T::reverse_iterator it;

   for (it = sqrt.integer.rbegin(); it != sqrt.integer.rend(); it++) {
       value_type high = powerTwo - 1;
       value_type low = 0;
       value_type mid;

       while (low < high) {
           mid = (low + high) / 2;
           if (*it == mid) {
               (*it)++;
               break;
           }
           *it = mid;

           HugeInteger squared(sqrt.square(powerTwo));

           if (*this < squared) {
               high = mid;
           }
           else if (squared < *this) {
               low = mid;
           }
       }

       HugeInteger squared(sqrt.square(powerTwo));

       if (*this < squared) {
           (*it)--;
       }

   }

   return sqrt;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   typename T::iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::value_type numDigits = sizeof( typename T::value_type ) - 1;
   typename T::reverse_iterator it = hugeInteger.integer.rbegin();
   output << *it;
   for( ++it; it != hugeInteger.integer.rend(); ++it )
      output << setw( numDigits ) << setfill( '0' ) << *it;

   return output; // enables cout << x << y;
}

template< typename T1, typename T2 >
void solution2()
{
   char buf[ 1002 ];
   int numCases;
   cin >> numCases;
   for( int i = 1; i <= numCases; ++i )
   {
      cin >> buf;

      T2 digits[ 1001 ] = {};
      size_t last = strlen( buf ) - 1;
      for( size_t i = 0; i <= last; ++i )
         digits[ i ] = static_cast< T2 >( buf[ last - i ] ) - '0';

      T1 integer;
      T2 powerTwo;
      size_t numDigits = sizeof( T2 ) - 1;
      for( size_t i = 0; i <= last; i += numDigits )
      {
         powerTwo = 1;
         T2 bigDigit = 0;
         for( size_t j = i; j < i + numDigits; ++j, powerTwo *= 10 )
            bigDigit += digits[ j ] * powerTwo;

         integer.push_back( bigDigit );
      }

      HugeInteger< T1 > hugeInteger( integer );

      cout << hugeInteger.squareRoot( powerTwo ) << endl;

      if( i < numCases )
         cout << endl;
   }
}

template< typename T >
void solution1()
{
   int choice = 2;
   switch( choice )
   {
   case 1:
      solution2< vector< T >, T >();
      break;
   case 2:
      solution2< list< T >, T >();
      break;
   default:
      cout << "Program should never get here!";
   }

}

int main()
{
   int choice = 5;
   switch( choice )
   {
   case 1:
      solution2< vector< int >, int >();
      break;
   case 2:
      solution2< vector< unsigned int >, unsigned int >();
      break;
   case 3:
      solution1< long int >();
      break;
   case 4:
      solution1< unsigned long int >();
      break;
   case 5:
      solution1< long long int >();
      break;
   case 6:
      solution1< unsigned long long int >();
      break;
   default:
      cout << "Program should never get here!";
   }

   system( "pause" );
}
