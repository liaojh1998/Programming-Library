//UVa: 10104 - Euclid Problem
#include <bits/stdc++.h>
using namespace std;

template <class T>
T egcd(T a, T b, T &s, T &t){
	if(b){
		T gcd = egcd(b, a%b, s, t), div = a/b;
		T tmp = s - div*t;
		s = t;
		t = tmp;
		return gcd;
	}
	s = 1;
	t = 0;
	return a;
}

int main(){
	long long a, b, s, t, gcd;
	while(~scanf("%lld%lld", &a, &b)){
		gcd = egcd(a, b, s, t);
		printf("%lld %lld %lld\n", s, t, gcd);
	}
	return 0;
}