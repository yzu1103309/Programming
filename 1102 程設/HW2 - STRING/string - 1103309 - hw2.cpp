#include <iostream>
using std::cout;
using std::exit;

#include "string.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = count;
   myRes = ( mySize / 16 ) * 16 + 15;

   if (myRes < 16) {
       for (size_type t = 0; t < count; t++) {
           myPtr()[t] = ptr[t];
       }
   }
   else {
       bx.ptr = new value_type[myRes + 1];
       for (size_type t = 0; t < count; t++) {
           myPtr()[t] = ptr[t];
       }
   }
}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   // construct from count * ch
   mySize = count;
   if( count > 15 )
   {
      myRes = ( mySize / 16 ) * 16 + 15;
      bx.ptr = new value_type[myRes + 1];
      for (size_type t = 0; t < count; t++) {
          myPtr()[t] = ch;
      }
   }
   else {
       for (size_type t = 0; t < count; t++) {
           myPtr()[t] = ch;
       }
   }
}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = right.mySize;
   myRes = ( mySize / 16 ) * 16 + 15;
   if (myRes < 16) {
       for (size_type t = 0; t < mySize; t++) {
           myPtr()[t] = right.myPtr()[t];
       }
   }
   else {
       bx.ptr = new value_type[myRes + 1];
       for (size_type t = 0; t < mySize; t++) {
           myPtr()[t] = right.myPtr()[t];
       }
   }
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

string& string::assign( const string &right )
{
   if( this != &right )
   {
          resize(right.mySize);
          for (size_t t = 0; t < right.mySize; t++) {
              myPtr()[t] = right.myPtr()[t];
          }
   }
   return *this;
}

bool string::equal( const string &right )
{
    if (mySize != right.mySize) {
        return false;
    }
    if (myRes != right.myRes) {
        return false;
    }
    for (size_type t = 0; t < mySize; t++) {
        if (myPtr()[t] != right.myPtr()[t]) {
            return false;
        }
    }
    return true;
}

string& string::erase( const size_type off, size_type count )
{
   if( off < mySize )
   {
       if (count != 0) {
           size_type add = 0;
           size_type decrease = 0;
           for (size_type t = off + count; t < mySize; t++) {
               myPtr()[t - count] = myPtr()[t];
               add++;
           }
           for (size_type t = off + add; t < mySize; t++) {
               myPtr()[t] = char();
               decrease++;
           }

           mySize = mySize - decrease;
       }
   }
   return *this;
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return myPtr();
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

string::iterator string::end()
{
   return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::at( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::const_reference string::at( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

void string::push_back( char ch )
{
   resize( mySize + 1 );
   myPtr()[ mySize - 1 ] = ch;
}

void string::pop_back()
{
   if( mySize > 0 )
      --mySize;
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

void string::resize( const size_type newSize, const char ch )
{
   // determine new length, padding with ch elements as needed
   if( newSize > mySize )
   {
      if( newSize > myRes ) //Res Not enough
      {
         size_type newMyRes = myRes * 3 / 2;
         if( newMyRes < ( newSize / 16 ) * 16 + 15 )
            newMyRes = ( newSize / 16 ) * 16 + 15;

         pointer temp = new value_type[newMyRes + 1];
         
         for (size_type t = 0; t < mySize; t++) {
             temp[t] = myPtr()[t];
         }
         myRes = newMyRes;
         bx.ptr = temp;
         for (size_type t = mySize; t < newSize; t++) {
             bx.ptr[t] = ch;
         }
         bx.ptr[newSize] = char();
      }
      else {
          for (size_type t = mySize; t < newSize; t++) {
              myPtr()[t] = ch;
          }
          myPtr()[newSize] = char();
      }
   }
   else {
       myPtr()[newSize] = char();
   }
   mySize = newSize;
}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}