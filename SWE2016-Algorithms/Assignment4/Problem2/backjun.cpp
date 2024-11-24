#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>

using namespace std;
struct compare{
	bool operator()(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b){
		// {int, {int, int}} == {vertex_num, {adj_vertex_num, cost}}, 마지막 cost 기준 정렬
		return a.first > b.first;
	}
};
long long function(vector<vector<pair<int, int>>> &graph, int &n){
	bool *visit = new bool[n];
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,compare> index; // min priority queue
	for(int i = 0; i < n; i++){
		visit[i] = false;
	}

	visit[0] = true;
	for(auto it = graph[0].begin(); it < graph[0].end(); it++){
		if(it->second < 1000000 && it->second > -1000000 && !visit[it->first]){
			index.push(make_pair(it->second, make_pair(0, it->first)));
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
		for(auto it = graph[dest].begin(); it < graph[dest].end(); it++){
			if(it->second < 1000000 && it->second > -1000000 && !visit[it->first]){
				index.push(make_pair(it->second, make_pair(dest, it->first)));
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
	scanf("%d %d", &n, &m); // store input at inputstring	
	
	int v1, v2, cost;
	// int **graph = new int*[n];
	vector<vector<pair<int, int>>> graph(n);
	// {vertex, weight}

	for(int i = 0; i < m; i++){
		scanf("%d %d %d", &v1, &v2, &cost);
		graph[v1-1].push_back(make_pair(v2-1, cost));
		graph[v2-1].push_back(make_pair(v1-1, cost));
		// 숫자는 1부터 시작
	}

	long long answer = function(graph, n);
	printf("%lld", answer);	
	return 0;
}
