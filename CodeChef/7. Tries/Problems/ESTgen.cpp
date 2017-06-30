#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("input.txt", "w", stdout);
	srand(time(NULL));
	printf("10\n");
	int T = 10;
	while(T--){
		for(int i = 0; i < 100000; i++)
			printf("%c", rand()%26 + 'a');
		printf("\n");
	}
	return 0;
}