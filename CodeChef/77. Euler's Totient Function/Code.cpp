//http://e-maxx.ru/algo/euler_function
//https://en.wikipedia.org/wiki/Euler%27s_totient_function
#include <bits/stdc++.h>
using namespace std;

//Euler's totient function counts the positive integers up to a given integer n that are relatively prime to n.
//Definition of relatively prime: gcd(n, natural numbers) = 1. (This means 1 is included in the totient function, since gcd(n, 1) = 1)
//Also, phi(1) = 1 here. If needed, make phi(1) = 0.
/*
	Important properties:
	Let m, n, p be some arbitrary natural number.
	- If p is prime:
		phi(p) = p - 1
	Proof: Obvious since p is prime and all numbers less than it are not multiples of p.
	- If p is prime and it is raised to the power k:
		phi(p^k) = p^k - p^(k-1)
	Proof: Since p is prime, any natural number m less than p^k are not relatively prime to p^k when they are a multiple of p.
	If m is a multiple of p, then p can divide both p^k and m, which implies gcd(p^k, m) != 1.
	Multiples of p less than p^k come in the form of 1*p, 2*p, 3*p, 4*p, ..., p^(k-1)*p, which implies there are p^(k-1) such numbers.
	Therefore, of the p^k numbers from 1 to p^k, we can take away p^(k-1) numbers which are not relatively prime to p^k.
	- If m and n is coprime, then:
		phi(m*n) = phi(m)*phi(n)
	Proof: Construct a set of nonnegative integers less than n, a set of nonnegative integers less than m, and a set of nonnegative integers less than m*n.
	Let them be respectively set A, B, and C. By the Chinese remainder theorem, we can construct a bijection (one-to-one correspondence)
	between A x B and C. That is, there exist only 1 number in C, or c (mod m*n), that is congruent to a (mod m) and b (mod n) for some number a, b, and c.
	Formally, c ≡ a (mod m) and c ≡ b (mod n) has only 1 solution with 0 <= c < m*n given m and n are coprime. By the bijection, there must be a
	one-to-one correspondence in the multiplication, which proves the multiplicative property.

	Combining everything above, for some arbitrary nonnegative integer n, factored into relatively coprime power primes p_1^k_1, p_2^k_2, p_3^k_3, ..., p_r^k_r:
	phi(n) = phi(p_1^k_1)*phi(p_2^k_2)*phi(p_3^k_3)*...*phi(p_r^k_r)
	phi(n) = (p_1^k_1 - p_1^(k_1-1))*(p_2^k_2 - p_2^(k_2-1))*...*(p_r^k_r - p_r^(k_r-1))
	phi(n) = (p_1^k_1)*(p_2^k_2)*(p_3^k_3)*...*(p_r^k_r)*(1 - 1/p_1)*(1 - 1/p_2)*...*(1 - 1/p_r)

	Which gives us the formula:
		phi(n) = n*(1 - 1/p_1)*(1 - 1/p_2)*...*(1 - 1/p_r)

	For a better computation (linear):
		phi(n) = n/(p_1*p_2*p_3*...*p_r)*(p_1 - 1)*(p_2 - 1)*(p_3 - 1)*...*(p_r - 1)

	Or (square root):
		phi(n) = (n - n/p_1)*(1 - 1/p_2)*(1 - 1/p_3)*...*(1 - 1/p_r)
		phi(n) = ((n - n/p_1) - (n - n/p_1)/p_2)*(1 - 1/p_3)*...*(1 - 1/p_r)
		phi(n) = (((n - n/p_1) - (n - n/p_1)/p_2) - ((n - n/p_1) - (n - n/p_1)/p_2)/p_3)*...*(1 - 1/p_r)
		And so on until (1 - 1/p_r) as an algorithm:

		Let (n - n/p_1) be result_1:
			phi(n) = (result_1 - result_1/p_2)*(1 - 1/p_3)*...*(1 - 1/p_r)
		Let (result_1 - result_1/p_2) be result_2:
			phi(n) = (result_2 - result_2/p_3)*...*(1 - 1/p_r)
		And continuing down until (1 - 1/p_r) gives us result_r, which is the answer we need.

	Ultimately, computing phi then depends on optimization techniques combined with quick factorization of n.

	Obviously, no worries on integer overflow, since phi(n) < n.
	Other identities:
		- phi(m*n) = phi(m)*phi(n)*gcd(m, n)/phi(gcd(m, n)).
		- sum { phi(d) | d is a divisor of n } = n.
	Interesting properties:
		- When n >= 3, since all 3 of the properties used to construct the formula return even numbers, the function will always give out even numbers.
		- Cototient, or natural numbers less than or equal to n that is not relatively prime to n, is "n - phi(n)".
*/

//O(N)
/*
template <class T>
T phi(T n){
	T ans = n;
	for(T i = 2; i <= n; i++){
		if(!(n % i)){
			while(!(n % i))
				n /= i;
			ans /= i;
			ans *= (i - 1);
		}
	}
	return ans;
}
*/

//O(sqrt(N))
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
	//Enter code here
	return 0;
}