/*
 * deadLockDetect.cpp
 *
 *  Created on: 2019年8月31日
 *      Author: wen
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

void dFSCheck(vector<vector<int> >&wfg, int vertex, vector<int>& visit, vector<int>& father){
	int edge_size = wfg[vertex].size();
	visit[vertex] = 1;
	for(int i = 0; i < edge_size; i++){
		int node = wfg[vertex][i];
	        if(node != vertex)
	        {
	        	cout << vertex << " " << node << " " << vertex << " " << visit[node] << " "<< father[vertex] << endl;
	            if(visit[node] == 1 && node == father[vertex])
	            {
	                cout<<"false: ";
	            }
	            else if(visit[node] == 0)
	            {
	                father[node] = vertex;
	                dFSCheck(wfg, node, visit, father);
	            }
	        }
	}
	visit[vertex] = 2;
}

bool TopSort(vector<vector<int>> &wfg, int n, vector<int> &inDegree) {
	int num = 0;
	//used for topsort
	queue<int> zero_queue;
	for (int i = 0; i < n; i++)
		//push the node which indegree is 0
		if (inDegree[i] == 0)
			zero_queue.push(i);
	while (!zero_queue.empty()) {
		int u = zero_queue.front();
		zero_queue.pop();
		for (int i = 0; i < wfg[u].size(); i++) {
			int v = wfg[u][i];
			inDegree[v]--;
			if (inDegree[v] == 0)
				zero_queue.push(v);
		}
		wfg[u].clear();
		num++;
	}
	//if topsort success, it is non-circle, otherwise it has circles
	if (num == n)
		return true;
	else
		return false;
}

int main(){
	int len;
	map<int, vector<int> > resources;
	vector<vector<int> > wfg;

	cin >> len;
	for(int i = 0; i<len; i++){
		int proc, res;
		cin >> proc >> res;
		resources[res].push_back(proc);
	}

	for(map<int, vector<int> >::iterator it = resources.begin(); it!=resources.end(); it++){
		vector<int>& procs = it->second;
		for(int i = 1; i<procs.size(); i++){
			if(wfg.size() < procs[i]) wfg.resize(procs[i]+1);
			wfg[procs[i]].push_back(procs[i-1]);
		}
	}
	vector<int> visit(wfg.size(), 0);
	vector<int> father(wfg.size(), -1);
	vector<int> inDegree(wfg.size());
	for(int i = 0; i < wfg.size(); i++){
		for(int j = 0; j<wfg[i].size(); j++)
			++inDegree[j];
	}

//	for(int i = 0; i < wfg.size(); i++){
//		if(visit[i] == 0)
//			dFSCheck(wfg, i, visit, father);
//	}

	if(TopSort(wfg, wfg.size(), inDegree))
		cout << "good";
	else
		cout << "bad";
	cout << endl;


}


