#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include "Macros.h"
using namespace std;

template<typename T>
class BNode {
  public: 
  typedef T value_t ;
  typedef vector<value_t> container_t;
  typedef vector<BNode*> pcontainer_t;
  typedef typename std::vector<value_t>::iterator iterator_t;

  unsigned int order;
  container_t data;
  pcontainer_t children;
  bool leaf;
  size_t n;

  BNode(unsigned int order = 4):order(order),leaf(false),n(0)
  {
    data = container_t(order+1,0);
    children = pcontainer_t(order,nullptr);
  }
  
  void insertNodeChild(value_t value) 
    { 
        int i = n-1; 
        if (leaf == true) 
        { 
            while (i >= 0 && data[i] > value) 
            { 
                data[i+1] = data[i]; 
                i-=1; 
            } 
            data[i+1] = value; 
            n +=1; 
        } 
        else 
        { 
            while (i >= 0 && data[i] > value) 
                i-=1; 
            if (children[i+1]->n == order-1) 
            { 
                splitNodeChild(i+1, children[i+1]); 
                if (data[i+1] < value) 
                    i+=1; 
            } 
            children[i+1]->insertNodeChild(value); 
        } 
    }
    void splitNodeChild(int i, BNode*& node)  
    { 
        BNode* new_node = new BNode(order);
        new_node->leaf = node->leaf; 
        new_node->n = ceil(order/2) - 1; 
      
        for (int j = 0; j < ceil(order/2)-1; j++) 
            new_node->data[j] = node->data[j+order]; 
      
        if (node->leaf == false) 
        { 
            for (int j = 0; j < ceil(order/2); j++) 
                new_node->children[j] = node->children[j+order]; 
        } 
      
        node->n = ceil(order/2) - 1; 
      
        for (int j = n; j >= i+1; j--) 
          children[j+1] = children[j]; 
      
        children[i+1] = new_node; 
      
        for (int j = n-1; j >= i; j--) 
            data[j+1] = data[j]; 
      
        data[i] = node->data[ceil(order/2)-1]; 
      
        n += 1; 
    }

    bool find(value_t val)
    {
      int i = 0;
      while(i < n && val > data[i])
        i++;

      if(data[i] == val)
        return true;

      if (leaf == true)
        return false;

      return children[i]->find(val);
    }
  ~BNode(void){}
};


#endif