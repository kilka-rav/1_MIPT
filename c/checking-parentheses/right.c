#include<stdio.h>

char check_rec(char** res) {
	char c = *(*res)++;
	char wait_for;
	switch (c) {
		case '{': wait_for = '}'; break;
		case '[': wait_for = ']'; break;
		case '(': wait_for = ')'; break;
		case '}': case ']': case ')': case '\0': return c;
	default:
		return check_rec(res);
	}
	return check_rec(res) != wait_for ? -1 : check_rec(res);
}
int main() {
	char buf[8192];
	char* s = fgets(buf,sizeof(buf), stdin);
	if ( !check_rec(&s) )
		printf("OK\n");
	else
		printf("NOT OK\n");
	return 0;
}
