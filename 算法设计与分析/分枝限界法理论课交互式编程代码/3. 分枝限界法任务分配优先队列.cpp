#include <iostream>
#include <queue>
using namespace std;
#define MAXN 20
#define MAX_INT 2147483647

//问题表示
int n = 4;
int c[MAXN][MAXN] = { {0},{0,9,2,7,8},{0,6,4,3,7},
	{0,5,8,1,8},{0,7,6,9,4} };
//下标0的元素不用
int bestx[MAXN];		//最优分配方案
int mincost = MAX_INT;		//最小成本
int total = 1;			//结点个数累计

struct NodeType		//队列结点类型
{
	int no;			//结点编号
	int i;			//人员编号
	int x[MAXN];		//x[i]为人员i分配的任务编号
	bool worker[MAXN];		//worker[i]=true表示任务i已经分配
	int cost;			//已经分配任务所需要的成本
	int lb;			//下界
	bool operator<(const NodeType& s) const	//重载<关系函数
	{
		return lb > s.lb;
	}
};

void bound(NodeType& e)	     //求结点e的限界值	
{
	int minsum = 0;
	for (int i1 = e.i + 1; i1 <= n; i1++) //求c[e.i+1..n]行中最小元素和
	{
		int minc = MAX_INT;
		for (int j1 = 1; j1 <= n; j1++)   //各列中仅仅考虑没有分配的任务
			if (e.worker[j1] == false && c[i1][j1] < minc)
				minc = c[i1][j1];
		minsum += minc;
	}
	e.lb = e.cost + minsum;
}

void bfs()				//求解任务分配
{
	int j;
	NodeType e, e1;
	priority_queue<NodeType> qu;
	memset(e.x, 0, sizeof(e.x));	//初始化根结点的x
	memset(e.worker, 0, sizeof(e.worker));
	//初始化根结点的worker
	e.i = 0;				//根结点，指定人员为0
	e.cost = 0;
	bound(e);				//求根结点的lb
	e.no = total++;
	qu.push(e);			//根结点进队列
	while (!qu.empty())
	{
		e = qu.top(); qu.pop();		//出队结点e，当前考虑人员e.i
		if (e.i == n)			//达到叶子结点
		{
			if (e.cost < mincost)	//比较求最优解
			{
				mincost = e.cost;
				for (j = 1; j <= n; j++)
					bestx[j] = e.x[j];
			}
		}
		e1.i = e.i + 1;		//扩展分配下一个人员的任务，对应结点e1
		for (j = 1; j <= n; j++)	//考虑n个任务
		{
			if (e.worker[j]) 	//任务j是否已分配人员,若已分配，跳过
				continue;
			for (int i1 = 1; i1 <= n; i1++)	//复制e.x得到e1.x
				e1.x[i1] = e.x[i1];
			e1.x[e1.i] = j;		//为人员e1.i分配任务j
			for (int i2 = 1; i2 <= n; i2++)	//复制e.worker得到e1.worker
				e1.worker[i2] = e.worker[i2];
			e1.worker[j] = true;		//表示任务j已经分配
			e1.cost = e.cost + c[e1.i][j];
			bound(e1);			//求e1的lb
			e1.no = total++;
			if (e1.lb <= mincost)		//剪枝
				qu.push(e1);
		}
	}
}


int main()
{
	bfs();
	printf("最小成本为：%d, 分配任务编号为：", mincost);
	for (int j = 1; j <= n; j++) printf(" %d", bestx[j]);
	return 0;
}