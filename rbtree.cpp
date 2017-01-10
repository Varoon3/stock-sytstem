// File:        rbtree.cpp
// Author:      Varoon Mathur	
// Date:        2016-06-13
// Description: implementation of a RBTree class for use with CPSC 221 assignment #3

#include "rbtree.h"

using namespace std;


template <typename T>		
Node<T>* RBTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode){
	if (sourcenode == NULL)
		return NULL;
	
	Node<T>* copysource = new Node<T>(sourcenode->data); 
	copysource->is_black = sourcenode->is_black; 
	copysource->p = parentnode; 
								
	copysource->left = CopyTree(sourcenode->left, sourcenode); 
	copysource->right = CopyTree(sourcenode->right, sourcenode); 
 
	return copysource; 
}


template <typename T>		
void RBTree<T>::RemoveAll(Node<T>* node){
	if (node == NULL)
		return;
	if (node->left != NULL)
		RemoveAll(node->left);
	if (node->right != NULL)
		RemoveAll(node->right);
	delete node;
}

template <typename T>		
void RBTree<T>::RBRemoveFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild){

	Node<T>* y;

	while (x != root && (x == NULL || x->is_black == true)) {
		
        if (xisleftchild){
            y = xparent->right;

			if (!(y->is_black)){
				y->is_black = true;
                xparent->is_black = false;
                RotateLeft(xparent);
                y = xparent->right;
			}
            
            if (y->right == NULL && y->left == NULL){       
					y->is_black = false;			
					x = xparent;
					xparent = xparent->p;
					xisleftchild = (x == xparent->left);

            } else if (y->right == NULL && y->left != NULL){
            	if(y->left->is_black){
            		y->is_black = false;
            		x = xparent;
            		xparent = xparent->p;
            	} else {
            		y->left->is_black = true;
            		y->is_black = false;
					RotateRight(y);
					y = xparent->right;
            	}
            } else if (y->right != NULL && y->left == NULL){
            	if (y->right->is_black){
            		y->is_black = false;
            		x = xparent;
            		xparent = xparent->p;
            	} else {
            		y->is_black = xparent->is_black;
					xparent->is_black = true;
					y->right->is_black = true;
					RotateLeft(xparent);
					x = root;
            	}
            } else if (y->right->is_black && y->left->is_black){
				y->is_black = false;
				x = xparent;
				xparent = xparent->p;
			} else if (y->right->is_black){
				if (y->left != NULL){
				y->left->is_black = true;
				}
				y->is_black = false;
				RotateRight(y);
				y = xparent->right;
			} else{
				y->is_black = xparent->is_black;
				xparent->is_black = true;
				y->right->is_black = true;
				RotateLeft(xparent);
				x = root;
			} 


        } else {
             y = xparent->left;
             
			if (!(y->is_black)){	
            	y->is_black = true;
                xparent->is_black = false;
                RotateRight(xparent);
                y = xparent->left;   
			}

            if (y->right == NULL && y->left == NULL){    
				y->is_black = false;	
				x = xparent;
				xparent = xparent->p;
				xisleftchild = (x == xparent->left);
			} else if (y->right == NULL && y->left != NULL){
				if (y->left->is_black){  
					y->is_black = false;
					x = xparent;
					xparent = xparent->p;
				} else{
						y->is_black = xparent->is_black;
					xparent->is_black = true;
					y->left->is_black = true;
					RotateRight(xparent);
					x = root;
				}
			} else if (y->right != NULL && y->left == NULL){
				if (y->right->is_black){  
					y->is_black = false;
					x = xparent;
					xparent = xparent->p;
				} else{
						y->left->is_black = true;
						y->is_black = false;
						RotateLeft(y);
						y = xparent->left;
				}
			} else if (y->right->is_black && y->left->is_black){
				y->is_black = false;
				x = xparent;
				xparent = xparent->p;	
			} else if (y->right->is_black){	
				y->left->is_black = true;
				y->is_black = false;
				RotateLeft(y);
				y = xparent->left;
			} else{
				y->is_black = xparent->is_black;
				xparent->is_black = true;
				y->left->is_black = true;
				RotateRight(xparent);
				x = root;
			}
        }   
    }

	x->is_black = true;

}




template <typename T>		
int RBTree<T>::ComputeHeight(Node<T>* node) const{
	
	if (node == NULL)
		return 0;

	return max((1 + ComputeHeight(node->left)), (1 + ComputeHeight(node->right)));
}

