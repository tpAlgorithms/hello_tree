#include <iostream>
#include <cstdio>


struct node_t {
  node_t(int _key = 0, node_t * _left = NULL, node_t *_right = NULL) 
    :key(_key)
    ,left(_left)
    ,right(_right)
  {}

  int key;
  node_t *left;
  node_t *right;
};

void action(node_t *node) {
  printf("%d\n", node->key);
}

template <typename action_t>
void traverse_in_order(node_t *root, action_t &action) {
  if (!root) return;
  traverse_in_order(root->right, action);
  action(root);
  traverse_in_order(root->left, action);
}

node_t * tree_add(node_t *root, int value) {
  if (!root) {
    return new node_t(value);
  }
  if (value < root->key) {
    root->left = tree_add(root->left, value);
  } else {
    root->right = tree_add(root->right, value);
  }
  return root;
}

const node_t* lower_bound(const node_t *root, int key) {
  if (!root) {
    return NULL;
  }

  const node_t * parent = root;
  for(const node_t *curr = root; ;) {
    if (key < curr->key) {
      parent = curr;
      curr = curr->left;
      if (curr==NULL) {
        return parent;
      }
    } else if (curr->key < key) {
      curr = curr->right;
      if (curr==NULL) {
        return parent;
      }
    } else {
      return curr;
    }
  }
}

const node_t* tree_find(const node_t *root, int key) {
  const node_t* ptr = lower_bound(root, key);
  if (!ptr) return NULL;
  if (key < ptr->key) {
    return NULL; 
  }
  return ptr;
}



int main() {
  node_t *root_node = NULL;

  int value;
  while(1 == scanf("%d", &value)) {
    root_node = tree_add(root_node, value);
  }

  traverse_in_order(root_node, action);
  //{ 
  //  print(el.key);
  //}

  for (int i = 0; i < 10; ++i) {
    const node_t *ptr = tree_find(root_node, i);
    int value = -1;
    if (ptr) value = ptr->key;

    std::cout << (void*)(ptr) << " " << i << " -> " << value << std::endl;
  }
  return 0;
}
