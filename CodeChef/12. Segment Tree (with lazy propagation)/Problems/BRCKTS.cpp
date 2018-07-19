#include <bits/stdc++.h>
using namespace std;

struct node{
	int sum, left;
	node(){
		sum = left = 0;
	}
	node(int a, int b){
		sum = a;
		left = b;
	}
	node operator+(const node& n) const{
		return node(sum+n.sum, min(left, sum+n.left));
	}
};

template<typename T> class SegTree{
private:
	T* sgt;
	T* arr;
	size_t N;

	T applyfunc(const T& a, const T& b){
		return b;
	}
	T queryfunc(const T& a, const T& b){
		return a + b;
	}
	
	T push(size_t node, size_t l, size_t r){
		if(l^r)
			sgt[node] = queryfunc(push(node<<1, l, (l+r)/2), push(node<<1|1, (l+r)/2+1, r));
		else
			sgt[node] = applyfunc(sgt[node], arr[l]);
		return sgt[node];
	}
	void update(size_t node, size_t l, size_t r, size_t pos, const T& value){
		if(l^r){
			size_t m = (l+r)/2;
			if(pos > m)
				update(node<<1|1, m+1, r, pos, value);
			else
				update(node<<1, l, m, pos, value);
			sgt[node] = queryfunc(sgt[node<<1], sgt[node<<1|1]);
		}else{
			sgt[node] = applyfunc(sgt[node], value);
			arr[pos] = applyfunc(arr[pos], value);
		}
	}
	T query(size_t nde, size_t ql, size_t qr, size_t l, size_t r){
		if(ql > r || qr < l || r < l)
			return node();
		if(!((ql^l) | (qr^r)))
			return sgt[nde];
		size_t m = (l+r)/2;
		return queryfunc(query(nde<<1, ql, min(qr, m), l, m), query(nde<<1|1, max(ql, m+1), qr, m+1, r));
	}

public:
	SegTree(size_t n){
		N = n;
		sgt = new T[(1<<((size_t)ceil(log2(N))+1))+5]();
		arr = new T[N+5]();
	}
	~SegTree(){
		delete[] sgt;
		delete[] arr;
	}
	T& operator[](size_t i){
		return arr[i];
	}
	void build(){
		push(1, 0, N-1);
	}
	void update(size_t pos, const T& value){
		if(pos < 0 || pos >= N) return;
		arr[pos] = applyfunc(arr[pos], value);
		update(1, 0, N-1, pos, value);
	}
	T query(size_t l, size_t r){
		return query(1, l, r, 0, N-1);
	}
};
	
int main(){
	int test = 1, N, Q, q;
	char c;
	while(~scanf("%d", &N)){
		c = getchar();
		SegTree<node> sgt(N);
		for(int i = 0; i < N; i++){
			c = getchar();
			if(c == '(')
				sgt[i] = node(1, 1);
			else
				sgt[i] = node(-1, -1);
		}
		sgt.build();
		printf("Test %d:\n", test++);
		scanf("%d", &Q);
		node temp;
		while(Q--){
			scanf("%d", &q);
			if(q){
				if(sgt[q-1].sum == 1)
					sgt.update(q-1, node(-1, -1));
				else
					sgt.update(q-1, node(1, 1));
			}else{
				temp = sgt.query(0, N-1);
				if(!temp.sum && !temp.left)
					printf("YES\n");
				else
					printf("NO\n");
			}
			/*for(int i = 0; i < N; i++)
				printf("%c", (sgt[i].sum == 1 ? '(' : ')'));
			printf("\n");*/
		}
	}
	return 0;
}
