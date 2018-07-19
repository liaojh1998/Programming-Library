//UVa 10090 - Marbles
#include <bits/stdc++.h>
using namespace std;

template <class T>
T egcd(T a, T b, T &s, T &t){
	if(b){
		T gcd = egcd(b, a%b, t, s), div = a/b;
		t -= div*s;
		return gcd;
	}
	s = 1;
	t = 0;
	return a;
}

int main(){
	long long n, c_1, c_2, n_1, n_2, gcd, s, t, div, k;
	bool failed;
	while(~scanf("%lld", &n) && n){
		scanf("%lld%lld%lld%lld", &c_1, &n_1, &c_2, &n_2);
		gcd = egcd(n_1, n_2, s, t);
		if(n%gcd)
			printf("failed\n");
		else{
			failed = false;
			div = n/gcd;
			s *= div, t *= div;
			if(s < 0){
				k = (-s)%(n_2/gcd) ? (-s)/(n_2/gcd)+1 : (-s)/(n_2/gcd);
				if(t - n_1/gcd*k < 0)
					failed = true;
				else{
					s += n_2/gcd*k;
					t -= n_1/gcd*k;
				}
			}else if(t < 0){
				k = (-t)%(n_1/gcd) ? (-t)/(n_1/gcd)+1 : (-t)/(n_1/gcd);
				if(s - n_2/gcd*k < 0)
					failed = true;
				else{
					s -= n_2/gcd*k;
					t += n_1/gcd*k;
				}
			}
			if(failed)
				printf("failed\n");
			else{
				if(c_1*n_2 > c_2*n_1){
					k = s/(n_2/gcd);
					s -= n_2/gcd*k;
					t += n_1/gcd*k;
				}else{
					k = t/(n_1/gcd);
					s += n_2/gcd*k;
					t -= n_1/gcd*k;
				}
				printf("%lld %lld\n", s, t);
			}
		}
	}
	return 0;
}