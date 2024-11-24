#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>

using namespace std;
struct compare{
	bool operator()(pair<int, pair<int, int> > &a, pair<int, pair<int, int> > &b){
		// {int, {int, int}} == {vertex_num, {adj_vertex_num, cost}}, 마지막 cost 기준 정렬
		return a.first > b.first;
	}
};
long long function(vector<vector<pair<int, int> > > &graph, int &n){
	bool *visit = new bool[n];
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, compare> index; // min priority queue
	for(int i = 0; i < n; i++){
		visit[i] = false;
	}

	visit[0] = true;
	for(int i = 0; i < graph[0].size(); i++){
		if(graph[0][i].second < 1000000 && graph[0][i].second > -1000000 && !visit[graph[0][i].first]){
			index.push(make_pair(graph[0][i].second, make_pair(0, graph[0][i].first)));
		}
	}
	long long sum_cost = 0;
	int esc_key = 0;
	int src, dest;
	long long cost;
	while(true){
		while(visit[index.top().second.second]){
			index.pop();
		}
		src = index.top().second.first;
		dest = index.top().second.second;
		cost = index.top().first;
		index.pop();

		sum_cost += cost;
		visit[dest] = true;
		for(int i = 0; i < graph[dest].size(); i++){
			if(graph[dest][i].second < 1000000 && graph[dest][i].second > -1000000 && !visit[graph[dest][i].first]){
				index.push(make_pair(graph[dest][i].second, make_pair(dest, graph[dest][i].first)));
			}
		}

		esc_key = 0;
		for(int i = 0; i < n; i++){
			if(visit[i]){
				esc_key++;
			}
		}
		if(esc_key == n){
			break;
		}
	}
	return sum_cost;
}

int main(int argc, char** argv){
	int n, m;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d %d", &n, &m); // store input at inputstring	
	
	int v1, v2, cost;
	vector<vector<pair<int, int> > > graph(n);
	// {vertex, weight}

	for(int i = 0; i < m; i++){
		fscanf(fr, "%d %d %d", &v1, &v2, &cost);
		graph[v1-1].push_back(make_pair(v2-1, cost));
		graph[v2-1].push_back(make_pair(v1-1, cost));
		// 숫자는 1부터 시작
	}

    fclose(fr); // file close

	long long answer = function(graph, n);
	// file write
	FILE* fw = fopen(argv[2], "w"); // open output file
	
	fprintf(fw, "%lld", answer);
    
	fclose(fw); // file close	
	return 0;
}
