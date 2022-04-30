#include<stdio.h>

int main(){
  int arr[] = {1,2,3,4};
  char * str = 'hello world';
  printf("%s\n", &str);
  printf("%d\n", arr[1]);
  
  return 0;
}