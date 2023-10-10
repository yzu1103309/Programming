// xtree internal header

#ifndef XTREE
#define XTREE

template< typename Ty >
struct TreeNode
{
   using NodePtr = TreeNode *;
   using value_type = Ty;

   NodePtr    left;   // left subtree, or smallest element if head
   NodePtr    parent; // parent, or root of tree if head
   NodePtr    right;  // right subtree, or largest element if head
   char       color;  // 0: Red, 1: Black; Black if head
   char       isNil;  // 1 only if head (also nil) node
   value_type myval;  // the stored value, unused if head
};

// CLASS TEMPLATE TreeVal
template< typename Ty >
class TreeVal
{
public:
   using NodePtr = TreeNode< Ty > *;

   using value_type = Ty;
   using size_type  = size_t;

   TreeVal()
      : myHead( new TreeNode< value_type > ),
        mySize( 0 )
   {
      myHead->left = myHead;
      myHead->parent = myHead;
      myHead->right = myHead;
      myHead->color = 1;
      myHead->isNil = 1;
   }

   ~TreeVal()
   {
      clear( myHead->parent );
      delete myHead;
   }

   // Removes all elements from the set object (which are destroyed)
   void clear( TreeNode< value_type > *node )
   {
      if( !node->isNil ) // node is not an external node
      {
         clear( node->left );
         clear( node->right );
         delete node;
      }
   }

   // rebalance for insertion; u points to the inserted node
   void reBalance( TreeNode< value_type > *u )
   {  // u->parent cannot be the root
      if (u->parent->color == 1) return;

      TreeNode< value_type > *pu = u->parent;
      TreeNode< value_type > *gu = pu->parent;
      TreeNode< value_type > *uncle; // uncle of u

      if (gu->left == pu)
          uncle = gu->right;
      else
          uncle = gu->left;

      if (uncle->color == 0)
      {
          pu->color = 1;
          uncle->color = 1;
          if (gu != myHead->parent) //gu is not the root
          {
              gu->color = 0;
              reBalance(gu);
          }
      }
      else
      {
          if (gu->left == pu)
          {
              pu->color = 1;
              gu->color = 0;
              LLRotation(pu);
          }
          else
          {
              pu->color = 1;
              gu->color = 0;
              RRRotation(pu);
          }
      }
   }

   // rotate right at gu, where pu = gu->left and u = pu->left
   void LLRotation( TreeNode< value_type > *pu )
   {
      TreeNode< value_type > *gu = pu->parent;
      TreeNode< value_type >* tmp = pu->right;

      pu->right = gu;
      pu->parent = gu->parent;
      gu->parent = pu;
      gu->left = tmp;
      if (!tmp->isNil)
          tmp->parent = gu;

      if (pu->parent == myHead)
      {
          myHead->parent = pu;
      }
      else
      {
          if (pu->parent->left == gu)
              pu->parent->left = pu;
          else
              pu->parent->right = pu;
      }
   }

   // rotate left at gu, where pu = gu->right and u = pu->right
   void RRRotation( TreeNode< value_type > *pu )
   {
      TreeNode< value_type > *gu = pu->parent;
      TreeNode< value_type >* tmp = pu->left;

      pu->left = gu;
      pu->parent = gu->parent;
      gu->parent = pu;
      gu->right = tmp;
      if (!tmp->isNil)
          tmp->parent = gu;

      if (pu->parent == myHead)
      {
          myHead->parent = pu;
      }
      else
      {
          if (pu->parent->left == gu)
              pu->parent->left = pu;
          else
              pu->parent->right = pu;
      }
   }

   // erase p provided that the degree of p is at most one
   // p points to the node to be deleted
   // p == M in "Ch 10 Sec 3.pptx"
   void eraseDegreeOne( TreeNode< value_type > *p )
   {
      TreeNode< value_type > *child;
      if( p->left != myHead )
         child = p->left;
      else if( p->right != myHead )
         child = p->right;
      else
         child = myHead;

      if( p == myHead->parent ) // p points to the root; Cases 2 & 3 in "Ch 10 Sec 3.pptx"
      {
         // set child to be the new root
         myHead->parent = child;
         child->parent = myHead;
         child->color = 1;
      }
      else
      {
         TreeNode< value_type > *pp = p->parent;
         if (pp->left == p)
             pp->left = child;
         else
             pp->right = child;

         if (!child->isNil)
             child->parent = pp;

         if( p->color == 1 ) 
            if( child->color == 0 ) // Case 2 in "Ch 10 Sec 3.pptx"
               child->color = 1;
            else                   // Case 4 in "Ch 10 Sec 3.pptx"
               fixUp( child, p->parent );
      }

      if (myHead->left == p)
      {
          myHead->left = p->parent;
          while (myHead->left->left != myHead)
              myHead->left = myHead->left->left;
      }
      if (myHead->right == p)
      {
          myHead->right = p->parent;
          while (myHead->right->right != myHead)
              myHead->right = myHead->right->right;
      }

      delete p;
      mySize--;
   }

