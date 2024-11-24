#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <math.h>

#include <unistd.h>

using namespace std;

struct compare{
	bool operator()(pair<int, double> v1, pair<int, double> v2){
		return v1.second < v2.second;
	}
};

class graph{
	public:
		int x;
		int y;
		int index;
		int bef_index;
		bool visit;
		double dist_from;
		multiset<pair<int, double>, compare> adj_list; // first = index, second = dist;
		graph(){
			x = 0; y = 0;
			index = 0; bef_index = 0;
			visit = false;
			dist_from = 1000000000001;
		}
};

double dist(graph v1, graph v2){
	double xdif = v1.x - v2.x;
	double ydif = v1.y - v2.y;
	return sqrt(xdif * xdif + ydif * ydif);
}

struct compare2{
	bool operator()(graph v1, graph v2){
		return v1.dist_from > v2.dist_from;
	}
};
void Astar(graph *g, int start_idx, int tmp_goal_idx, int &N, deque<int> &answer, bool isFront){
	priority_queue<graph, vector<graph>, compare2> pq;
	for(set<pair<int, double>, compare>::iterator it = g[start_idx].adj_list.begin(); it != g[start_idx].adj_list.end(); it++){
		g[it->first].dist_from = dist(g[start_idx], g[it->first]) + dist(g[it->first], g[tmp_goal_idx]);
		g[it->first].bef_index = start_idx;
		pq.push(g[it->first]);
	}
	g[start_idx].visit = true;
	graph* tmp;
	double tmp_dist;
	deque<int> tmpanswer;
	while(!pq.empty()){
		tmp = &g[pq.top().index];
		tmp->visit = true;
		if(tmp->x == g[tmp_goal_idx].x && tmp->y == g[tmp_goal_idx].y){
			while(tmp->bef_index != tmp->index){
				if(isFront){
					tmpanswer.push_front(tmp->index);
				}
				else{
					tmpanswer.push_back(tmp->index);
				}
				tmp = &g[tmp->bef_index];
			}
			for(deque<int>::iterator it = tmpanswer.begin(); isFront && it != tmpanswer.end(); it++){
				answer.push_back(*it);
			}
			for(deque<int>::reverse_iterator it = tmpanswer.rbegin(); !isFront && it != tmpanswer.rend(); it++){
				answer.push_front(*it);
			}
			for(int i = 0; i <= N; i++){
				g[i].visit = false;
				g[i].bef_index = 0;
				g[i].dist_from = 1000000000001;
			}
			return;
		}
		for(set<pair<int, double>, compare>::iterator it = tmp->adj_list.begin(); it != tmp->adj_list.end(); it++){
			if(g[it->first].visit){
				continue;
			}
			tmp_dist = tmp->dist_from - dist(*tmp, g[tmp_goal_idx]) + dist(*tmp, g[it->first]) + dist(g[it->first], g[tmp_goal_idx]);
			if(g[it->first].dist_from > tmp_dist){
				g[it->first].dist_from = tmp_dist;
				g[it->first].bef_index = tmp->index;
			}
			pq.push(g[it->first]);
		}
		while(g[pq.top().index].visit){
			pq.pop();
		}
	}
}

vector<int> Stopover(graph *g, deque<int> &left_Karr, int &N){
	int front_idx = 1, back_idx = N;
	deque<int> front_answer;
	deque<int> back_answer;
	int tmp_goal_front_idx;
	int tmp_goal_back_idx;
	double tmp_value;
	double min = 1000000000001;
	int i;
	while(!left_Karr.empty()){
		tmp_goal_front_idx = 0;
		min = 1000000000001;
		for(i = 0; i < left_Karr.size(); i++){
			tmp_value = dist(g[front_idx], g[left_Karr[i]]);
			if(min > tmp_value){
				min = tmp_value;
				tmp_goal_front_idx = left_Karr[i];
			}
		}
		Astar(g, front_idx, tmp_goal_front_idx, N, front_answer, true);
		front_idx = tmp_goal_front_idx;
		for(deque<int>::iterator it = left_Karr.begin(); it != left_Karr.end(); it++){
			if(*it == tmp_goal_front_idx){
				left_Karr.erase(it);
				break;
			}
		}
		if(left_Karr.empty()){
			break;
		}

		tmp_goal_back_idx = 0;
		min = 1000000000001;
		for(i = 0; i < left_Karr.size(); i++){
			tmp_value = dist(g[back_idx], g[left_Karr[i]]);
			if(min > tmp_value){
				min = tmp_value;
				tmp_goal_back_idx = left_Karr[i];
			}
		}
		Astar(g, back_idx, tmp_goal_back_idx, N, back_answer, false);
		back_idx = tmp_goal_back_idx;
		for(deque<int>::iterator it = left_Karr.begin(); it != left_Karr.end(); it++){
			if(*it == tmp_goal_back_idx){
				left_Karr.erase(it);
				break;
			}	
		}
		if(left_Karr.empty()){
			break;
		}
	}
	Astar(g, tmp_goal_front_idx, tmp_goal_back_idx, N, front_answer, true);

	vector<int> ret;
	for(deque<int>::iterator it = front_answer.begin(); it != front_answer.end(); it++){
		ret.push_back(*it);
	}
	for(deque<int>::iterator it = back_answer.begin(); it != back_answer.end(); it++){
		ret.push_back(*it);
	}
	for(vector<int>::iterator it = ret.begin() + 1; it != ret.end(); it++){
		if(*(it - 1) == *(it)){
			ret.erase(it);
		}
	}
	return ret;
}

int main(int argc, char** argv){
	FILE * fr = fopen(argv[1], "r");
	int N, M, K;
	fscanf(fr, "%d %d %d", &N, &M, &K);
	
	int i;
	double x, y;
	int v1, v2;
	
	graph *g = new graph[N+1];
	deque<int> left_Karr(K);

	for(i = 1; i <= N; i++){
		fscanf(fr, "%lf %lf", &x, &y); // input about position
		g[i].x = x;	g[i].y = y;
		g[i].index = i;
	}
	for(i = 0; i < M; i++){
		fscanf(fr, "%d %d", &v1, &v2); // input about edge
		g[v1].adj_list.insert(make_pair(v2, dist(g[v1], g[v2])));
		g[v2].adj_list.insert(make_pair(v1, dist(g[v1], g[v2])));
	}
	for(i = 0; i < K; i++){
		fscanf(fr, "%d", &left_Karr[i]);
	}
	fclose(fr);
	
	// **********
	for(i = 1; i <= N; i++){
		printf("index : %d, (%d, %d)\tadj : ", i, g[i].x, g[i].y);
		for(set<pair<int, double>,compare>::iterator it = g[i].adj_list.begin(); it != g[i].adj_list.end(); it++){
			printf("%d ", it->first);
		}
		printf("\n");
	}
	vector<int> answer = Stopover(g, left_Karr, N);
	// **********

	FILE * fw = fopen(argv[2], "w");
	// file write
	fprintf(fw, "%d\n", (int)answer.size());
	for(int i = 0; i < answer.size(); i++){
		fprintf(fw, "%d ", answer[i]);
	}
	fclose(fw);
	return 0;
}
