#include <bits/stdc++.h>
using namespace std;

template<class T> class Matrix{
private:
	int N, M; //N rows and M columns
	T* mat;
	T* matAddress() const{
		return mat;
	}

public:
	//Restrict matrix size to no bigger than n*m = 10^8
	Matrix(int n, int m){
		N = n;
		M = m;
		mat = new T[n*m];
		memset(mat, 0, sizeof(T)*n*m); //Remove if every T has a self initiation technique and call that instead
	}
	~Matrix(){
		delete[] mat;
	}
	//Accessor
	int getN() const{
		return N;
	}
	int getM() const{
		return M;
	}
	//Fails if accessing outside of matrix
	T& getSafe(int n, int m) const{
		return mat[n*M+m];
	}
	//Change mat[i][j]
	T& get(int n, int m){
		return mat[n*M+m];
	}
	//Safe assignment
	Matrix<T>& operator=(const Matrix<T>& m){
		if(this != &m){
			N = m.getN();
			M = m.getM();
			delete[] mat;
			mat = new T[N*M];
			memcpy(mat, m.matAddress(), sizeof(T)*N*M);
		}
		return *this;
	}
	//Addition, fails if m has different dimension
	Matrix<T> operator+(const Matrix<T>& m){
		Matrix<T> ans(N, M);
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				ans.get(i, j) = (*this).getSafe(i, j) + m.getSafe(i, j);
		return ans;
	}
	Matrix<T> modAdd(const Matrix<T>& m, const T& MOD){
		Matrix<T> ans(N, M);
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				ans.get(i, j) = ((*this).getSafe(i, j) + m.getSafe(i, j))%MOD;
		return ans;
	}
	//Subtraction
	Matrix<T> operator-(const Matrix<T>& m){
		Matrix<T> ans(N, M);
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				ans.get(i, j) = (*this).getSafe(i, j) - m.getSafe(i, j);
		return ans;
	}
	Matrix<T> modSubtract(const Matrix<T>& m, const T& MOD){
		Matrix<T> ans(N, M);
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				ans.get(i, j) = ((*this).getSafe(i, j) - m.getSafe(i, j) + MOD)%MOD;
		return ans;
	}
	//Multiplication, make sure M = m.getN()
	Matrix<T> operator*(const Matrix<T>& m){
		Matrix<T> ans(N, m.getM());
		int tM = m.getM();
		for(int i = 0; i < N; i++)
			for(int j = 0; j < tM; j++)
				for(int k = 0; k < M; k++)
					ans.get(i, j) += (*this).getSafe(i, k) * m.getSafe(k, j);
		return ans;
	}
	Matrix<T> modMultiply(const Matrix<T>& m, const T& MOD){
		Matrix<T> ans(N, m.getM());
		int tM = m.getM();
		for(int i = 0; i < N; i++)
			for(int j = 0; j < tM; j++)
				for(int k = 0; k < M; k++)
					ans.get(i, j) = (ans.get(i, j) + ((*this).getSafe(i, k) * m.getSafe(k, j))%MOD)%MOD;
		return ans;
	}
	void operator+=(const Matrix<T>& m){
		(*this) = ((*this) + m);
	}
	void operator-=(const Matrix<T>& m){
		(*this) = ((*this) - m);
	}
	void operator*=(const Matrix<T>& m){
		(*this) = ((*this) * m);
	}
	//For debug
	//Print, change print technique if changed type T to something that's not int
	void print() const{
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				printf("%d%s", (*this).getSafe(i, j), j == M-1 ? "\n" : " ");
	}
	//Generates an identity matrix with N*N dimension
	static Matrix<T> ONE(const int& N){
		Matrix<T> ans(N, N);
		for(int i = 0; i < N; i++)
			ans.get(i, i) = 1; //Note that 1 is not always the ONE for T, works for any numerical data type (for example, Matrix of Matrices do not have 1, but ONE)
		return ans;
	}
	//To do
	//- Test with matrix exponentiation
	//- Modular multiplication, addition, and subtraction
	//- Echelon form? Reduced echelon form? Inverse?
};

template<class T> struct BinPow{
	static T pow(T base, long long p){
		T res = 1; //Change this if T has some different identity, for example, matrices use identity matrix
		while(p){
			if(p & 1)
				res *= base;
			base *= base;
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
	static T rpow(const T& base, long long p){
		if(p == 1) return base;
		if(!(p & 1)){
			T res = rpow(base, p >> 1);
			return (res * res);
		}
		return (rpow(base, p - 1) * base);
	}
	static T rmpow(const T& base, long long p, const long long& MOD){
		if(p == 1) return base%MOD;
		if(!(p & 1)){
			T res = rpow(base, p >> 1);
			return (res * res)%MOD;
		}
		return (rpow(base, p - 1) * base)%MOD;
	}
};

int main(){
	Matrix<int> LOL = Matrix<int>::ONE(10);
	BinPow<Matrix<int>>::rpow(LOL, 100).print();
	//LOL.print();
	return 0;
}