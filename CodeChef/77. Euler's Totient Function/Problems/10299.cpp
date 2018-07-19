//10299 - Relatives, EXACTLY THE SAME AS 10179?!
#include <bits/stdc++.h>
using namespace std;

template <class T>
T phi(T n){
	T ans = n;
	for(T i = 2; i*i <= n; i++){
		if(!(n % i)){
			while(!(n % i))
				n /= i;
			ans -= ans/i;
		}
	}
	//Last prime
	if(n > 1)
		ans -= ans/n;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	long long a;
	cin >> a;
	while(a){
		if(a == 1)
			cout << 0 << endl;
		else
			cout << phi<long long>(a) << endl;
		cin >> a;
	}
	return 0;
}