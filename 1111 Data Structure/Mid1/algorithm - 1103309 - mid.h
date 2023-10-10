// algorithm standard header

#ifndef ALGORITHM
#define ALGORITHM

namespace MyNamespace
{
   template< typename RanIt, typename Ty, typename Pr >
   inline void pushHeapByIndex( RanIt first, ptrdiff_t hole, ptrdiff_t top, Ty &val, Pr pred )
   {
       ptrdiff_t idx;
       while (hole != top)
       {
           idx = (hole - 1) / 2;
           if (pred(first[idx], val))
           {
               first[hole] = first[idx];
               hole = idx;
           }
           else
               break; 
       }
       first[hole] = val;
   }

   // push *(last - 1) onto heap at [first, last - 1), using pred
   template< typename RanIt, typename Pr >
   inline void push_heap( RanIt first, RanIt last, Pr pred )
   {
      ptrdiff_t count = last - first;
      if( count >= 2 )
      {
         --last;
         typename RanIt::value_type val = *last;
         --count;
         pushHeapByIndex( first, count, 0, val, pred );
      }
   }
}

#endif // ALGORITHM