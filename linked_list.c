// RB트리 전 c언어 연습하기
// 단방향 연결리스트 구현하기
// 목표: 삽입, 삭제, 조회 기능 구현
// 삽입 -> 헤더 뒤에 새로운 값 추가
// 삭제 -> 첫 요소 삭제와 원하는 요소 삭제 추가
// 조회 -> 현제 링크드리스트에 들어있는 값들 조회
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
  struct Node *next;
  int data;  
} Node;

void insert_first(Node *head, int k){
  Node *insert_node = malloc(sizeof (Node));
  insert_node->next = head->next;
  insert_node->data = k;
  
  head->next = insert_node;  
}

void insert_end(Node *head, int k){
  Node *insert_node = malloc(sizeof (Node));
  insert_node->data = k;
  insert_node->next = NULL;
  Node *curr = head;
  while (curr->next != NULL){
    curr = curr->next;
  }
  curr->next = insert_node;
}

int search(Node *head, int k){
  Node *curr = head->next;
  while (curr != NULL){
    if (curr->data == k){
      free(curr);
      return 1;
    }else{
      curr = curr->next;
    }
  }
  free(curr);
  return 0;
}

void show(Node *head){
  Node *curr = head->next;
  while(curr != NULL){
    printf("%d\n", curr->data);
    curr = curr->next;
  }
  free(curr);
}

void delete_first(Node *head){
  if (head->next != NULL)
    head->next = head->next->next;
}

void delete(Node *head, int k){
  if (head->next != NULL && head->next->data == k){
    head ->next = head->next->next;
  }

  Node *curr = head->next;
  while(curr->next != NULL){
    if (curr->next-> data == k){
      curr->next = curr->next-> next;
    }else{
      curr = curr->next;
    }
  }
}

int main(){
  // 헤더 노드 링크스 리스트의 헤드
  struct Node *head = malloc(sizeof (struct Node));
  head->next = NULL;
  
  insert_first(head, 10);
  insert_first(head, 20);
  insert_first(head, 30);
  insert_first(head, 40);
  insert_first(head, 50);
  insert_first(head, 60);
  insert_end(head, 100);

  if (search(head, 70)){
    printf("숫자가 안에 있음\n");
  }else{
    printf("숫자 없음\n");
  };

  show(head);
  delete_first(head);
  delete(head, 30);
  printf("-------------\n");

  show(head);

  free(head);

  return 0;
}