   // rebalance for deletion;  // Case 4 in "Ch 10 Sec 3.pptx"
   void fixUp( TreeNode< value_type > *N, TreeNode< value_type > *P )
   {
       TreeNode< value_type >* S;
       if (P->left == N)
           S = P->right;
       else
           S = P->left;

       if (S->right->color == 1 && S->left->color == 1)
       {
           if(!S->isNil) S->color = 0;
           P->color = 1;
       }
       else if (S->right->color == 0)
       {
           S->color = P->color;
           P->color = 1;
           S->right->color = 1;
           RRRotation(S);
       }
       else if (S->left->color == 0)
       {
           S->color = P->color;
           P->color = 1;
           S->left->color = 1;
           LLRotation(S);
       }
   }

   NodePtr myHead;   // pointer to head node
   size_type mySize; // number of elements
};

// CLASS TEMPLATE Tree
template< typename Traits >
class Tree // ordered red-black tree for map/multimap/set/multiset
{
public:
   using value_type = typename Traits::value_type;

protected:
   using ScaryVal = TreeVal< value_type >;

public:
   using key_type      = typename Traits::key_type;
   using key_compare   = typename Traits::key_compare;

   using size_type       = size_t;

   Tree( const key_compare &parg )
      : keyCompare( parg ),
        scaryVal()
   {
   }

   ~Tree()
   {
   }

   // Extends the container by inserting a new element,
   // effectively increasing the container size by one.
   void insert( const value_type &val )
   {
      if( scaryVal.mySize == 0 )
      {
         TreeNode< value_type > *root = new TreeNode< value_type >;
         root->myval = val;
         root->left = scaryVal.myHead;
         root->right = scaryVal.myHead;
         root->isNil = 0;
         root->parent = scaryVal.myHead;
         root->color = 1;
         scaryVal.myHead->left = root;
         scaryVal.myHead->parent = root;
         scaryVal.myHead->right = root;
         scaryVal.mySize = 1;
      }
      else
      {                           // scaryVal.myHead->parent points to the root
         TreeNode< value_type > *p = scaryVal.myHead->parent; // p points to the root
         TreeNode< value_type > *pp = nullptr;
         while( p != scaryVal.myHead )
         {
            pp = p;
            if( keyCompare( val, p->myval ) ) // if( val < p->myval )
               p = p->left;
            else if( keyCompare( p->myval, val ) ) // if( val > p->myval )
               p = p->right;
            else
               return; //already exist
         }

         TreeNode< value_type >* newNode = new TreeNode< value_type >;
         newNode->color = 0;
         newNode->isNil = 0;
         newNode->left = scaryVal.myHead;
         newNode->right = scaryVal.myHead;
         newNode->myval = val;
         newNode->parent = pp;

         if (keyCompare(val, pp->myval)) // if( val < p->myval )
             pp->left = newNode;
         else // if( val > p->myval )
             pp->right = newNode;

         ++scaryVal.mySize;

         if( pp->color == 0 ) // pp cannot be the root
            scaryVal.reBalance( newNode );

         if (keyCompare(val, scaryVal.myHead->left->myval))
             scaryVal.myHead->left = newNode;
         if (keyCompare(scaryVal.myHead->right->myval, val))
             scaryVal.myHead->right = newNode;
      }
   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val )
   {
      TreeNode< key_type > *p = scaryVal.myHead->parent; // p points to the root
      while( p != scaryVal.myHead && val != p->myval )
      {
         if( keyCompare( val, p->myval ) ) // if( val < p->myval )
            p = p->left;
         else
            p = p->right;
      }

      if( p == scaryVal.myHead ) // not found
         return 0;
      else // found
      {  // deletes the node pointed by p
          TreeNode< value_type >* rSub = p->right;

          if (rSub != scaryVal.myHead)
          {
              while (rSub->left != scaryVal.myHead)
              {
                  rSub = rSub->left;
              }
          }
          else
          {
              rSub = p;
          }
          
          p->myval = rSub->myval;
          scaryVal.eraseDegreeOne(rSub);

         return 1;
      }
   }

private:
   key_compare keyCompare;
   ScaryVal scaryVal;
};

#endif // XTREE