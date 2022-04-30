#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int key;
  struct node *parent, *left, *right;
} node;

typedef struct{
  node *root;
} binery_tree;

void insert(binery_tree *t, const int key){
  // 탐색 실패시 실패한 위치에 삽입한다.
  node *insert_node = (node*)calloc(1, sizeof(node));
  insert_node->key = key;

  if (t->root == NULL){
    //트리의 root가 null이면 insert_node를 트리에 root로 설정한다.
    t->root = insert_node;
    return; 
  }else{
    node *curr = t->root;
    while (curr != NULL){
      if (curr->key > key){
        if (curr->left == NULL){
          curr->left = insert_node;
          return ;
        }else{
          curr = curr->left;
        }
      }else{
        if (curr->right == NULL){
          curr->right = insert_node;
          return ;
        }else{
          curr= curr->right;
        }
      }
    }
  }
}

void inorder(node *root){
  // 중위순회 이진 검색트리에서는 정렬되어 나온다.

  if (root != NULL){
    inorder(root ->left);
    printf("%d\n", root->key);
    inorder(root ->right);
  }
}

node * search(node *root, int data){
  if (root == NULL || root->key == data){
    return root;
  }else if (root-> key > data){
    return search(root->left, data);
  }else
    return search(root->right, data);
}

// 반환타입을 노드 포인터로 해야하는 이유
// 루트노드가 지워지고 아래의 값이 새 루트가 되었을 때
// 새로운 루트노드를 반환값으로 주어야한다.

node * delete(node * root, int data){
  node *p = root;
  node * parent = NULL;
  while ((p != NULL) && (p->key != data)){
    parent = p;
    if (p->key >data){
      p = p->left;
    }else{
      p = p-> right;
    }
  }
  if (p == NULL){
    printf("찾는 노드가 없음\n");
    return root;
  }

  // 차수가 0인 경우 단말노드
  if (p->left == NULL && p->right == NULL){
    //현재 노드가 루트인지 아닌지 확인해야함
    if(parent == NULL){ // 차수가 0이고 루트 인경우
      root = NULL;
    }else{
      //parent가 가리키는 p의 위치를 찾고 NULL로 할당한다.
      if (parent->left == p){
        parent->left = NULL;
      }else{
        parent->right = NULL;
      }
    }
  }else if (p->left == NULL || p ->right == NULL){ // 차수가 1인 경우
    node *child = (p->left != NULL) ? p->left : p->right;
    if(parent == NULL)
      root = child;
    else{
      if (parent->left == p){
        parent->left = child;
      }else{
        parent->right = child;
      }
    }
  }else{
    // 후계자를 찾기위해서 왼쪽 오른쪽 상관x 오른쪽으로 찾아가겠음
    node *succ_parent = p;
    node *succ = p -> right;
    while(succ->left != NULL){
      succ_parent = succ;
      succ= succ->left;
    }
    p->key = succ->key;
    // succ노드는 왼쪽자식이 없는 것이 확실
    // 있을 수 있는 succ의 오른쪽 자식을 succ_parent에 할당한다.
    if (succ_parent ->left == succ)
      succ_parent ->left = succ->right;
    else
      //삭제하기 위해서 가장 작은 값을 찾아야하는데 
      // succ_parent의 오른쪽에 succ이 있으면 더 큰 값이지 않나?
      succ_parent->right = succ->right;
    p = succ;
  }
  
  // 어떤 경우에도 p는 삭제된다.
  free(p);
  return root;
}

int main(){
  binery_tree *t = (binery_tree*)calloc(1,sizeof(binery_tree));
    
  t->root = NULL;

  insert(t, 50);
  insert(t, 30);
  insert(t, 60);
  insert(t, 20);
  insert(t, 40);

  inorder(t->root);
  printf("-------------\n");
  delete(t->root, 20);
  inorder(t->root);
  printf("-------------");
 
  return 0;
}