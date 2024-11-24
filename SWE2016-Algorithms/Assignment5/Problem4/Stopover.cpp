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

struct compare2{
	bool operator()(graph *v1, graph *v2){
		return v1->dist_from > v2->dist_from;
	}
};

double dist(graph v1, graph v2){
	double xdif = v1.x - v2.x;
	double ydif = v1.y - v2.y;
	return sqrt(xdif * xdif + ydif * ydif);
}

void Astar(graph *g, int start_idx, int tmp_goal_idx, int &N, deque<int> &answer, bool isFront){
	priority_queue<graph*, vector<graph*>, compare2> pq;
	for(set<pair<int, double>, compare>::iterator it = g[start_idx].adj_list.begin(); it != g[start_idx].adj_list.end(); it++){
		g[it->first].dist_from = dist(g[start_idx], g[it->first]) + dist(g[it->first], g[tmp_goal_idx]);
		g[it->first].bef_index = start_idx;
		pq.push(&g[it->first]);
	}
	g[start_idx].visit = true;
	graph* tmp;
	double tmp_dist;
	deque<int> tmpanswer;
	while(!pq.empty()){
		tmp = pq.top();
		tmp->visit = true;
		if(tmp->x == g[tmp_goal_idx].x && tmp->y == g[tmp_goal_idx].y){ // when tmp is equal to tmp_goal
			while(tmp->bef_index != tmp->index){
				if(isFront){ // if front answer : push front to tmp_answer
					tmpanswer.push_front(tmp->index);
				}
				else{ // if back answer : push back to tmp_answer
					tmpanswer.push_back(tmp->index);
				}
				tmp = &g[tmp->bef_index];
			}
			for(deque<int>::iterator it = tmpanswer.begin(); isFront && it != tmpanswer.end(); it++){ // if front_answer : front_answer + tmp_answer
				answer.push_back(*it);
			}
			for(deque<int>::reverse_iterator it = tmpanswer.rbegin(); !isFront && it != tmpanswer.rend(); it++){ // if back answer : tmp_answer + back_answer
				answer.push_front(*it);
			}
			for(int i = 0; i <= N; i++){ // re initialize
				g[i].visit = false;
				g[i].bef_index = 0;
				g[i].dist_from = 1000000000001;
			}
			return; // exit this function
		}

		for(set<pair<int, double>, compare>::iterator it = tmp->adj_list.begin(); it != tmp->adj_list.end(); it++){ // tmp's adj_list
			if(g[it->first].visit){
				continue;
			}
			tmp_dist = tmp->dist_from - dist(*tmp, g[tmp_goal_idx]) + dist(*tmp, g[it->first]) + dist(g[it->first], g[tmp_goal_idx]);
			if(g[it->first].dist_from > tmp_dist){
				g[it->first].dist_from = tmp_dist;
				g[it->first].bef_index = tmp->index;
			}
			pq.push(&g[it->first]);
		}
		while(pq.top()->visit){
			pq.pop();
		}
	}
}

vector<int> Stopover(graph *g, deque<int> &left_Karr, int &N){
	int front_idx = 1, back_idx = N;
	deque<int> front_answer;	int tmp_goal_front_idx;
	deque<int> back_answer;		int tmp_goal_back_idx;
	double tmp_value;
	double min;
	
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
	Astar(g, tmp_goal_front_idx, tmp_goal_back_idx, N, front_answer, true); // connect Last of front vector -> First of back vector

	vector<int> answer;
	for(deque<int>::iterator it = front_answer.begin(); it != front_answer.end(); it++){
		answer.push_back(*it);
	}
	for(deque<int>::iterator it = back_answer.begin(); it != back_answer.end(); it++){
		answer.push_back(*it);
	}
	for(vector<int>::iterator it = answer.begin() + 1; it != answer.end(); it++){
		if(*(it - 1) == *(it)){ // erase duplicated vertex
			answer.erase(it);
		}
	}
	return answer;
}

int main(int argc, char** argv){
	// file read
	FILE * fr = fopen(argv[1], "r");
	int N, M, K;
	fscanf(fr, "%d %d %d", &N, &M, &K);
	
	int i;
	double x, y;
	int v1, v2;
	graph *g = new graph[N+1]; // index 0 ~ N, using index 1 ~ N
	deque<int> left_Karr(K); // must visit vertices

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
	// file read close
	
	// **********
	vector<int> answer = Stopover(g, left_Karr, N);
	// **********
	
	// file write
	FILE * fw = fopen(argv[2], "w");
	fprintf(fw, "%d\n", (int)answer.size());
	fprintf(fw, "%d", answer[0]);
	for(int i = 1; i < answer.size(); i++){
		fprintf(fw, " %d", answer[i]);
	}
	fclose(fw);
	// file write close
	return 0;
}
