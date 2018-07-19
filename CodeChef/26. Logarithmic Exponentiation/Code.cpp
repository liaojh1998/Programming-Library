#include <bits/stdc++.h>
using namespace std;

template<class T> struct BinPow{
	static T pow(T base, long long p){
		T res = 1; //Change this if T has some different identity, for example, matrices use identity matrix
		while(p){
			if(p & 1)
				res = res * base;
			base = base * base;
			p >>= 1;
		}
		return res;
	}
	static T mpow(T base, long long p, const long long& MOD){
		T res = 1;
		while(p){
			if(p & 1)
				res = (res * base)%MOD;
			base = (base * base)%MOD;
			p >>= 1;
		}
		return res%MOD;
	}
	//Recursive, if too much memory is required
	static T rpow(const T& base, long long p){
		if(p == 1) return base;
		if(!(p & 1)){
			T res = rpow(base, p >> 1);
			return res * res;
		}
		return base * rpow(base, p - 1);
	}
	static T rmpow(const T& base, long long p, const long long& MOD){
		if(p == 1) return base%MOD;
		if(!(p & 1)){
			T res = rmpow(base, p >> 1, MOD);
			return (res * res)%MOD;
		}
		return (base * rmpow(base, p - 1, MOD))%MOD;
	}
};

int main(){
	return 0;
}