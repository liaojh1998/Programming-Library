//Timus: 1673. Admission to Exam
#include <bits/stdc++.h>
using namespace std;

/*
	Let K be the number of students that were admitted.
	We know 1 student, call it d, in K must satisfy the following condition:
		For all 0 < k <= N, there exist a 0 <= c < N such that (c*N + k)%d = 0.
	Let q = (-k)%d. We want to find when (c*N)%d = q, which implies for some arbitrary number p, c*N = p*d + q.
	This turns into a linear diophantine equation, c*N - p*d = q, which can be solved using the Extended Euclidean Algorithm.
	A solution exist for q if q is divisible by gcd(N, d). However, because q is clocked by d, we need to find solutions for all 0 <= q < d.
	Because only the number 1 can divide all possible values of q, there exist a solution for all possible values of q if gcd(N, d) = 1.
	Since all values of our linear diophantine equations will eventually be modded by d, a c < N must exist for all values of k when gcd(N, d) = 1.
	Furthermore, it is proven that there must exist a solution |c| <= |d/gcd(N, d)| by the Extended Euclidean Algorithm.
	Therefore, our problem reduces to finding the minimal N that has K relative primes less than it.
	In other words, figure out a formula for the inverse of the Euler Totient function.
*/
//This will not be a formula, rather, just generating the Euler Totient function tree backwards by its identities, and then checking.

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	return 0;
}