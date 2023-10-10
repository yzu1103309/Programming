#include "./deque - 1103309 - Mid 2-2.h"

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

// Represents a term of a polynomial
struct Term
{
   int expon;
   int coef;
};

// Polynomial class template definition
template< typename T >
class Polynomial : public deque< T >
{
public:
   Polynomial(); // Default constructor; Constructs an empty polynomial, with no terms.

   // Copy constructor; Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
   Polynomial( const Polynomial &polynomialToCopy );

   ~Polynomial(); // Destructor with empty body

   void insert( Term termToInsert ); // Inserts a new term into the polynomial

   Polynomial operator*( Polynomial &multiplier ); // Returns the product of two polynomials

}; // end class template Polynomial

#endif


// Default constructor; Constructs an empty polynomial, with no terms.
template< typename T >
Polynomial< T >::Polynomial()
   : deque< T >()
{
}

// Copy constructor; Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
template< typename T >
Polynomial< T >::Polynomial( const Polynomial &polynomialToCopy )
   : deque< T >( polynomialToCopy )
{
}

// Destructor with empty body
template< typename T >
Polynomial< T >::~Polynomial()
{
}

// Inserts a new term into the polynomial
template< typename T >
void Polynomial< T >::insert( Term termToInsert )
{
   if( this->empty() )
      deque< T >::insert( this->begin(), termToInsert );
   else
   {
      for (typename deque< T >::iterator it = deque< T >::begin(); ; ++it) //added
        if (it->expon == termToInsert.expon) { it->coef += termToInsert.coef; if (it->coef == 0) this->erase(it); break; } //added
        else if( it->expon < termToInsert.expon ){ deque< T >::insert(it, termToInsert); break; } //added
        else if ((it + 1) == deque< T >::end()){ deque< T >::insert(it+1, termToInsert); break; } //added
   }
}

// Returns the product of two polynomials
template< typename T >
Polynomial< T > Polynomial< T >::operator*( Polynomial< T > &multiplier )
{
   Polynomial< T > product;
   Term newTerm;

   typename deque< T >::iterator it1;
   typename deque< T >::iterator it2;
   if( !this->empty() && !multiplier.empty() )
      for( it1 = this->begin(); it1 != this->end(); ++it1 )
         for( it2 = multiplier.begin(); it2 != multiplier.end(); ++it2 )
         {
            newTerm.coef = it1->coef * it2->coef;
            newTerm.expon = it1->expon + it2->expon;
            product.insert( newTerm );
         }

   return product;
}

// Overloaded stream insertion operator
template< typename T >
ostream& operator<<( ostream &output, const Polynomial< T > polynomial )
{
   if( polynomial.empty() ) // zero polynomial
   {
      output << 0;
      return output;
   }

   typename deque< T >::const_iterator it = polynomial.begin();
   for( ; it != polynomial.end(); ++it )
      output << it->coef << " " << it->expon << " ";

   return output; // enables cout << x << y;
} // end function operator<<
