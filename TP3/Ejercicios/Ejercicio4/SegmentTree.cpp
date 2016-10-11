#include <bits/stdc++.h>

using namespace std;

class SegmentTree{
	public:
		SegmentTree(){}
		void init(vector<int> &keys) {
			unsigned int t = 1;
			INF = 2000000;
			while(t < keys.size()*2) t*=2;
			v.resize(t);
			for(unsigned int i = 0; i < t; i++){
				v[i] = INF;
			}
			for(unsigned int i=0;i<keys.size();i++) {
				v[i+t/2] = keys[i];
			}
			for(unsigned int i=t-1;i>=1;i--) {
				v[i/2] = min(v[i/2],v[i]);
			}
		}
		int query(int first, int second) {
			return _query(1,0,v.size()/2,first,second);
		}
	private:
		int INF;
		vector<int> v;
		int _query(int node, int left, int right, int first, int second) {
			if(first <= left && second >= right)
				return v[node];
			if(second <= left || first >= right)
				return INF;
			return min(_query(node*2,left,(left+right)/2,first,second),
					   _query(node*2+1,(left+right)/2,right,first,second));
		}
};

int main(){
	
}
