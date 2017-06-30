#include <bits/stdc++.h>
using namespace std;

class Trie{
private:
	struct node{
		node *leaves;
		int *count;
		int size;
		node(){
			leaves = NULL;
			count = NULL;
		}
		~node(){
			if(leaves != NULL)
				delete[] leaves;
			if(count != NULL)
				delete[] count;
		}
		void allocate(int n){
			if(leaves != NULL)
				delete[] leaves;
			if(count != NULL)
				delete[] count;
			size = n;
			leaves = new node[size]();
			count = new int[size]();
		}
		//Customize insert, query for different needs
		void insert(int i){
			//Make sure allocate before insert
			if(leaves[i].leaves == NULL)
				leaves[i].allocate(size);
			count[i]++;
		}
		int query(int i){
			//Test for unallocated
			if(count != NULL && i < size)
				return count[i];
			return 0;
		}
	};
	node *root;
	int N;

public:
	Trie(int n){
		N = n; //Number of children per node
		root = new node;
		root->allocate(N);
	}
	~Trie(){
		delete root;
	}
	//Customize insert and query for different needs
	void insert(int n){
		node *cur = root;
		for(int i = 20; i >= 0; i--){
			int j = n & (1 << i) ? 1 : 0;
			cur->insert(j);
			cur = &(cur->leaves[j]);
		}
	}
	int query(int n, int K){
		int ans = 0;
		node *cur = root;
		for(int i = 20; i >= 0 && cur->leaves != NULL; i--){
			bool p = n & (1 << i);
			bool q = K & (1 << i);
			if(q)
				if(p){
					ans += cur->query(1);
					cur = &(cur->leaves[0]);
				}else{
					ans += cur->query(0);
					cur = &(cur->leaves[1]);
				}
			else
				if(p) cur = &(cur->leaves[1]);
				else cur = &(cur->leaves[0]);
		}
		return ans;
	}
};

int main(){
	//Enter code here
	return 0;
}