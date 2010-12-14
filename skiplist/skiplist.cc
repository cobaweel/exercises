// -*- c++ -*-

#include <stdlib.h>
#include "skiplist.h"

static const int depth = 8;
static const float reduction = .25; 

struct Node {
     int key;
     int val;
     Node *next[depth];
};

struct SkipList::D {
     Node *first[depth];
     void walk(int key, Node *prv[], Node *cur[]);
};

void SkipList::D::walk(int key, Node *prv[], Node *cur[])
{
     Node *x = 0;
     for ( int i = depth - 1; i >= 0; --i ) {
	  prv[i] = 0;
	  cur[i] = x ?: first[i];
	  while ( cur[i] && cur[i]->key < key ) {
	       x = prv[i] = cur[i];
	       cur[i] = cur[i]->next[i];
	  }	  
     }
}

SkipList::SkipList() 
{
     d = new D;
     for ( int i = 0; i < depth; ++i )
	  d->first[i] = 0;
}

SkipList::~SkipList() 
{
     Node *cur = d->first[0];
     Node *prv = d->first[0];
     while ( cur ) {
	  prv = cur;
	  cur = cur->next[0];
	  delete prv;
     }
}

unsigned SkipList::len(void) 
{
     Node *cur = d->first[0];
     unsigned i = 0;
     while ( cur ) {
	  cur = cur->next[0];
	  ++i;
     }
     return i;
}


void SkipList::put(int key, int val) 
{
     Node *prv[depth];
     Node *cur[depth];
     d->walk(key, prv, cur);
     if ( cur[0] && cur[0]->key ==key ) {
	  return;
     } else {
	  Node *x = new Node;
	  x->key = key;
	  x->val = val; 
	  for ( int i = 0; i < depth; ++i )
	       x->next[i] = 0;
	  int p = RAND_MAX;
	  for ( int i = 0; i < depth; ++i ) {
	       x->next[i] = cur[i];
	       if ( prv[i] )
		    prv[i]->next[i] = x;
	       else
		    d->first[i] = x;
	       p *= reduction;
	       if ( rand() > p ) break;
	  }
     }
}

bool SkipList::get(int key, int *val) 
{
     Node *prv[depth];
     Node *cur[depth];
     d->walk(key, prv, cur);
     if ( cur[0] && cur[0]->key == key ) {
	  *val = cur[0]->val;
	  return true;
     } else {
	  return false;
     }
}

void SkipList::del(int key) 
{
     Node *prv[depth];
     Node *cur[depth];
     d->walk(key, prv, cur);
     for (int i = 0; i < depth; ++i) {
	  if ( cur[i] && cur[i]->key == key ) {
	       if ( prv[i] ) {
		    prv[i]->next[i] = cur[i]->next[i];
	       } else {
		    d->first[i] = cur[i]->next[i];
	       }
	  }
     } 
     delete cur[0];
}
