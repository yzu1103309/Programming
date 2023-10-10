#ifndef DEQUE_H
#define DEQUE_H

#include "xutility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
   using size_type = typename MyDeque::size_type;

public:
   using value_type      = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer         = typename MyDeque::const_pointer;
   using reference       = const value_type &;

   // construct with null pointer
   DequeConstIterator()
      : myOff( 0 ),
        myCont( nullptr )
   {
   }

   // construct with offset off in *pDeque
   DequeConstIterator( size_type off, const MyDeque *pDeque )
      : myOff( off ),
        myCont( pDeque )
   {
   }

   DequeConstIterator( const DequeConstIterator &right ) // copy constructor
      : myOff( right.myOff ),
        myCont( right.myCont )
   {
   }

   ~DequeConstIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const DequeConstIterator& operator=( const DequeConstIterator &right )
   {
      if( &right != this ) // avoid self-assignment
      {
         myCont = right.myCont;
         myOff = right.myOff;
      }
      return *this; // enables x = y = z, for example
   }

   reference operator*() const
   {
//      size_type block = myOff % ( 4 * myCont->mapSize ) / 4;
      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % 4;
      return myCont->map[ block ][ off ];
   }

   pointer operator->() const
   {
      return &( operator*() );
   }

   DequeConstIterator& operator++() // preincrement
   {
      ++myOff;
      return *this;
   }

   DequeConstIterator operator++( int ) // postincrement
   {
      DequeConstIterator tmp = *this;
      ++*this;
      return tmp;
   }

   DequeConstIterator& operator--() // predecrement
   {
      --myOff;
      return *this;
   }

   DequeConstIterator operator--( int ) // postdecrement
   {
      DequeConstIterator tmp = *this;
      --*this;
      return tmp;
   }

   // increment by integer
   DequeConstIterator& operator+=( const difference_type off )
   {
      myOff += off;
      return *this;
   }

   // return this + integer
   DequeConstIterator operator+( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   // return this - integer
   DequeConstIterator operator-( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp -= off;
   }

   // return difference of iterators
   difference_type operator-( const DequeConstIterator &right ) const
   {
      return ( static_cast< difference_type >( this->myOff - right.myOff ) );
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return *( *this + off );
   }

   // test for iterator equality
   bool operator==( const DequeConstIterator &right ) const
   {
      return this->myCont == right.myCont && this->myOff == right.myOff;
   }

   // test for iterator inequality
   bool operator!=( const DequeConstIterator &right ) const
   {
      return !( *this == right );
   }

   // test if this < right
   bool operator<( const DequeConstIterator &right ) const
   {
      return this->myOff < right.myOff;
   }

   // test if this > right
   bool operator>( const DequeConstIterator &right ) const
   {
      return right < *this;
   }

   // test if this <= right
   bool operator<=( const DequeConstIterator &right ) const
   {
      return !( right < *this );
   }

   // test if this >= right
   bool operator>=( const DequeConstIterator &right ) const
   {
      return !( *this < right );
   }

   const MyDeque *myCont; // keep a pointer to deque
   size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
   using size_type = typename MyDeque::size_type;
   using MyBase = DequeConstIterator< MyDeque >;

public:
   using value_type      = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer         = typename MyDeque::pointer;
   using reference       = value_type &;

   DequeIterator() // construct with null deque pointer
   {
   }

   DequeIterator( size_type off, const MyDeque *pDeque )
      : MyBase( off, pDeque ) // construct with offset off in *pDeque
   {
   }

   reference operator*() const // return designated object
   {
      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const // return pointer to class object
   {
      return const_cast< pointer >( MyBase::operator->() );
//      return &( operator*() );
   }

   DequeIterator& operator++() // preincrement
   {
      MyBase::operator++();
      return *this;
   }

   DequeIterator operator++( int ) // postincrement
   {
      DequeIterator tmp = *this;
      MyBase::operator++();
      return tmp;
   }

   DequeIterator& operator--() // predecrement
   {
      MyBase::operator--();
      return *this;
   }

   DequeIterator operator--( int ) // postdecrement
   {
      DequeIterator tmp = *this;
      MyBase::operator--();
      return tmp;
   }

   // increment by integer
   DequeIterator& operator+=( const difference_type off )
   {
      MyBase::operator+=( off );
      return *this;
   }

   // return this + integer
   DequeIterator operator+( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeIterator& operator-=( const difference_type off )
   {
      MyBase::operator-=( off );
      return *this;
   }

   using MyBase::operator-; // return difference of iterators

   // return this - integer
   DequeIterator operator-( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp -= off;
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return const_cast< reference >( MyBase::operator[]( off ) );
   }
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference       = value_type &;
   using const_reference = const value_type &;
   using MapPtr = Ty **;

   DequeVal() // initialize values
      : map(),
        mapSize( 0 ),
        myOff( 0 ),
        mySize( 0 )
   {
   }

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return off % ( 4 * mapSize ) / 4;
//      return ( off / 4 ) & ( mapSize - 1 );
   }

   MapPtr map;        // pointer to array of pointers to blocks
   size_type mapSize; // size of map array, zero or 2^N
   size_type myOff;   // offset of initial element
   size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
   using MapPtr = Ty **;
   using ScaryVal = DequeVal< Ty >;

public:
   using value_type      = Ty;
   using size_type       = size_t;
   using difference_type = ptrdiff_t;
   using pointer         = value_type *;
   using const_pointer   = const value_type *;
   using reference       = value_type &;
   using const_reference = const value_type &;

   using iterator               = DequeIterator< ScaryVal >;
   using const_iterator         = DequeConstIterator< ScaryVal >;

   using reverse_iterator       = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   // construct empty deque
   deque()
      : myData()
   {
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   deque( size_type count )
      : myData()
   {
      resize( count );
   }

   // construct by copying right
   deque( const deque &right )
      : myData()
   {
       const_iterator it = right.begin();
       while (myData.mySize < right.size()) {
           push_back(*it);
           ++it;
       }
   }

   // destroy the deque
   ~deque()
   {
      clear();
   }

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   deque& operator=( const deque &right )
   {
      if( &right != this ) // avoid self-assignment
      {
          iterator it1 = begin();
          const_iterator it2 = right.begin();
          size_type count = 0;
          if (size() > right.size()) {
              resize(right.size());
          }
          while (count < size()) {
              *it1 = *it2;
              ++count; ++it1; ++it2;
          }
          while (count < right.size()) {
              push_back( *it2 );
              ++count; ++it2;
          }
      }

      return *this; // enables x = y = z, for example
   } // end function operator=

   // return iterator for beginning of mutable sequence
   iterator begin()
   {
      return iterator( myData.myOff, &myData );
   }

   // return iterator for beginning of nonmutable sequence
   const_iterator begin() const
   {
      return const_iterator( myData.myOff, &myData );
   }

   // return iterator for end of mutable sequence
   iterator end()
   {
      return iterator( myData.myOff + myData.mySize, &myData );
   }

   // return iterator for end of nonmutable sequence
   const_iterator end() const
   {
      return const_iterator( myData.myOff + myData.mySize, &myData );
   }

   // return iterator for beginning of reversed mutable sequence
   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   // return iterator for beginning of reversed nonmutable sequence
   const_reverse_iterator rbegin() const
   {
      return const_reverse_iterator( end() );
   }

   // return iterator for end of reversed mutable sequence
   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   // return iterator for end of reversed nonmutable sequence
   const_reverse_iterator rend() const
   {
      return const_reverse_iterator( begin() );
   }

   // return iterator for beginning of nonmutable sequence
   const_iterator cbegin() const
   {
      return begin();
   }

   // return iterator for end of nonmutable sequence
   const_iterator cend() const
   {
      return end();
   }

   // return iterator for beginning of reversed nonmutable sequence
   const_reverse_iterator crbegin() const
   {
      return rbegin();
   }

   // return iterator for end of reversed nonmutable sequence
   const_reverse_iterator crend() const
   {
      return rend();
   }

   void resize( size_type newSize )
   {
      while( myData.mySize < newSize )
         push_back( value_type() );

      while( newSize < myData.mySize )
         pop_back();
   }

   // return length of sequence
   size_type size() const
   {
      return myData.mySize;
   }

   // test if sequence is empty
   bool empty() const
   {
      return myData.mySize == 0;
   }

   const_reference operator[]( size_type pos ) const
   {
      return *( begin() + static_cast< difference_type >( pos ) );
   }

   reference operator[]( size_type pos )
   {
      return *( begin() + static_cast< difference_type >( pos ) );
   }

   reference front()
   {
      return *begin();
   }

   const_reference front() const
   {
      return *begin();
   }

   reference back()
   {
      return *( end() - 1 );
   }

   const_reference back() const
   {
      return *( end() - 1 );
   }

   // insert element at beginning
   void push_front( const value_type &val )
   {
       size_type newFront;
       if (myData.mySize == 0)
       {
           if (myData.mapSize == 0 && myData.map == nullptr) {
               myData.map = new pointer[8]();
               myData.mapSize = 8;
           }
           newFront = (myData.myOff - 1) % (4 * myData.mapSize);
       }
       else
       {
           newFront = (myData.myOff - 1) % (4 * myData.mapSize);
           if (newFront % 4 == 3 && myData.mySize >= 4 * (myData.mapSize - 1))
           {
               doubleMapSize();
               newFront = (myData.myOff - 1) % (4 * myData.mapSize);
           }
       }

       if (myData.map[getBlock(newFront)] == nullptr) {
           myData.map[getBlock(newFront)] = new value_type[4];
       }
       myData.map[getBlock(newFront)][newFront % 4] = val;
       myData.myOff = newFront;
       myData.mySize++;
   }

   // erase element at beginning
   void pop_front()
   {
      size_type front = myData.myOff % ( 4 * myData.mapSize );
      if( front % 4 == 3 )
      {
         size_type back = ( myData.myOff + myData.mySize - 1 ) % ( 4 * myData.mapSize );
         if( back >= front - 3 && back < front )
         {
            delete[] myData.map[ ( front - 3 ) / 4 ];
            myData.map[ ( front - 3 ) / 4 ] = nullptr;
         }
      }

      --myData.mySize;
      if( myData.mySize == 0 )
         myData.myOff = 0;
      else
         ++myData.myOff;
   }

   // insert element at end
   void push_back( const value_type &val )
   {
       size_type newBack;
       if (myData.mySize == 0)
       {
           if (myData.mapSize == 0) {
               myData.map = new pointer[8]();
               myData.mapSize = 8;
           }
           newBack = (myData.myOff + myData.mySize) % (4 * myData.mapSize);
       }
       else
       {
           newBack = (myData.myOff + myData.mySize) % (4 * myData.mapSize);
           if (newBack % 4 == 0 && myData.mySize >= 4 * (myData.mapSize - 1))
           {
               doubleMapSize();
               newBack = myData.myOff + myData.mySize;
           }
       }

       if (myData.map[getBlock(newBack)] == nullptr) {
           myData.map[getBlock(newBack)] = new value_type[4];
       }

       myData.map[getBlock(newBack)][newBack % 4] = val;
       myData.mySize++;
       if (myData.myOff >= 4 * myData.mapSize) {
           myData.myOff %= 4 * myData.mapSize;
       }
   }

   // erase element at end
   void pop_back()
   {
      size_type back = ( myData.myOff + myData.mySize - 1 ) % ( 4 * myData.mapSize );
      if( back % 4 == 0 )
      {
         size_type front = myData.myOff % ( 4 * myData.mapSize );
         if( front > back && front <= back + 3 )
         {
            delete[] myData.map[ back / 4 ];
            myData.map[ back / 4 ] = nullptr;
         }
      }

      --myData.mySize;
      if( myData.mySize == 0 )
         myData.myOff = 0;
   }

   // erase all
   void clear()
   {
      if( myData.mapSize > 0 )
      {
         for( size_type i = 0; i < myData.mapSize; i++ )
            if( myData.map[ i ] != nullptr )
               delete[] myData.map[ i ];
         delete[] myData.map;

         myData.mapSize = 0;
         myData.mySize = 0;
         myData.myOff = 0;
         myData.map = MapPtr();
      }
   }

private:

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return myData.getBlock( off );
//      return ( ( myData.off / 4 ) & ( myData.mapSize - 1 ) );
   }

   void doubleMapSize()
   {
       //create a double-sized map "temp"
       size_type newMapSize = myData.mapSize * 2;
       MapPtr temp = new pointer[newMapSize]();
       size_type first = getBlock(myData.myOff);
       for (size_type t = 0; t < myData.mapSize; t++) {
           temp[first + t] = myData.map[(first + t) % myData.mapSize];
       }

       //delete old map
       delete[] myData.map;

       //assign new map and new mapSize
       myData.map = temp;
       myData.mapSize = newMapSize;
   }

   ScaryVal myData;
};

#endif