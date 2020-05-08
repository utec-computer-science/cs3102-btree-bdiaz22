#include <iostream>
#include <vector> 

using namespace std;

template <typename T>
class SS_Traits{
public:
  typedef T  value_t;
  typedef vector<value_t> container_t;
  typedef typename container_t::iterator iterator_t;
  
  class simple_search{
  public:
    int operator() (container_t a, value_t v){
      for (int i = 0; i < a.size(); i++)
      {
        if (a[i] == v) 
          return i;
      }
      return -1;    
    }
  };

  class post_order_print{
  public:
    void operator() (void){
      cout << "post order" << endl;
    }
  };

  typedef simple_search functor_t;
  typedef post_order_print print_t;
};

template <typename T>
class BS_Traits{
public:
  typedef T  value_t;
  typedef vector<value_t> container_t;
  typedef typename container_t::iterator iterator_t;
  
  class binary_search{
  public:
    int operator() (container_t a, value_t v){
      return 0;
    }
  };

  class pre_order_print{
  public:
    void operator() (void){
      cout << "pre order" << endl;
    }
  };

  typedef binary_search functor_t;
  typedef pre_order_print print_t;
};

template <typename T, int S> 
class BNode {
public:
  typedef typename T::value_t value_t;
  typedef typename T::container_t container_t;
  typedef typename T::iterator_t iterator_t;
  typedef vector< BNode<T,S>* > pcontainer_t;
  typedef typename T::functor_t functor_t;

  container_t keys;
  pcontainer_t ptrs;
  size_t  order;
  size_t n;
  bool isLeaf;
  functor_t search;

  BNode(bool leaf):order(S),n(0),isLeaf(leaf){
    keys=container_t(order,0);
    ptrs=pcontainer_t(order+1,nullptr); 
  }

  ~BNode(void){}

  void insertNodeChild(value_t value) 
    { 
        int i = n-1; 
        if (isLeaf == true) 
        { 
            while (i >= 0 && keys[i] > value) 
            { 
                keys[i+1] = keys[i]; 
                i-=1; 
            } 
            keys[i+1] = value; 
            n +=1; 
        } 
        else 
        { 
            while (i >= 0 && keys[i] > value) 
                i-=1; 
            if (ptrs[i+1]->n == 2*order-1) 
            { 
                splitNodeChild(i+1, ptrs[i+1]); 
                if (keys[i+1] < value) 
                    i+=1; 
            } 
            ptrs[i+1]->insertNodeChild(value); 
        } 
    } 
  
    void splitNodeChild(int i, BNode<T,S> *y)  
    { 
        BNode<T,S> *z = new BNode<T,S>(y->isLeaf); 
        z->n = order - 1; 
      
        for (int j = 0; j < order-1; j++) 
            z->keys[j] = y->keys[j+order]; 
      
        if (y->isLeaf == false) 
        { 
            for (int j = 0; j < order; j++) 
                z->ptrs[j] = y->ptrs[j+order]; 
        } 
      
        y->n = order - 1; 
      
        for (int j = n; j >= i+1; j--) 
          ptrs[j+1] = ptrs[j]; 
      
        ptrs[i+1] = z; 
      
        for (int j = n-1; j >= i; j--) 
            keys[j+1] = keys[j]; 
      
        keys[i] = y->keys[order-1]; 
      
        n += 1; 
    }
    bool find(value_t val)
    {
      int i = 0;
      while(i < n && val > keys[i])
        i++;

      if(keys[i] == val)
        return true;

      if (isLeaf == true)
        return false;

      return ptrs[i]->find(val);
    }
};

template <typename T, int S>
class BTree {
public: 
  typedef typename T::value_t value_t;
  typedef typename T::container_t container_t;
  typedef typename T::functor_t functor_t;
  typedef typename T::print_t print_t;

  BNode<T,S>* root;
  print_t print;
  functor_t search;

  BTree(void):root(nullptr){
  }

  ~BTree(void){}

  void insert(const value_t& value = 0)
  {
    // TODO :: INSERT
    if (root == nullptr) 
    {   
      root = new BNode<T,S>(true); 
      root->keys[0] = value;  
      root->n = 1;  
    } 
    else  
    { 
      if (root->n == 2*root->order-1) 
      { 
        BNode<T,S> *new_node = new BNode<T,S>(false); 
        new_node->ptrs[0] = root; 
        new_node->splitNodeChild(0, root); 
        int i = 0; 
        if (new_node->keys[0] < value) 
          i++; 
        new_node->ptrs[i]->insertNodeChild(value);
        root = new_node; 
      } 
      else  
        root->insertNodeChild(value); 
    } 
  }

  bool find(const value_t value = 0) const{
    // TODO :: SEARCH
    // search(x); inside each page
    if (root == nullptr)
      return false;
    else
      return root->find(value);
  }

  friend ostream& operator<<(ostream& out, BTree<T,S> tree){
    tree.print();// (out)
    // IN PRE POST LEVEL ORDER
    return out;
  }

};

int main() {
  typedef BS_Traits<int> btrait_t;
  BTree<btrait_t,4> tree;
  tree.find(10);
  cout<<tree<< endl;

  typedef SS_Traits<float> strait_t;
  BTree<strait_t,4> stree; 
  
  stree.insert(10);
  stree.insert(2);
  stree.insert(4);
  stree.insert(41);
  stree.insert(15);
  stree.insert(26);
  stree.insert(19);
  stree.insert(11);
  
  cout << stree.find(10) << endl;
  cout << stree.find(2) << endl;
  cout << stree.find(4) << endl;
  cout << stree.find(41) << endl;
  cout << stree.find(15) << endl;
  cout << stree.find(26) << endl;
  cout << stree.find(19) << endl;
  cout << stree.find(11) << endl;
  cout << stree.find(100)<< endl;
  cout << stree.find(8) << endl;
  cout << stree.find(0) << endl; 
  std::cout << std::endl << stree << std::endl;
}