#ifndef TREE_H__
#define TREE_H__

#include <iomanip>
#include <list>
#include <iostream>
#include <cmath>
#include <functional> //less<T> <-> operator<
//you can #include <queue> and #include <stack> but no other STL

using std::setw;
using std::list;
using std::cout;
using std::endl;
using std::less;
            //function object used for comparison, default value is less
template <typename Comparable, typename Comparator=less<Comparable> >
class Tree
{
public:
  
  Tree( );  //construct an empty tree
  Tree( const list<Comparable> & ); //construct complete BST with min height based on list vals
  ~Tree( ); //release all dynamically allocated memory
  
  void construct( const list<Comparable> & ); //release own sources and get values from list

  const Comparable * findMin( ) const; //pointer to element that is minimal wrt Comparator, implemented
  const Comparable * findMax( ) const; //pointer to element that is maximal wrt Comparator, implemented

  const Comparable * getAddress( const Comparable & ) const; //find pointer to element with given values

  bool contains( const Comparable * ) const; //does this element with data exists in tree, implemented
  bool isEmpty( ) const; //is the tree empty, implemented
    
  void insert( const Comparable * ); //insert if dereferenced argument's data is not present, update heights of those affected
  void remove( const Comparable * ); //delete if dereferenced argument's data is present, update heights of those affected
  /* DO NOT FORGET TO CHECK BALANCE AND REBALANCE TREE IF NOT BALANCED AFTER INSERTION AND DELETION */

  size_t getSize( ) const; //accessor to size, implemented
  int getHeight( ) const; //accessor  to height, implemented
  bool isBalanced( ) const; //accessor to balanced, implemented

  void print( ) const; //inorder print of dereferenced pointers held in nodes, implemented

  friend class MusicList; //MusicList class can access private parts of Tree

private:
  struct TreeNode  //scope Tree::TreeNode, thus is only public to Tree structure, no non-friend outsiders can see
  {	 	  	  	   	     	  	        	 	
    const Comparable * element; //adress of the item
    TreeNode * left; //pointer to the root of left subtree
    TreeNode * right; //pointer to the root of right subtree
    TreeNode * parent; //pointer to parent node, pay attention to this!
    size_t height; //height >= 0

    //constructor
    TreeNode( const Comparable * el,
              TreeNode * l, TreeNode * r, 
              TreeNode * p )
      : element( el ), 
        left( l ), right( r ),
        parent( p )
    {
    }
    //you should separately set height values, no constructor is defined for them
  } ;

  TreeNode * root; //designated root
 
  /* isLessThan( const Comparable & lhs, const Comparable & rhs )
   * returns true if lhs<rhs and false otherwise */
  Comparator isLessThan;
  
  size_t size; //number of nodes
  bool balanced;

  /* uncopiable */
  Tree( const Tree & ); //disabled, provide no implementation
  Tree & operator=( const Tree & ); //disabled, provide no implementation

  /* private utility functions */
  TreeNode * findMin( TreeNode * ) const; //recursively find min in (leftward) subtrees
  TreeNode * findMax( TreeNode * ) const; //recursively find max in (rightward) subtrees
  bool contains( const Comparable *, TreeNode * ) const; //recursively search for an item
  
  bool isLeaf( TreeNode * ) const; //isLeaf
  bool isFull( TreeNode * ) const; //isFull
  void print( TreeNode * ) const; //recursive print

  //define and use more as you may need
void  helper_removeToList(TreeNode* root,const Comparable* data,list<Comparable*> & liste);
void helper_insert(TreeNode* root,const Comparable* data);
void helper_treeToList(TreeNode *root, list<Comparable*>& liste)const;
void helper_destructor(TreeNode* root);
int helper_getHeight(TreeNode* root, int h);
const Comparable * helper_getAddress(TreeNode *root, const Comparable & item )const;
list <Comparable> * helper_slice(list <Comparable> & liste, int begin, int end);
void helper_constructor(TreeNode *root, const list<Comparable>& liste,int begin, int end);
const Comparable* helper_getPtrAt(const list<Comparable>& liste, int index);
const Comparable* helper_getElementAt(const list<Comparable*>& liste, int index);
void helper_postorder(TreeNode* p, int indent=0)const;
void helper_printList(const list<Comparable*>& liste);
void helper_inorderPrint(TreeNode* p)const;
void musiclistprint()const;
void helper_remove(TreeNode* root, const Comparable* data);
int helper_heightAssigner(TreeNode *root,int level);
int helper_powerOfTwo(int n);
void helper_reconstructor(TreeNode *root, const list<Comparable*>& liste,int begin, int end);
int helper_perfectMid(int end);
void pretty_print()const;