template <typename T>			
RBTree<T>::RBTree(){	
	root = NULL;
	size = 0;
}

template <typename T>
RBTree<T>::RBTree(const RBTree<T>& rbtree){
	Node<T>* temp = rbtree.root;
	
	Node<T>* newRoot = new Node<T>(temp->data);
	size = rbtree.Size();
	newRoot->is_black = true;
	if (newRoot != NULL)
	{
		newRoot->left = CopyTree(temp->left, newRoot);
		newRoot->right = CopyTree(temp->right, newRoot);
	}
	root = newRoot;
}

template <typename T>		
RBTree<T>::~RBTree(){
	RemoveAll();
}


template <typename T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T>& rbtree){
	
  if (rbtree.Size() == 0)
    {
        this->RemoveAll();
        root = NULL;
        return *this;
    }

    if (this != &rbtree)
    {
        if (this->root != NULL)
        {
            this->RemoveAll();
        }

        Node<T>* R = rbtree.GetRoot();
        this->root = new Node<T>(R->data);
        this->size = rbtree.Size();
        CopyTree(R, this->root);
        
    }

    this->root->is_black = true;
    return *this;
}


template <typename T>		
bool RBTree<T>::Insert(T item){
	
        if (Contains(item) == true){
            return false;
        }
        
		Node<T>* y = BSTInsert(item);
        size++;
        
		if (root == NULL) {
            y->is_black = true;
            return true;
        }
       
        else {

            Node<T>* z;
            y->is_black =false;
            
			while (y != root && y->p->is_black == false){
                if (y->p->p != NULL && y->p == y->p->p->left){
                    z = y->p->p->right; 

                    if (z != NULL && z->is_black == false){
                        y->p->is_black = true;
                        z->is_black = true;
                        y->p->p->is_black = false;
                        y = y->p->p;
                    } else {
                        if (y == y->p->right){
                            y = y->p;
                            RotateLeft(y);
                        }

                        y->p->is_black = true;
                        y->p->p->is_black = false;
                        RotateRight(y->p->p);
                    }
                } else if (y->p->p != NULL || y->p == y->p->p->right){
                    z = y->p->p->left;
                    
					if (z != NULL && z->is_black == false){
                        y->p->is_black = true;
                        z->is_black = true;
                        y->p->p->is_black = false;
                        y = y->p->p;
                    } else {
                        if (y == y->p->left) {
                            y = y->p;
                            RotateRight(y);
                        }

                        y->p->is_black = true;
                        y->p->p->is_black = false;
                        RotateLeft(y->p->p);
                    }
                }
            }

            root->is_black=true;
            return true;     
           
        }
    }



template <typename T>
bool RBTree<T>::Remove(T item){

	bool XisLeftForNull = true;

	if (size <= 0 || root == NULL) //empty tree
		return false;

	Node<T>* y = NULL;
	Node<T>* node = root;
	Node<T>* x = NULL;
	
	if (Contains(item) == false)
		return false;
	
	if (size == 1) 
	{
		delete root;
		root = NULL;
		return true;
	}

	node = Find(item);
	
	if (node->left == NULL || node->right == NULL) {   
		y = node;
		
	} else {                                            
		y = Predecessor(node);	
	}

	if (y->left != NULL){ 
		x = y->left;
		
	} else {               
		x = y->right;	
	}


	if (x != NULL) {
		x->p = y->p;
	}

	if (y->p == NULL) {
		root = x;
	} else {
		if (y == y->p->left){
			y->p->left = x;
		} else{
			y->p->right = x;
			XisLeftForNull = false;
		}
	}

	if (y != node){            
		node->data = y->data;
	}                 
	
	if (y->is_black) {        
		if (x == NULL){
			RBRemoveFixUp(x, y->p, XisLeftForNull);
		} else {
			RBRemoveFixUp(x, y->p, x == x->p->left);
		}
	}

	size--;
	delete y;
	return true;
}


template <typename T>
void RBTree<T>::RemoveAll(){
	RemoveAll(root);
	root = NULL;
	size = 0;
}


template <typename T>
int RBTree<T>::Size() const{
	return size;
}


template <typename T>
int RBTree<T>::Height() const{
	
	if (size == 0 || size == 1)
		return size; 
	else
		return ComputeHeight(root); 
}

