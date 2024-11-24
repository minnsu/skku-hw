#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

class task{
	public:
		int inDegree;
		int taskTime;
		int criticalTime;
		int index;
		int previousTask;
		vector<int> child;
};

struct compare{
	bool operator()(task *t1, task *t2){
		return t1->inDegree > t2->inDegree;
	}
};

unsigned long long CriticalTime(task *tasks, int N){
	unsigned long long answer = 0;
	priority_queue<task*, deque<task*>, compare> pq;
	queue<task*, deque<task*> > q;
	
	int i;
	for(i = 0; i < N; i++){
		pq.push(&tasks[i]);
	}
	
	task* tmp;
	//unsigned long long tmpTime;
	int tmpSize;
	while(!pq.empty()){
		if(pq.top()->inDegree != 0){
			return 0;
		}
		while(!pq.empty() && pq.top()->inDegree == 0){
			printf("index : %d, inDegree : %d\n", pq.top()->index, pq.top()->inDegree);
			q.push(pq.top());
			pq.pop();
		}
		while(!q.empty()){
			tmp = q.front();
			//tmpTime = tmp->criticalTime + tmp->taskTime;
			//if(tmpTime > tmp->criticalTime){
			tmp->criticalTime = tmp->criticalTime + tmp->taskTime;
			//}
			tmpSize = tmp->child.size();
			for(i = 0; i < tmpSize; i++){
				tasks[tmp->child[i]].inDegree--;
				if(tasks[tmp->child[i]].criticalTime < tmp->criticalTime){
					tasks[tmp->child[i]].previousTask = tmp->index;
					tasks[tmp->child[i]].criticalTime = tmp->criticalTime;
				}
				//tasks[tmp->child[i]].criticalTime = tmp->criticalTime;
			}
			q.pop();
		}
	}
	for(i = 0; i < N; i++){
		answer = answer < tasks[i].criticalTime ? tasks[i].criticalTime : answer;
	}
	return answer;
}

int main(int argc, char** argv){
	
	int N, M;
	int i;

	FILE * fr = fopen(argv[1], "r");
	fscanf(fr, "%d %d", &N, &M);

	N = N + 1;
	task *tasks = new task[N];
	int a, b;

	for(i = 1; i < N; i++){
		fscanf(fr, "%d", &tasks[i].taskTime);
		tasks[i].index = i;
	}
	for(i = 0; i < M; i++){
		fscanf(fr, "%d %d", &a, &b);
		tasks[a].child.push_back(b);
		tasks[b].inDegree++;
	}
	fclose(fr);
	
	// **********
	unsigned long long answer = CriticalTime(tasks, N);
	// **********
	
	FILE * fw = fopen(argv[2], "w");
	if(answer == 0){
		fprintf(fw, "%d\n", -1);
	}
	else{
		fprintf(fw, "%llu\n", answer);
	}
	fclose(fw);
	return 0;
}
