#ifdef _RBTREE_H_

template <typename T>
Node<T>* RBTree<T>::BSTInsert(T item)
{
  Node<T>* refnode; 
  Node<T>* newnode; 
  if (size <= 0)
  {
    root = new Node<T>(item);
    newnode = root;
  }
  else 
  {
    refnode = root;

    while ((item < refnode->data && refnode->left != NULL) || (item > refnode->data && refnode->right != NULL))
    {
      if (item < refnode->data)
        refnode = refnode->left;
      else if (item > refnode->data)
        refnode = refnode->right;
    }
    newnode = new Node<T>(item);
    newnode->p = refnode;
    if (item < refnode->data)
      refnode->left = newnode;
    else
      refnode->right = newnode;
  }

  return newnode;
}

template <typename T>
bool RBTree<T>::Contains(T item) const
{
  Node<T>* node = root;

  while (node != NULL)
  {
    if (item == node->data)
      return true;
    else if (item < node->data)
      node = node->left;
    else
      node = node->right;
  }

  return false;
}

template <typename T>
T* RBTree<T>::Retrieve(T item)
{
  T* value = NULL;

  Node<T>* node = root;
  while (node != NULL)
  {
    if (item == node->data)
    {
      value = &(node->data);
      break; 
    }
    else if (item < node->data)
      node = node->left;
    else
      node = node->right;
  }
  return value;
}

template <typename T>
void RBTree<T>::InOrder(const Node<T>* node, T* arr, int arrsize, int& index) const
{
  if (node != NULL)
  {
    // recurse on left child
    if (node->left != NULL)
      InOrder(node->left, arr, arrsize, index);
    arr[index] = node->data;
    index++;
    if (node->right != NULL)
      InOrder(node->right, arr, arrsize, index);
  }
}

template <typename T>
void RBTree<T>::PreOrder(const Node<T>* node, T* arr, int arrsize, int& index) const
{
  if (node != NULL)
  {
	if(node->is_black)
		arr[index] = node->data + 10000;
		else
			arr[index] = node->data;
	index++;
    if (node->left != NULL)
      PreOrder(node->left, arr, arrsize, index);
    if (node->right != NULL)
      PreOrder(node->right, arr, arrsize, index);
  }
}

template <typename T>
void RBTree<T>::RotateLeft(Node<T>* node)
{
  if (node != NULL)
  {
    if (node == root)
    {
      if (node->right == NULL)
      {
      }
      else
      {
        Node<T>* rc = node->right; 
        Node<T>* rclc = node->right->left; 
        rc->p = NULL;
        rc->left = node;
        node->p = rc;
        node->right = rclc;
        if (rclc != NULL)
          rclc->p = node;

        root = rc;
      }
    }
    else
    {
      if (node->right == NULL)
      {
      }
      else
      {
        Node<T>* parent = node->p; 
        Node<T>* rc = node->right; 
        Node<T>* rclc = node->right->left; 
        if (node == node->p->left)
          node->p->left = rc;
        else
          node->p->right = rc;
        rc->p = parent;
        rc->left = node;
        node->p = rc;
        node->right = rclc;
        if (rclc != NULL)
          rclc->p = node;
      }
    }
  }
}

template <typename T>
void RBTree<T>::RotateRight(Node<T>* node)
{
  if (node != NULL)
  {
    if (node == root)
    {
      if (node->left == NULL)
      {
      }
      else
      {
        Node<T>* lc = node->left;
        Node<T>* lcrc = node->left->right; 
        lc->p = NULL;
        lc->right = node;
        node->p = lc;
        node->left = lcrc;
        if (lcrc != NULL)
          lcrc->p = node;

        root = lc;
      }
    }
    else
    {
      if (node->left == NULL)
      {
      }
      else
      {
        Node<T>* parent = node->p; 
        Node<T>* lc = node->left; 
        Node<T>* lcrc = node->left->right; 

        if (node == node->p->left)
          node->p->left = lc;
        else
          node->p->right = lc;

        lc->p = parent;
        lc->right = node;
        node->p = lc;
        node->left = lcrc;
        if (lcrc != NULL)
          lcrc->p = node;
      }
    }
  }
}

template <typename T>
Node<T>* RBTree<T>::Predecessor(Node<T>* node) const
{
  Node<T>* pre = NULL;
  if (node != NULL)
  {
    if (node->left == NULL)
      pre = NULL;
    else
    {
      pre = node->left;
      while (pre->right != NULL)
      {
        pre = pre->right;
      }
    }
  }
  return pre;
}

template <typename T>
Node<T>* RBTree<T>::Find(T item) const
{
  Node<T>* node = root;

  while (node != NULL)
  {
    if (item == node->data)
      return node;
    else if (item < node->data)
      node = node->left;
    else
      node = node->right;
  }
  return NULL;
}

template <typename T>
T* RBTree<T>::DumpInOrder(int& arrsize) const
{
  int index = 0;
  arrsize = size;
  T* contents = new T[size];
  InOrder(this->root, contents, size, index);
  return contents;
}


template <typename T>
T* RBTree<T>::DumpPreOrder(int& arrsize) const
{
  int index = 0;
  arrsize = size;
  T* contents = new T[size];
  PreOrder(this->root, contents, size, index);
  return contents;
}

#endif