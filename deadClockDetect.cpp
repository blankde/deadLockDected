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

bool TopSort(vector<vector<int>> &G, int n, vector<int> &inDegree) {
	/*
	*	param
	*	G：	邻接表
	*	n：	顶点数
	*	InDegree：	记录顶点的入度
	*/
	int num = 0;				//记录加入拓扑排序的顶点数
	queue<int> q;
	for (int i = 0; i < n; i++)
		if (inDegree[i] == 0)
			q.push(i);		//将所有入度为0的顶点入队
	while (!q.empty()) {
		int u = q.front();		//取队首顶点u
		q.pop();
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];		//u的后继节点
			inDegree[v]--;			//v的入度减1
			if (inDegree[v] == 0)		//顶点v的入度减为0则入队
				q.push(v);
		}
		G[u].clear();			//清空顶点u的所有出边
		num++;
	}
	if (num == n)				//加入拓扑序列的顶点数为n，说明拓扑排序成功，否则，失败
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


