//11327 - Enumerating Rational Numbers, O(Q*(N + log(N)) + N*sqrt(N)) complexity, there are 200000 numbers
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

template <class T>
T gcd(T a, T b){
	return b ? gcd(b, a%b) : a;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	long long dp[200005];
	dp[0] = 1;
	dp[1] = 2;
	for(long long i = 2; i <= 200000; i++)
		dp[i] = dp[i-1] + phi<long long>(i);
	long long k;
	cin >> k;
	while(k){
		if(k == 1)
			cout << "0/1" << endl;
		else{
			long long d = lower_bound(dp, dp+200001, k) - dp;
			long long count = k - dp[d-1], n = 0;
			while(count--){
				n++;
				while(gcd<long long>(n, d) != 1)
					n++;
			}
			cout << n << '/' << d << endl;
		}
		cin >> k;
	}
	return 0;
}