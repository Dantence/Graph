#include<iostream>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
typedef char VertexType;
typedef int EdgeType;
const int MAXVEX = 100;
const int INF = 65535;
bool visited[MAXVEX];				//访问标志数组
struct Edge
{
	int begin;
	int end;
	int weight;
};
int Find(int* pre, int f)
{
	while (pre[f] != f)
	{
		f = pre[f];
	}
	return f;
}
bool cmp(Edge a, Edge b)
{
	return a.weight < b.weight;
}
template <typename T> class MGraph
{
public:
	MGraph();
	void PrintMGraph();						//打印邻接矩阵
	void DFS(int i);						//深度优先算法
	void DFSTraverse();						//深度优先遍历
	void BFSTraverse();						//广度优先遍历
	void MiniSpanTree_Prim();				//最小生成树之普里姆算法
	void MiniSpanTree_Kruskal();			//最小生成树之克鲁斯卡尔算法
	void Dijkstra(int begin,int end);		//最短路径之迪杰斯特拉算法
	void Floyd(int begin,int end);			//最短路径之弗洛伊德算法
private:
	T vexs[MAXVEX];							//顶点表
	int arc[MAXVEX][MAXVEX];				//邻接矩阵，可看作边表
	int numVertexes, numEdges;				//图中当前的顶点数和边数
};
template <typename T>MGraph<T>:: MGraph()
{
	int i, j, k, w;
	cout << "输入顶点数和边数" << endl;
	cin >> this->numVertexes >> this->numEdges;		//输入顶点数和边数
	for (i = 0; i < this->numVertexes; i++)		//读入顶点信息，建立顶点表
	{
		cin >> this->vexs[i];
	}
	for (i = 0; i < this->numVertexes; i++)
	{
		for (j = 0; j < this->numVertexes; j++)
		{
			if (i == j)
			{
				this->arc[i][j] = 0;
			}
			else
			{
				this->arc[i][j] = INF;					//邻接矩阵初始化
			}
		}
	}
	int cnt = 1;
	for (k = 0; k < this->numEdges; k++)
	{
		cout << "输入第"<<cnt<<"条边(Vi,Vj)上的下标i，下标j和权" << endl;
		cin >> i >> j >> w;
		this->arc[i][j] = w;
		this->arc[j][i] = this->arc[i][j];			//无向图对称矩阵
		cnt++;
	}
}
template <typename T>void MGraph<T>::PrintMGraph()
{
	int i, j;
	for (i = 0; i < this->numVertexes; i++)
	{
		for (j = 0; j < this->numVertexes; j++)
		{
			cout << this->arc[i][j] << "    ";
		}
		cout << endl;
	}
}
template <typename T>void MGraph<T>::DFS(int i)
{
	int j;
	visited[i] = true;
	cout << this->vexs[i] << "-->";
	for (j = 0; j < this->numVertexes; j++)
	{
		if (this->arc[i][j] != INF && !visited[j])
		{
			DFS(j);
		}
	}
}
template <typename T>void MGraph<T>::DFSTraverse()
{
	int i;
	for (i = 0; i < this->numVertexes; i++)
	{
		visited[i] = false;					//初始所有顶点都是未访问状态
	}
	for (i = 0; i < this->numVertexes; i++)
	{
		if (!visited[i])					//若是连通图，只会执行一次
		{
			DFS(i);
		}
	}
}
//每遍历一个结点，把其所有子结点入队
template <typename T>void MGraph<T>::BFSTraverse()
{
	queue<int>q;
	int i, j;
	for (i = 0; i < this->numVertexes; i++)
	{
		visited[i] = false;
	}
	for (i = 0; i < this->numVertexes; i++)		//对每个顶点循环
	{
		if (!visited[i])						//若是连通图，只会执行一次
		{
			visited[i] = true;
			cout << this->vexs[i] << "-->";
			q.push(i);							//将此顶点入队
			while (!q.empty())					//若当前队列不为空
			{
				q.pop();						//将队中元素出队
				for (j = 0; j < this->numVertexes; j++)
				{
					if (this->arc[i][j] != INF && !visited[j])
					{
						visited[j] = true;
						cout << this->vexs[j] << "-->";
						q.push(j);
					}
				}
			}
		}
	}
}
template <typename T>void MGraph<T>::MiniSpanTree_Prim()
{
	int min, i, j, k, sum = 0;
	int adjvex[MAXVEX];					//数组下标表示最小生成树的某个顶点，值表示与该顶点相连的最小权值边的顶点
	int lowcost[MAXVEX];				//数组下标表示某个顶点，值表示当前与该点相连的边的最小权值
	lowcost[0] = 0;						//初始化第一个权值为0，即顶点0加入生成树（lowcost的值为0就代表此下标的顶点已经加入生成树，值为INF表示当前的u最小生成树与此下标的顶点没有边相连）
	adjvex[0] = 0;						//初始化第一个顶点下标为0
	for (i = 1; i < this->numVertexes; i++)		//循环除下标为0外的全部顶点
	{
		lowcost[i] = this->arc[0][i];	//将顶点0与之相连的边的权值存入数组
		adjvex[i] = 0;					//初始化都为顶点0的下标
	}
	cout << "最小生成树的各边为：" << endl;
	for (i = 1; i < this->numVertexes; i++)
	{
		min = INF;
		j = 1;
		k = 0;
		while (j < this->numVertexes)
		{
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		sum += min;
		cout << "(" << vexs[adjvex[k]] << "," << vexs[k] << ")  " << min << endl;		//打印当前顶点中权值最小边
		lowcost[k] = 0;										//将当前顶点权值设为0，表示已经加入最小生成树中
		for (j = 1; j < this->numVertexes; j++)
		{
			if (lowcost[j] != 0 && this->arc[k][j] < lowcost[j])	//若下标为k顶点各边权值小于此前这些顶点未被加入生成树的权值
			{
				lowcost[j] = this->arc[k][j];
				adjvex[j] = k;
			}
		}
	}
	cout << "最小权值和为：" << sum << endl;
}
//并查集：用于判定某条边与目前的最小生成树是否联通。该最小生成树的首个元素称为代表元，可以理解成根结点
//因此，我们在建立树的时候有意识地将每条新边的两个结点中的一个结点作为某一个结点的前驱
//如果一条新边，它的两个结点的代表元相等，说明它们在同一棵树中，那么此边与目前最小生成树联通，应舍去
//主要思想：定义一个pre数组，pre[i]表示i点的前驱，如果pre[i]==i，则i为代表元，pre[n]=m表示将n的前驱设置成m
//Kruskal的主要步骤:
//1、先将邻接矩阵转换为边集数组，即一个edge结构中含有一条边的起始点、终点以及权值
//2、再将所有边的权值从小到大排序
//3、所有结点的pre数组初始化为其本身，所有结点初始状态都为代表元
//4、按照权值从小到大的顺序，依次遍历所有边，判断一条边的两个结点的代表元是否相同，如果相同，则遍历下一个结点
//如果不同，则将其中某一个结点的代表元设置为另一个结点的代表元的前驱，表示该边加入最小生成树中
template <typename T>void MGraph<T>::MiniSpanTree_Kruskal()
{
	Edge *edge = new Edge[this->numEdges];
	int cnt = 0;
	for (int i = 0; i < this->numVertexes; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (this->arc[i][j] != INF)
			{
				edge[cnt].begin = i;
				edge[cnt].end = j;
				edge[cnt].weight = arc[i][j];
				cnt++;
			}
		}
	}
	sort(edge, edge + this->numEdges,cmp);
	int i, n, m, sum = 0;
	int *pre = new int[numVertexes];
	for (i = 0; i < numVertexes; i++)
	{
		pre[i] = i;
	}
	for (i = 0; i < this->numEdges; i++)
	{
		n = Find(pre, edge[i].begin); 
		m = Find(pre, edge[i].end);	   
		if (n != m)
		{
			pre[m] = n;
			cout << "(" << vexs[edge[i].begin] << "," << vexs[edge[i].end] << ")  " << edge[i].weight << endl;
			sum += edge[i].weight;
		}
	}
	cout << "最小权值和为:" << sum << endl;
}
//迪杰斯特拉算法，用于求解最短路径的算法之一，采取一种贪心的策略，定义一个dis数组来保存起始点
//到各个顶点目前的最短距离；定义一个path数组，用于记录已经找到了最短路径的顶点；定义一个visited
//数组，用于表示一个顶点到起始点是否已经求得了最短路径；
//初始化：visited数组全为0，表示所有顶点都没有求得最短路径
//dis数组初始化为所有与起始点直接相连的顶点的权值，如果没有边则为INF
//path数组全为0，表示现在没有任何路径
//从起始点开始，把起始点的访问标记变为1，dis[begin]为0（起始点到本身的距离为0）
//然后找到与起始点相连的最小权值的顶点，找到后把该顶点的访问标记变为1
//接下来是关键步骤：遍历与新加入的顶点直接相连的未访问的顶点，如果从新加入
//的顶点到那些顶点的距离小于dis数组中相应下标的值（因为之前的dis已经是最小值了），那么就更新dis数组中的值
//然后又从dis中找出最小值，重复以上步骤，直到path数组中包含全部顶点为止
template <typename T>void MGraph<T>::Dijkstra(int begin,int end)
{
	int* dis = new int[this->numVertexes];
	int* path = new int[this->numVertexes];
	int v, w, k, min;
	int* visited = new int[this->numVertexes];
	for (v = 0; v < this->numVertexes; v++)
	{
		visited[v] = 0;
		dis[v] = this->arc[begin][v];
		path[v] = 0;
	}
	dis[begin] = 0;
	visited[begin] = 1;
	for (v = 1; v < this->numVertexes; v++)
	{
		min = INF;
		for (w = 0; w < this->numVertexes; w++)
		{
			if (!visited[w] && dis[w] < min)
			{
				k = w;
				min = dis[w];
			}
		}
		visited[k] = 1;
		for (w = 0; w < this->numVertexes; w++)
		{
			if (!visited[w] && (min + this->arc[k][w] < dis[w]))
			{
				dis[w] = min + this->arc[k][w];
				path[w] = k;
			}
		}
	}
	cout << endl;
	int h = end;
	while (h != begin)
	{
		cout << vexs[h] << "<--";
		h = path[h];
	}
	cout << vexs[begin] << endl;
	cout << this->vexs[begin] << "到" << this->vexs[end] << "的最小权值和为" << dis[end] << endl;
}
template <typename T>void MGraph<T>::Floyd(int begin, int end)
{
	int dis[MAXVEX][MAXVEX];
	int path[MAXVEX][MAXVEX];
	for (int i = 0; i < this->numVertexes; ++i)
	{
		for (int j = 0; j < this->numVertexes; ++j)
		{
			dis[i][j] = this->arc[i][j];
			if (arc[i][j] == INF || arc[i][j] == 0)
			{
				path[i][j] = -1;
			}
			else
			{
				path[i][j] = i;
			}			
		}
	}
	for (int k = 0; k < this->numVertexes; ++k)
	{
		for (int v = 0; v < this->numVertexes; ++v)
		{
			for (int w = 0; w < this->numVertexes; ++w)
			{
				if (dis[v][w] > dis[v][k] + dis[k][w])
				{
					dis[v][w] = dis[v][k] + dis[k][w];
					path[v][w] = k;
				}
			}
		}
	}
	int a = begin;
	int b = end;
	cout << vexs[b] << "<--";
	while (a != path[a][b])
	{
		cout << vexs[path[a][b]] << "<--";
		b = path[a][b];
	}
	cout << vexs[begin];
	cout << endl;
	cout << this->vexs[begin] << "到" << this->vexs[end] << "的最小权值和为" << dis[begin][end] << endl;
}
int main()
{
	MGraph<char>g;
	//g.DFSTraverse();
	//g.BFSTraverse();
	//g.MiniSpanTree_Prim();
	//g.MiniSpanTree_Kruskal();
	//g.Dijkstra(0, 3);
	//g.Floyd(0, 3);
	//g.PrintMGraph();
}
