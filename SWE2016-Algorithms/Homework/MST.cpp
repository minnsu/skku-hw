#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <queue>

using namespace std;

template <typename WT>
class Graph{
	public:
		int nV, nE;

		vector<pair<int, WT>> *edges;

		Graph(){}
		Graph(const char *_filename){
			FILE *input = fopen(_filename, "r");
			fscanf(input, "%d %d", &nV, &nE);
			edges = new vector<pair<int, WT>> [nV];
			for(int i = 0; i < nE; i++){
				int vA, vB; double weight;
				fscanf(input, "%d %d %lf", &vA, &vB, &weight);
				vA--; vB--;
				edges[vA].push_back(make_pair(vB, (WT) weight));
				edges[vB].push_back(make_pair(vA, (WT) weight));
			}
			fclose(input);	
		}
};

template<typename WT>
WT Prim(Graph<WT> &_g){
	bool *visit = new bool[_g.nV];
	int *parent = new int[_g.nV];
	
	WT *dist = new WT[_g.nV];

	for(int i = 0; i < _g.nV; i++){
		visit[i] = false;
		parent[i] = -1;
		dist[i] = (WT) 999999999;

	}

	WT ret = (WT) 0;

	int rootIdx = 0;
	
	dist[rootIdx] = (WT) 0;
	parent[rootIdx] = 0;
	
	priority_queue<pair<WT, int>, vector<pair<WT, int>>, greater<pair<WT, int>> > pq;
	pq.push(make_pair((WT) 0, rootIdx));

	for(;;){
		if(pq.empty()){ break;}
		pair<WT, int> x = pq.top(); pq.pop();

		if(visit[x.second]){ continue; }
		
		visit[x.second] = true;
		ret += x.first;

		for(int i = 0; i < _g.edges[x.second].size(); i++){
			int idx = _g.edges[x.second][i].first;
			WT w = _g.edges[x.second][i].second;
			if( !visit[idx] && w < dist[idx]){
				pq.push(make_pair(w, idx));
				parent[idx] = x.second;
				dist[idx] = w;
			}
		}
	}
	printf("Idx\tV\tDist\tParent\n");
	for(int i = 0; i < _g.nV; i++){
		printf("%2d\t%d\t%.2lf\t%2d\n", i+1, (int) visit[i], (double)dist[i], parent[i]);
	}
	delete[] visit;
	delete[] parent;
	delete[] dist;
	return ret;
}

class Disjoint_Set{
	public:
		int n;
		int *parent;
		int *height;

		Disjoint_Set() {}
		Disjoint_Set(int _n){
			this->n = _n;
			parent = new int[n];
			for(int i = 0; i < n; i++){
				parent[i] = i;
				height[i] = 0;
			}
		}

		int Find_Set(int _x){
			while(parent[_x] != _x){
				_x = parent[_x];
			}
			return _x;
		}

		bool Union_Set(int _x, int _y){
			_x = Find_Set(_x);
			_y = Find_Set(_y);

			if(_x == _y){return false;}

			if(height[_x] == height[_y]){
				parent[_y] = _x;
				height[_x]++;
			}
			else if(height[_x] > height[_y]){
				parent[_y] = _x;
			}
			else{
				parent[_x] = _y;
			}
			return true;
		}
};

template<typename WT>
WT Kruskal(Graph<WT> &_g){
	vector< pair<WT, pair<int, int>> > d;
	for(int i = 0; i < _g.nV; i++){
		for(int j = 0; j < _g.edges[i].size(); j++){
			// vertex i and _g.edges[i][j].first with weight of _g.edges[i][j].second
			if(i < _g.edges[i][j].first){
				d.push_back(make_pair(_g.edges[i][j].second, make_pair(i, _g.edges[i][j].first)) );
			}
		}
	}
	sort(d.begin(), d.end());

	Disjoint_Set s(_g.nV);

	WT ret = (WT) 0;

	for(int i = 0; i < d.size(); i++){
		int x = d[i].second.first;
		int y = d[i].second.second;
		WT w = d[i].first;
		
		if(s.Find_Set(x) != s.Find_Set(y)){
			printf("%2d - %2d (Weight : %.2lf)\n", x+1, y+1, (double) w);
			ret += w;
			s.Union_Set(x, y);
		}
	}
	return ret;
}

int main(int argc, char **argv){
	
	Graph<double> g(argv[1]);
	double cost_prim = Prim<double>(g);
	printf("Cost (Prim) = %lf\n", cost_prim);
	printf("\n");

	double cost_kruskal = Kruskal<double>(g);
	printf("Cost (Kruskal) = %lf\n", cost_kruskal);
	printf("\n");
	return 0;
}
