#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

class node{
	public:
		bool visit;
		int x;
		int y;
		double dist_from;
		vector<node*> adj_list;
		// vector<double> dist_list;
		
		node(){this->x = 0, this->y = 0;}
		node(int x, int y){
			this->visit = false;
			this->dist_from = 1000000000001;
			this->x = x;
			this->y = y;
		}
		//node(const node& arg){
		//	this->x = arg.x;
		//	this->y = arg.y;
		//	this->visit = false;
		//	this->dist_from = 1000000000001;
		//	vector<node *> tmp(arg.adj_list.size());
		//	for(int i = 0; i < tmp.size(); i++){
		//		tmp[i] = arg.adj_list[i];
		//	}
		//	this->adj_list = tmp;
		//}
};

double dist(node loc1, node loc2){
	double tmpx = pow(loc1.x - loc2.x, 2);
	double tmpy = pow(loc1.y - loc2.y, 2);
	return sqrt(tmpx + tmpy);
}
void connect(vector<node> &graph){
	double tmp_dist;
	for(auto &it : graph){
		for(auto &it2 : graph){
			tmp_dist = dist(it, it2);
			if(3 > tmp_dist && tmp_dist != 0){
				it.adj_list.push_back(&it2);
			}
		}
	}
	for(int i = 0; i < graph.size(); i++){
		printf("(%d, %d) ->", graph[i].x, graph[i].y);
		for(auto &it : graph[i].adj_list){
			printf(" (%d, %d)", it->x, it->y);
		}
		printf("\n");
	}
}
struct compare{
	bool operator()(node *loc1, node *loc2){
		return loc1->dist_from > loc2->dist_from;
	}
};
double JUMP(vector<node> &graph, node &tmpGoal, int &n){
	priority_queue<node*, vector<node*>, compare> pq;
	pq.push(&graph[0]);
	for(auto &it : graph[0].adj_list){
		if(it->visit){
			continue;
		}
		it->dist_from = dist(graph[0], *it) + dist(*it, tmpGoal);
		pq.push(it);
	}
	graph[0].visit = true;
	pq.pop();

	node* tmp;
	double tmp_dist;
	while(!pq.empty()){
		while(pq.top()->visit){
			pq.pop();
		}
		tmp = pq.top();
		tmp->visit = true;
		printf("visited : (%d, %d)\n", tmp->x, tmp->y);
		if(tmp->x == tmpGoal.x && tmp->y == tmpGoal.y){
			printf("Answer in this goal : %lf\n", tmp->dist_from);
			tmp_dist = tmp->dist_from;
			for(auto &it : graph){
				it.visit = false;
				it.dist_from = 1000000000001;
			}
			return tmp_dist;
		}
		for(auto &it : tmp->adj_list){
			if(it->visit){
				continue;
			}
			tmp_dist = tmp->dist_from - dist(*tmp, tmpGoal) + dist(*tmp, *it) + dist(*it, tmpGoal);
			if(it->dist_from > tmp_dist){
				it->dist_from = tmp_dist;
			}
			pq.push(it);
		}
		pq.pop();
	}
	return -1;
}

int main(int argc, char** argv){
	int n, Goal_high;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d %d", &n, &Goal_high); // store input at inputstring
	// file scan
	int x, y;
	vector<node> graph;
	graph.push_back(node(0, 0));
	vector<node> goal;
	graph[0].dist_from = 0;
	double tmp_dist; 
	for(int i = 0; i < n; i++){
		fscanf(fr, "%d %d", &x, &y);
		if(y >= Goal_high){
			goal.push_back(node(x, y));
		}
		graph.push_back(node(x, y));	
	}
    fclose(fr); // file close

	connect(graph);
	double answer = 1000000000001;
	double tmpAnswer;
	printf("visit [0] : %d\n", graph[0].visit);
	for(auto &it : goal){
		printf("Goal location : (%d, %d)\n", it.x, it.y);
		tmpAnswer = JUMP(graph, it, n);
		answer = answer > tmpAnswer ? tmpAnswer : answer;
	}
	// file write
	FILE* fw = fopen(argv[2], "w"); // open output file
	fprintf(fw, "%d", (int)(answer + 0.5));
	fclose(fw); // file close		
	return 0;
}