  template <typename T>  //templated max
  T max( T x, T y ) { return x > y ? x : y; }	 	  	  	   	     	  	        	 	
}; //Do not modify method prototypes and data member names


template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::
helper_postorder(TreeNode* p, int indent)const
{
    if(p != NULL) {
        if(p->right) {
            helper_postorder(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<<*( p->element) << " |"<<p->height<<"\n ";
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            helper_postorder(p->left, indent+4);
        }
    }
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::
pretty_print()const{
  helper_postorder(root);
}
template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::
musiclistprint()const{
  //cout << "INSIDE MUSICLISTPRINT"<<endl;
  helper_inorderPrint(root);
}	 	  	  	   	     	  	        	 	
template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::
helper_inorderPrint(TreeNode* p)const{
  //cout << "INSIDE INORDERPRINT"<<endl;
  //cout << "ROOT= "<<root <<endl;

  if(p!=NULL){
    //cout << "inside if"<<endl;
    if(p->left){ helper_inorderPrint(p->left); }
      cout << *(p->element) << endl;
      if(p->right){helper_inorderPrint(p->right); }
  }
}

template <typename Comparable, typename Comparator>
int Tree<Comparable,Comparator>::
helper_heightAssigner(TreeNode *root,int level){
    
    if(root==NULL) { return -1; }
    root->height=1+max( helper_heightAssigner(root->left,level), helper_heightAssigner(root->right,level));
    return root->height;

}










//Below this point you should begin implementing the missing parts
template <typename Comparable, typename Comparator>
Tree<Comparable,Comparator>::
Tree( ){	 	  	  	   	     	  	        	 	
    root = NULL;
    size = 0;
    balanced=true;
}
//Complete the body of the constructor

template <typename Comparable, typename Comparator>
Tree<Comparable,Comparator>::
Tree( const list<Comparable> & data ){
    if(data.size()!=0){
      root= new TreeNode(NULL,NULL,NULL,NULL);
      construct(data);
    }
    else{
      root=NULL;
      size=0;
      balanced;
    }

}
//Complete the body of the constructor

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::
construct( const list<Comparable> & data )
{
  helper_destructor(root);
  root= new TreeNode(NULL,NULL,NULL,NULL);
  helper_constructor(root,data,0,data.size() -1 );
  
  helper_heightAssigner(root,0);
  
  size=data.size();
  balanced=true;
}	 	  	  	   	     	  	        	 	



template <typename Comparable, typename Comparator>
Tree<Comparable,Comparator>::~Tree( ){
 // cout << "Starting ~tree" << endl;
 // helper_destructor(root);
  //cout << "ending ~tree" << endl;
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::
insert( const Comparable * data )
{  
     if(root==NULL){
      root = new TreeNode(data,NULL,NULL,NULL);
      root->height=0;
      size=1;
      balanced=true;
      return;
     }
     //insert into the tree
    helper_insert(root,data);
    //check if balanced
    
    helper_heightAssigner(root,0);
    

    if(root->height>=2*floor( log2(getSize()) ) and getSize()>1){ 
        //RECONTRUCT
      //cout << "Reconstrcting" << endl;
        list<Comparable*> liste;
        helper_treeToList(root,liste);
      //  cout << "finished tree to list" <<endl;
     //   cout << "list= "<< endl;
      //  helper_printList(liste);
        helper_destructor(root);
      //  cout << "finished destructor" << endl;
        root= new TreeNode(NULL,NULL,NULL,NULL);
        helper_reconstructor(root,liste,0,liste.size()-1);

        helper_heightAssigner(root,0);
        
      }	 	  	  	   	     	  	        	 	
    balanced=true;
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::
remove( const Comparable * data )
{
    if(root==NULL){return;}
    helper_remove(root,data);
    helper_heightAssigner(root,0);
    
    if(root==NULL){return;}
    if(root->height>=2*floor( log2(getSize()) ) and getSize()>1){
        //cout <<"About to RECONSTRUCT"<<endl;
        list<Comparable*> liste;
        helper_removeToList(root, data,liste);
        //cout << "FINISHED remove to list" << endl;
        
        helper_destructor(root);
        root= new TreeNode(NULL,NULL,NULL,NULL);
        helper_reconstructor(root,liste,0,size-1);
        
        
        
    }
    helper_heightAssigner(root,0);
    
    balanced=true;
}

template <typename Comparable, typename Comparator>
const Comparable *
Tree<Comparable,Comparator>::
getAddress( const Comparable & item ) const
{	 	  	  	   	     	  	        	 	
  return helper_getAddress(root,item);
}









template <typename Comparable, typename Comparator>
void  Tree<Comparable,Comparator>::
helper_remove(TreeNode* root, const Comparable* data){
    if(root==NULL){return;}
    if(isLessThan(*data,*(root->element))){ helper_remove(root->left,data); }
    else if(isLessThan(*(root->element),*data)){ helper_remove(root->right,data); }
    else if(root->left!=NULL and root->right!=NULL){ //two children
         
        root->element= findMin( root->right)->element;    
        helper_remove(root->right,root->element);
        
    
      }
    else{
        
        if(root->left==NULL and root->right==NULL){ //leaf
          //cout <<"IN LEAF"<<endl;
          if(root==this->root) {delete root; this->root=NULL;size--;return;}
          //cout << "NOT ROOT"<<endl;
          root->element=NULL;
          if(root->parent->left==root){root->parent->left=NULL;}
          else if(root->parent->right==root){root->parent->right=NULL;}
          root->parent=NULL;
          delete root;
          size--;
        }	 	  	  	   	     	  	        	 	
        else{ //has one children
         
          
          TreeNode* child = root->left==NULL ? root->right : root->left;
          if(root->parent!=NULL){
              if(root->parent->left==root){root->parent->left=child;}
              else if(root->parent->right==root){root->parent->right=child;}
              child->parent=root->parent;
              delete root;
              size--;
          }
          else{
            TreeNode* oldNode=this->root;
           this->root=child;
            delete oldNode;
            this->root->parent=NULL;
            size--;
          }
        
        }
    }
    
}

template <typename Comparable, typename Comparator>
void  Tree<Comparable,Comparator>::
helper_removeToList(TreeNode* root,const Comparable* data, list<Comparable*> & liste){
    if(root==NULL){ return; }
    if(root->left!=NULL){
      helper_removeToList(root->left,data,liste);
    }
    if( isLessThan(*(root->element),*data) or  isLessThan(*data,*(root->element))   ){
       liste.push_back( const_cast<Comparable*> (root->element) ); 
    }
    else{ size--; }
    if(root->right!=NULL){	 	  	  	   	     	  	        	 	
      helper_removeToList(root->right,data,liste);
    }
    
  

}

template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::
helper_insert(TreeNode* root,const Comparable* data){
  
  if(isLessThan(*(root->element),*data)){
    if(root->right==NULL){
      root->right= new TreeNode(data,NULL,NULL,root);
      size++;
      return;
    }
    helper_insert(root->right,data);
  }
  else if(isLessThan(*data,*(root->element))){
    if(root->left==NULL){
      root->left=new TreeNode(data,NULL,NULL,root);
      size++;
      return;
    }
    helper_insert(root->left,data);
  }
  else{ //duplicate
    return;
  }
}
template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::
helper_treeToList(TreeNode *root, list<Comparable*>& liste)const{
    
    if(root==NULL){ return;}	 	  	  	   	     	  	        	 	
    if(root->left!=NULL){
      helper_treeToList(root->left,liste);
    }
    liste.push_back( const_cast<Comparable*> (root->element) );
    if(root->right!=NULL){
      helper_treeToList(root->right,liste);
    }
    
    
}


template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::
helper_destructor(TreeNode* root){
  
  if(root==NULL){return;}
  if(root->parent!=NULL){
      delete root->parent;
  }
  if(root->left==NULL&&root->right==NULL){delete root;}
  else if(root->left!=NULL){ helper_destructor(root->left);}
  else if(root->right!=NULL){helper_destructor(root->right);}
  
}

template <typename Comparable, typename Comparator>
int Tree<Comparable,Comparator>::
helper_getHeight(TreeNode* root, int h){
  if(root==NULL){return h-1;}
  return 1+max(helper_getHeight(root->left,0), helper_getHeight(root->right,0));
}

template <typename Comparable, typename Comparator>
const Comparable * 
Tree<Comparable,Comparator>::
helper_getAddress(TreeNode *root, const Comparable & item )const{	 	  	  	   	     	  	        	 	
  if(root==NULL){return NULL;}
  if(isLessThan(*(root->element),item)){
    if(root->right==NULL){return NULL; }
    return helper_getAddress(root->right,item);
  }
  else if(isLessThan(item,*(root->element))){
    if(root->left==NULL){return NULL;}
    return helper_getAddress(root->left,item);
  }
  else{ //FOUND IT
    return root->element;
  }
}

template <typename Comparable, typename Comparator>
list <Comparable> * 
Tree<Comparable,Comparator>::
helper_slice(list <Comparable> & liste, int begin, int end){
  
  typename std::list<Comparable>::const_iterator it = liste.begin();
  list<Comparable> * retval = new list<Comparable>;
  for(int i =0;i!=begin;i++){
    it++;
  }
  for(int i=begin;i<=end;i++){
    retval->pushback(*it);
    if(i!=end){it++; }
  }
}
template <typename Comparable, typename Comparator>
int Tree<Comparable,Comparator>::
helper_powerOfTwo(int n){
  int retval=0;
  while(n>pow(2,retval)){
    retval++;
  }	 	  	  	   	     	  	        	 	
  return retval-1;

}


template <typename Comparable, typename Comparator>
int Tree<Comparable,Comparator>::
helper_perfectMid(int n){
    int x = 1;

    
     //find a power of 2 <= n/2
     while(x <= n/2){ // this loop could probably be written more elegantly :)
        x *= 2;
      }
    
    // x = 1 << (n.bit_length() - 1)   # indeed you can

    if (x/2 - 1 <= (n-x)){
        return x - 1;      // case 1
      }
    else{
        return n - x/2;   // case 2 == n - (x//2 - 1) - 1
      }
}

template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::
helper_reconstructor(TreeNode *root, const list<Comparable*>& liste,int begin, int end){
    
    if(liste.size()==0){
        root=NULL;
    }
    if(end==begin){
        //cout << "ZERO DIFF" << endl;
        root->element=helper_getElementAt(liste,end);
    }	 	  	  	   	     	  	        	 	
    else{
      
    }
    if(end-begin==1){
      //cout << "ONE DIFF"<<endl;
      root->left = new TreeNode(NULL,NULL,NULL,root);
      root->element=helper_getElementAt(liste,end);
      root->left->element=helper_getElementAt(liste,begin);
    }

    if(end-begin==2){
      //cout << "TWO DIFF"<<endl;
      root->left = new TreeNode(NULL,NULL,NULL,root);
      root->right = new TreeNode(NULL,NULL,NULL,root);
      root->element=helper_getElementAt(liste,begin+1);
      root->left->element=helper_getElementAt(liste,begin); 
      root->right->element=helper_getElementAt(liste,end);
    }
    if(end-begin>2){
        /*int bom;
        int power=helper_powerOfTwo(end-begin+1);
        //cout << "AA= "<< power << endl;
        
        bom=begin+pow(2,power)-1;
        //cout << "BB= "<<bom<<endl;
        */
        /*if((end-begin+1)%2!=0){
          if(helper_powerOfTwo()){ bom=(end+begin)/2+1; }
        }
        else {
          bom=((end+begin)/2)+1;
        }
        */
        int bom=begin+helper_perfectMid(end-begin+1);
        
        root->element = helper_getElementAt(liste,bom);
        root->left = new TreeNode(NULL,NULL,NULL,root);
        root->right = new TreeNode(NULL,NULL,NULL,root);
        helper_reconstructor(root->left, liste,begin,bom-1 );
        helper_reconstructor(root->right, liste,bom+1,end);
    }	 	  	  	   	     	  	        	 	

}


template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::
helper_constructor(TreeNode *root, const list<Comparable>& liste,int begin, int end){
    
    if(liste.size()==0){
        root=NULL;
    }
    if(end==begin){
        root->element=helper_getPtrAt(liste,end);
    }
    else{
      
    }
    if(end-begin==1){
      root->left = new TreeNode(NULL,NULL,NULL,root);
      root->element=helper_getPtrAt(liste,end);
      root->left->element=helper_getPtrAt(liste,begin);
    }

    if(end-begin==2){
      root->left = new TreeNode(NULL,NULL,NULL,root);
      root->right = new TreeNode(NULL,NULL,NULL,root);
      root->element=helper_getPtrAt(liste,begin+1);
      root->left->element=helper_getPtrAt(liste,begin); 
      root->right->element=helper_getPtrAt(liste,end);
    }
    if(end-begin>2){
        int bom;
        
        bom=begin+helper_perfectMid(end-begin+1);

        root->element = helper_getPtrAt(liste,bom);
        root->left = new TreeNode(NULL,NULL,NULL,root);
        root->right = new TreeNode(NULL,NULL,NULL,root);
        helper_constructor(root->left, liste,begin,bom-1 );
        helper_constructor(root->right, liste,bom+1,end);
    }	 	  	  	   	     	  	        	 	

}

template <typename Comparable, typename Comparator>
const Comparable* Tree<Comparable,Comparator>::
helper_getPtrAt(const list<Comparable>& liste, int index){
  typename std::list<Comparable>::const_iterator it = liste.begin();
  for(int i=0;i!=index;i++){
    it++;
  }
  return &(*it);
}

template <typename Comparable, typename Comparator>
const Comparable* Tree<Comparable,Comparator>::
helper_getElementAt(const list<Comparable*>& liste, int index){
  typename std::list<Comparable*>::const_iterator it = liste.begin();
  for(int i=0;i!=index;i++){
    it++;
  }
  return *it;
}

template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::
helper_printList(const list<Comparable*>& liste){
  typename std::list<Comparable*>::const_iterator it = liste.begin();
  for(int i=0;i!=liste.size();i++){
    Comparable* ptr=*it;
    cout << *ptr<< "->";
    it++;
  }
  cout << endl;
}













template <typename Comparable, typename Comparator>
const Comparable *
Tree<Comparable,Comparator>::findMin( ) const
{	 	  	  	   	     	  	        	 	
  if( isEmpty( ) )
    return NULL;
  
  return findMin( root )->element; //call in to recursive utility function
}
template <typename Comparable, typename Comparator>
const Comparable *
Tree<Comparable,Comparator>::findMax( ) const
{
  if( isEmpty( ) )
    return NULL;
  
  return findMax( root )->element;
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::contains( const Comparable * item ) const
{  
  return contains( item, root );
}

template <typename Comparable, typename Comparator>
size_t
Tree<Comparable,Comparator>::getSize( ) const
{
  return size;
}

template <typename Comparable, typename Comparator>
int
Tree<Comparable,Comparator>::getHeight( ) const
{
  if( isEmpty( ) )
    return -1;  //convention: empty tree has height -1
  else
    return root->height; //>= 0
}	 	  	  	   	     	  	        	 	

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::isEmpty( ) const
{
  return ( root == NULL );
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::print( ) const
{
  print( root );
  cout << endl;  
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::isBalanced( ) const
{
  return balanced;
}

/* private utility functions 
 * define and use as many as you deem required
 * some are provided for the already implemented 
 * part of the public interface
 */
template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode *
Tree<Comparable,Comparator>::findMin( TreeNode * t ) const
{
  if( t == NULL )
    return NULL;

  if( t->left == NULL )
    return t;

  return findMin( t->left );
}	 	  	  	   	     	  	        	 	

template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode *
Tree<Comparable,Comparator>::findMax( TreeNode * t ) const
{
  if( t != NULL )
    while( t->right != NULL )
      t = t->right;
  return t;
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::contains( const Comparable * item, 
                                           TreeNode * t ) const
{
  if( t == NULL )
    return false;
  else if( isLessThan( *item, *(t->element) ) )
    return contains( item, t->left );
  else if( isLessThan( *(t->element), *item ) )
    return contains( item, t->right );
  else
    return true;
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::isLeaf( TreeNode * t ) const
{
  return ( ( t->left == NULL ) && ( t->right == NULL ) );
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::isFull( TreeNode * t ) const
{	 	  	  	   	     	  	        	 	
  return ( ( t->left != NULL ) && ( t->right != NULL ) );
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::print( TreeNode * t ) const
{
  if( t && t->left != NULL )
  {
    cout << '[';
    print( t->left );
  }
  else if( t&&t->left == NULL && t->right != NULL )
  {
    cout << "[";
  }

  if( t != NULL )
  {
    if( isLeaf( t ) )
    {
      cout << '(' << *( t->element ) << ')';
    }
    else if( !isLeaf( t ) )
    {
      cout << *( t->element );
    }
  }

  if(t&& t->right != NULL )
  {
    print( t->right );
    cout << ']';
  }
  else if( t&&t->left != NULL && t->right == NULL )
  {	 	  	  	   	     	  	        	 	
    cout << "]";
  }
}

#endif

