#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int main() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	char ch,tmp;
	int m = 0;
	scanf("%c", &tmp);
	for (int i = 0; i < c; i++) {
		scanf("%c", &ch);
		m = (a + b) / 2;
		if (ch == 'Y') {// m+1 <= k <= b
			a = m + 1;
		}
		else { // ch == N ,, a <= k <= m
			b = m;
		}
	}
	printf("%d", a);
}