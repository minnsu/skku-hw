#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>

// input
// 3 3
// 1 2 1
// 1 3 2
// 2 3 3
// -> a b c => a, b가 연결됨 and cost == c
// output
// 3

using namespace std;
struct compare{
	bool operator()(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b){
		// {int, {int, int}} == {vertex_num, {adj_vertex_num, cost}}, 마지막 cost 기준 정렬
		return a.second.second > b.second.second;
	}
};
int function(int **graph, int &n){
	int *visit = new int[n];
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,compare> index; // min priority queue

	visit[0] = 1;
	for(int i = 0; i < n; i++){
		if(graph[0][i] < 1000000 && graph[0][i] > -1000000 && visit[i] != 1){
			index.push(make_pair(0, make_pair(i, graph[0][i])));
		}
	}
	int sum_cost = 0;
	int esc_key = 0;
	int src, dest, cost;
	while(!index.empty()){
		while(visit[index.top().second.first] == 1){
			index.pop();
		}
		src = index.top().first;
		dest = index.top().second.first;
		cost = index.top().second.second;
		index.pop();

		sum_cost += cost;
		visit[dest] = 1;
		for(int i = 0; i < n; i++){
			if(graph[dest][i] < 1000000 && graph[dest][i] > -1000000 && visit[i] != 1){
				index.push(make_pair(dest, make_pair(i, graph[dest][i])));
			}
		}

		esc_key = 0;
		for(int i = 0; i < n; i++){
			if(visit[i] == 1){
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
	int **graph = new int*[n];
	for(int i = 0; i < n; i++){
		graph[i] = new int[n];
		for(int j = 0; j < n; j++){ // initialize
			graph[i][j] = 1000001;
		}
	}

	for(int i = 0; i < m; i++){
		fscanf(fr, "%d %d %d", &v1, &v2, &cost);
		graph[v1-1][v2-1] = cost;
		graph[v2-1][v1-1] = cost;
		// 숫자는 1부터 시작
	}

    fclose(fr); // file close

	int answer = function(graph, n);
	// file write
	FILE* fw = fopen(argv[2], "w"); // open output file
	
	fprintf(fw, "%d", answer);
    
	fclose(fw); // file close	
	return 0;
}
