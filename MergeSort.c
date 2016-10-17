#include <stdio.h>
#include <stdlib.h>

/* After calling the program, enter numbers for the list, pressing the
   ENTER key after each one. When finished with your list, make the last
   item CTRL-Z. This will invoke EOF and the program will run. */

typedef struct CELL *LIST;
struct CELL {
  int element;
  LIST next;
};

LIST merge(LIST list1, LIST list2);
LIST split(LIST list);
LIST MergeSort(LIST list);
LIST MakeList();
void PrintList(LIST list);

int main(void) {
  LIST list;

  list = MakeList();
  printf("My List:\n");
  PrintList(list);

  printf("My Sorted List:\n");
  PrintList(MergeSort(list));
}

LIST MakeList() {
  int x;
  LIST pNewCell;

  if (scanf("%d", &x) == EOF) return NULL;
  else {
    pNewCell = (LIST) malloc(sizeof(struct CELL));
    pNewCell->next = MakeList();
    pNewCell->element = x;
    return pNewCell;
  }
}

void PrintList(LIST list) {
  while (list != NULL) {
    printf("%d\n", list->element);
    list = list->next;
  }
}

LIST MergeSort(LIST list) {
  LIST SecondList;

  if (list == NULL) return NULL;
  else if (list->next == NULL) return list;
  else {
    SecondList = split(list);
    return merge(MergeSort(list), MergeSort(SecondList));
  }
}

LIST merge(LIST list1, LIST list2) {
  if (list1 == NULL) return list2;
  else if (list2 == NULL) return list1;
  else if (list1->element <= list2->element) {
    list1->next = merge(list1->next, list2);
    return list1;
  }
  else {
    list2->next = merge(list1, list2->next);
    return list2;
  }
}

LIST split(LIST list) {
  LIST pSecondCell;

  if (list == NULL) return NULL;
  else if (list->next == NULL) return NULL;
  else {
    pSecondCell = list->next;
    list->next = pSecondCell->next;
    pSecondCell->next = split(pSecondCell->next);
    return pSecondCell;
  }
}
