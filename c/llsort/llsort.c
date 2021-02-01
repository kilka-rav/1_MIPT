#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//создаем односвязный список
typedef struct _List {
	char* str;
	struct _List* next;
} List;

void llsplit(List** a, List** b, List* lst) {
	if ( lst ) {
		*a = lst;
		llsplit(b, &(*a)->next, lst->next);
	}
	else {
		*b = lst;
		*a = NULL;
		*b = NULL;
	}
}

void llmerge(List** lst, List* a, List* b) {
	if (a && b) {	// проверяем, что оба списка не пусты
		if ( strcmp(a->str, b->str) <= 0 ) { //сравниваем построчно и рекурсивно вызываем
			*lst = a;
			llmerge(&a->next, b, a->next);
		}
		else {
			*lst = b;
			llmerge(&b->next, b->next, a);
		}
	}
	else {
		*lst = a ? a : b; //синтаксический сахар, возвращаем непустой список
	}
}


void llsort(List** lst) {
	List* a = NULL;
	List* b = NULL;
	if( !*lst || !(*lst)->next) // проверяем, что в списке больше 0 и 1 элемента
		return;
	llsplit(&a, &b, *lst); //делим список на подсписки
	llsort(&a); //соритируем подсписки
	llsort(&b);
	llmerge(lst, a, b); // склеиваем подсписки
}

int llinsert(List** lst, const char* str) {
	List* new;
	if ( new = malloc(sizeof(List)) ) {
	      if ( new->str = (strdup(str)) ) {
		      new->next = *lst;
		      *lst = new;
		      return 0;
	      }
	      free(new);
	      return -1;
	}
	free(new);
	return -2;
}

void llfree(List* lst) {
	if ( lst ) {
		List* next = lst->next;
		free(lst->str);
		free(lst);
		llfree(next);
	}
}

void llprint(List* lst) {
	if ( lst ) {
		printf("%s", lst->str);
		llprint(lst->next);
	}
}

int main() {
	char buf[4096];
	List* lst = NULL;
	while (fgets(buf, sizeof(buf), stdin) ) {
		llinsert(&lst, buf);
	}

	printf("         SORTIROVO4k@\n");
	llsort(&lst);
	llprint(lst);
	llfree(lst);
}
