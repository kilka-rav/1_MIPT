#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void gen(int n, char* buf, void (*cb) ()) {
	int k;
	void cb1() {
		gen(n - k - 2, buf + k + 2, cb);
	}
	if ( !n )
		cb();
	else
		buf[0] = '1';
		for(k = 0; k < n; k += 2) {
			buf[k+1] = '0';
			gen(k, buf + 1, cb1);
		}
}
	


int main() {
	int n;
	fscanf(stdin,"%d", &n);
	char* buf = malloc(2 * n + 1);
	void cb() {
		printf("%s\n", buf);
	}
	memset(buf, 0, 2 * n + 1);
	gen(2 * n, buf, cb);
	free(buf);
	return 0;
}
