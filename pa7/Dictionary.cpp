//-----------------------------------------------------------------------------
// Dictionary.cpp
// Header file for Dictionary ADT based on a Binary Search Tree. Includes a
// built in iterator called current that can perform a smallest-to-largest
// (forward) or a largest-to-smallest (reverse) iteration over all keys.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
//#include<climits>
#include<stdexcept>
#include"Dictionary.h"

   const std::string null = "";
   // private Node struct
   Dictionary::Node::Node(keyType k, valType v){
      // Node fields
      key = k;
      val = v;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
   }

   // Dictionary fields
   Dictionary::Dictionary(){
      nil = new Node(null, -69);
      nil->parent = nil;
      nil->left = nil;
      nil->right = nil;
      root = nil;
      root->right = nil;
      root->left = nil;
      current = nil;
      current->parent = nil;
      current->left = nil;
      current->right = nil;
      num_pairs = 0;
   }

   Dictionary::Dictionary(const Dictionary& D){
      nil = new Node(null, -69);
      nil->parent = nil;
      nil->left = nil;
      nil->right = nil;
      root = nil;
      root->right = nil;
      root->left = nil;
      current = nil;
      current->parent = nil;
      current->left = nil;
      current->right = nil;
      num_pairs = 0;
      preOrderCopy(D.root, D.nil);
   }

   Dictionary::~Dictionary(){
      clear();
      num_pairs = 0;
      current = nil;

   }

   // Helper Functions (Optional) ---------------------------------------------

   void Dictionary::transplant(Node* N, Node* M){
      if(N->parent == nil){
         root = M;
      }
      else if(N == N->parent->left){
         N->parent->left = M;
      }
      else{
         N->parent->right = M;
      }
      if(M != nil){
         M->parent = N->parent;
      }
   }
   /*
   void Dictionary::preOrderVal(std::string& s, Node* R) const{
      if(R != nil){
         s += std::to_string(R->val);
         preOrderVal(s, R->left);
         preOrderVal(s, R->right);
      }
   }
   */
   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
   void Dictionary::inOrderString(std::string& s, Node* R) const{
      if(R != nil){
         inOrderString(s, R->left);
         s += R->key;
         s += " : ";
         s += std::to_string(R->val);
         s += "\n";
         inOrderString(s, R->right);
      }
   }

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order determined
   // by a pre-order tree walk.
   void Dictionary::preOrderString(std::string& s, Node* R) const{
      if(R != nil){
         s += R->key;
         preOrderString(s, R->left);
         preOrderString(s, R->right);
      }
   }


   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
   // R is not in this
   void Dictionary::preOrderCopy(Node* R, Node* N){
      
      if(R != nil && R != N){
         setValue(R->key, R->val);
         preOrderCopy(R->left, N);
         preOrderCopy(R->right, N);
      }
   }

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R, sets R to nil.
   void Dictionary::postOrderDelete(Node* R){
      if(R != nil){
         postOrderDelete(R->left);
         postOrderDelete(R->left);
         delete R;
         num_pairs --;
      }
   }

   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
   Dictionary::Node* Dictionary::search(Dictionary::Node* R, keyType k) const{
      if(R == nil || k == R->key){
         return R;
      }
      else if(k < R->key){
         return search(R->left, k);
      }
      else{
         return search(R->right, k);
      }
   }

   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMin(Dictionary::Node* R){
      if(R == nil){
         throw std::invalid_argument("Dictionary: findMin(): nil Node argument\n");
      }
      while(R->left != nil){
         R = R->left;
      }
      return R;
   }

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMax(Dictionary::Node* R){
      if(R == nil){
         throw std::invalid_argument("Dictionary: findMin(): nil Node argument\n");
      }
      while(R->right != nil){
         R = R->right;
      }
      return R;
   }

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
   Dictionary::Node* Dictionary::findNext(Dictionary::Node* N){
      if(N == nil || N->right != nil){
         return nil;
      }
      Node* M = N->parent;
      while(M != nil && N == M->right){
         N = M;
         M = M->parent;
      }
      return M;
   }

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
   Dictionary::Node* Dictionary::findPrev(Dictionary::Node* N){
      if(N == nil || N->left != nil){
         return nil;
      }
      Node* M = N->parent;
      while(M != nil && N == M->right){
         N = M;
         M = M->parent;
      }
      return M;
   }


   // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
   int Dictionary::size() const{
      return num_pairs;
   }

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool Dictionary::contains(keyType k) const{
      if(search(root, k) == nil){
         return false;
      }
      return true;
   }

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType& Dictionary::getValue(keyType k) const{
      if(search(root, k) == nil){
         throw std::out_of_range("Dictionary: getValue(): key not in dictionary\n");
      }
      Node* N = search(root, k);
      //printf("N was found\n");
      //printf("%d\n", N->val);
      return N->val;
   }

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool Dictionary::hasCurrent() const{
      if(current == nil){
         return false;
      }
      return true;
   }

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType Dictionary::currentKey() const{
      if(!hasCurrent()){
         throw std::out_of_range("Dictionary: currentKey(): current has not been initialized\n");
      }
      return current->key;
   }

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& Dictionary::currentVal() const{
      if(!hasCurrent()){
         throw std::out_of_range("Dictionary: currentKey(): current has not been initialized\n");
      }
      return current->val;
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void Dictionary::clear(){
      postOrderDelete(root);
   }

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   void Dictionary::setValue(keyType k, valType v){
      Node* M = nil;
      Node* N = root;
      while(N != nil){
         M = N;
         if(k == N->key){
            N->val = v;
            return;
         }
         
         if(k < N->key){
            N = N->left;
         }
         else{
            N = N->right;
         }
      }
      Node* O = new Node(k, v);
      O->parent = M;
      if(M == nil){
         root = O;
         O->left = nil;
         O->right = nil;
         O->parent = nil;
      }
      else if(O->key < M->key){
         M->left = O;
         O->left = nil;
         O->right = nil;
         O->parent = M;
      }
      else{
         M->right = O;
         O->left = nil;
         O->right = nil;
         O->parent = M;
      }
      num_pairs++;

   }

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void Dictionary::remove(keyType k){
      if(!contains(k)){
         throw std::out_of_range("Dictionary: getValue(): key not in dictionary\n");
      }
      Node* N = search(root, k);
      if(N == current){
         current = nil;
      }
      if(N->left == nil){
         transplant(N, N->right);
      }
      else if(N->right == nil){
         transplant(N, N->left);
      }
      else{
         Node* M = findMin(N->right);
         if(M->parent != N){
            transplant(M, M->parent);
            M->right = N->right;
            M->right->parent = M;
         }
         transplant(N, M);
         M->left = N->left;
         N->left->parent = M;
      }
      num_pairs--;
   }

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::begin(){
      if(num_pairs == 0){
         return;
      }
      current = root;

   }

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::end(){
      if(num_pairs == 0){
         return;
      }
      current = findMax(root);
   }

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::next(){
      if(!hasCurrent()){
         throw std::out_of_range("Dictionary: next(): currnet has not been set\n");
      }
      if(current == findMax(root)){
         current = nil;
         return;
      }
      current = findNext(current);
   }

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::prev(){
      if(!hasCurrent()){
         throw std::out_of_range("Dictionary: prev(): currnet has not been set\n");
      }
      if(current == findMin(root)){
         current = nil;
         return;
      }
      current = findPrev(current);
   }


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string Dictionary::to_string() const{
      std::string s = "";
      inOrderString(s, root);
      return s;
   }

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
   std::string Dictionary::pre_string() const{
      std::string s = "";
      preOrderString(s, root);
      return s;
   }

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
   bool Dictionary::equals(const Dictionary& D) const{
      if(num_pairs != D.num_pairs){
         //printf("Uneven number of pairs\n");
         return false;
      }
      std::string a = "";
      std::string b = "";
      //std::string c = "";
      //std::string d = "";
      inOrderString(a, root);
      D.inOrderString(b, D.root);
      //preOrderVal(c, root);
      //D.preOrderVal(d, D.root);
      if(a != b){
         //printf("Different pre order string\n");
         return false;
      }
      return true;
   }


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
   std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
      return stream << D.Dictionary::to_string();
   }

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
   bool operator==( const Dictionary& A, const Dictionary& B ){
      return A.equals(B);
   }

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
   Dictionary& Dictionary::operator=( const Dictionary& D ){
      if(this != &D){
         Dictionary temp = D;
         std::swap(num_pairs, temp.num_pairs);
         std::swap(root, temp.root);
         std::swap(nil, temp.nil);
      }

      return *this;
   }