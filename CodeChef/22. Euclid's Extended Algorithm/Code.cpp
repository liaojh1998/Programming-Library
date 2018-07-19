//https://en.wikipedia.org/wiki/Euclidean_algorithm
//https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
//https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity
#include <bits/stdc++.h>
using namespace std;

//In order to understand the Extended Euclidean, start by the normal Euclidean.
/*
Here, the normal Euclidean algorithm is based on the simple fact that the gcd of both a and b do not change
no matter how you subtract the smaller from the bigger until reaching 0.
	Proof of validity:
	- First step: Say our algorithm results in the final nonzero remainder r_N-1.
	Backtracking on our algorithm, we know that our next remainder will be 0, so the remainder before the final nonzero remainder, r_N-2, must be divisble by r_N-1.
	Or: r_N-2 = k*r_N-1 for some integer k.
	Backtracking on our algorithm, we know that the division before r_N-2 gave the remainder r_N-1. Let that dividend be r_N-3.
	We have: r_N-3 = k*r_N-2 + r_N-1. Because both r_N-1 and r_N-2 are divisible by r_N-1, r_N-3 must also be divisble by r_N-1.
	Backtracking our algorithm until we reach a and b in a similar fashion, we have that r_N-1 divides both a and b.
	- Second step: Let c be some common divisor of both a and b. Then, we can represent a = mc and b = nc.
	We can take the first step of our algorithm: WLOG assume a > b, let r_0 be the remainder of a divided by b.
	We have: r_0 = a - k*b.
	Substituting a = mc and b = nc, we have r_0 = mc - k*(nc) = (m - k*n)c. Thus, r_0 is divisible by c.
	Continuing down the algorithm until we reach r_N-1, we reach the conclusion that if c divides both a and b, then c divides r_N-1.
	- Third step: Let gcd be the greatest common divisor of both a and b. Since gcd divides both a and b, then gcd divides r_N-1
	and gcd <= r_N-1. But because r_N-1 divides both a and b, and no number greater than r_N-1, such as r_N-2, r_N-3
	can divide a and b (because they leave remainders), r_N-1 <= gcd of a and b. Because gcd <= r_N-1 and r_N-1 <= gcd, r_N-1 = gcd.
*/
//Note: <algorithm> has a built-in __gcd(a, b) function for integers
//Iterative
template <class T>
T gcd(T a, T b){
	T t;
	while(b){
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}
//Recursive
/*
template <class T>
T gcd(T a, T b){
	if(b)
		return gcd(b, a%b);
	return a;
}
*/
//The proof for the Extended Euclidean Algorithm is a little bit more disappointing; it is made by induction.
//Many other named algorithms such as Blankenship algorithm represent the same procedure except in a form such that it is easier to follow.
//The algorithm will find 2 integers s and t such that they fulfill Bézout's Identity: as + bt = gcd(a, b) (and proving the identity).
/*
	Let r_0 = a, s_0 = 1, t_0 = 0, r_1 = b, s_1 = 0, t_1 = 1.
	By the remainder theorem, WLOG assume b < a, assume r_2 is the remainder of a divided by b, then there must exist an integer k_1 such that r_2 = a - k_1*b.
	Construct r_2 in such a manner:
	r_2 = (a*s_0 + b*t_0) - k_1*(a*s_1 + b*t_1) = (s_0 - k_1*s_1)*a + (t_0 - k_1*t_1)*b.
	Let s_2 = s_0 - k_1*s_1, and t_2 = t_0 - k_1*t_1. We have:
	r_2 = s_2*a + t_2*b.
	We can substitute for a and b and result:
	r_2 = s_2*r_0 + t_2*r_1 = r_0 - k_1*r_1.
	This gives 3 recurrence relations that can be constructed all the way until
	r_N-1 = gcd(a, b) = s_N-1*r_0 + t_N-1*r_1 = s_N-1*a + t_N-1*b, which proves Bezout's Identity:
	r_i+1 = r_i-1 - k_i*r_i,
	s_i+1 = s_i-1 - k_i*s_i,
	t_i+1 = t_i-1 - k_i*t_i,
	Where r_0 = a, s_0 = 1, t_0 = 0, r_1 = b, s_1 = 0, t_1 = 1.
	This continuous subtraction is basically the Extended Euclidean Algorithm.

	For a formal proof, let r_k be gcd(a, b). We know by the Euclidean algorithm proof above that it eventually terminates and give r_k.
	Here, we'll prove r_k = a*s_k + b*t_k, given:
	r_i+1 = r_i-1 - k_i*r_i,
	s_i+1 = s_i-1 - k_i*s_i,
	t_i+1 = t_i-1 - k_i*t_i,
	Where r_0 = a, s_0 = 1, t_0 = 0, r_1 = b, s_1 = 0, t_1 = 1.
	By induction:
	r_i+1 = r_i-1 - k_i*r_i = (a*s_i-1 + b*t_i-1) - k_i*(a*s_i + b*t_i) = a*(s_i-1 - k_i*s_i) + b*(t_i-1 - k_i*t_i) = a*s_i+1 + b*t_i+1.
	Which concludes the proof.
*/
//Formal Iterative
/*
template <class T>
T egcd(T a, T b, T &s, T &t){
	T div, rem, s_cur = 0, t_cur = 1, s_next, t_next;
	s = 1, t = 0;
	while(b){
		div = a/b;
		//r_i+1
		rem = a%b;
		a = b;
		b = rem;
		//s_i+1
		s_next = s - div*s_cur;
		s = s_cur;
		s_cur = s_next;
		//t_i+1
		t_next = t - div*t_cur;
		t = t_cur;
		t_cur = t_next;
	}
	return a;
}
*/
//Formal Recursive
/*
template <class T>
T egcd_exec(T a, T b, T s_p, T t_p, T s_, T t_, T &s, T &t){
	if(b){
		T div = a/b;
		return egcd_exec(b, a%b, s_, t_, s_p - div*s_, t_p - div*t_, s, t);
	}
	s = s_p;
	t = t_p;
	return a;
}

template <class T>
T egcd(T a, T b, T &s, T &t){
	return egcd_exec<T>(a, b, 1, 0, 0, 1, s, t);
}
*/
//An interesting, simple recursive version (why does this one work?)
//http://e-maxx.ru/algo/extended_euclid_algorithm
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
//Practical information
/*
	When 1 pair of Bézout coefficients have been calculated, all pairs can be calculated by:
	(s + k*(b/gcd(a, b)), t - k*(a/gcd(a, b)))
	And the other theorem which the Extended Euclidean algorithm proves is that there exists only 2 pairs of Bézout coefficients that satisfy:
	|s_i| <= |b/gcd(a, b)| and |t_i| <= |a/gcd(a, b)|
	Note that b and a are switched for the pair solutions, not a/gcd(a, b) first.
*/
/*
	lcm(a, b) = ab/gcd(a, b) by a simple inclusion-exclusion principle and showing that a/gcd(a, b) and b/gcd(a, b) are coprime.
*/

int main(){
	//Enter code here
	return 0;
}