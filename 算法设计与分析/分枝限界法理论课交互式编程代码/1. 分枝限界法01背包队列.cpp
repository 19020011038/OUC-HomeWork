#include <iostream>
#include <queue>
using namespace std;
#define MAXN 20

//问题表示
int n = 3, W = 30;
int w[] = { 0,16,15,15 };		//重量，下标0不用
int v[] = { 0,45,25,25 };  	//价值，下标0不用
//求解结果表示
int maxv = -9999;		//存放最大价值,初始为最小值
int bestx[MAXN];		//存放最优解,全局变量
int total = 1;			//解空间中结点数累计,全局变量
struct NodeType		//队列中的结点类型
{
	int no;			//结点编号
	int i;			//当前结点在搜索空间中的层次
	int w;			//当前结点的总重量
	int v;			//当前结点的总价值
	int x[MAXN];		//当前结点包含的解向量
	double ub;			//上界
};

void bound(NodeType& e)			//计算分枝结点e的上界
{
	int i = e.i + 1;				//考虑结点e的余下物品
	int sumw = e.w;				//求已装入的总重量
	double sumv = e.v;				//求已装入的总价值
	while ((sumw + w[i] <= W) && i <= n)
	{
		sumw += w[i];				//计算背包已装入载重
		sumv += v[i];				//计算背包已装入价值
		i++;
	}
	if (i <= n)					//余下物品只能部分装入
		e.ub = sumv + (W - sumw) * v[i] / w[i];
	else						//余下物品全部可以装入
		e.ub = sumv;
}

void EnQueue(NodeType e, queue<NodeType>& qu)
//结点e进队qu
{
	if (e.i == n)					//到达叶子结点
	{
		if (e.v > maxv)				//找到更大价值的解
		{
			maxv = e.v;
			for (int j = 1; j <= n; j++)
				bestx[j] = e.x[j];
		}
	}
	else qu.push(e);				//非叶子结点进队
}

void bfs()				//求0/1背包的最优解
{
	int j;
	NodeType e, e1, e2;			//定义3个结点
	queue<NodeType> qu;		//定义一个队列
	e.i = 0;				//根结点置初值，其层次计为0
	e.w = 0; e.v = 0;
	e.no = total++;
	for (j = 1; j <= n; j++)
		e.x[j] = 0;
	bound(e);				//求根结点的上界
	qu.push(e);				//根结点进队

	while (!qu.empty())				//队不空循环
	{
		e = qu.front(); qu.pop();			//出队结点e
		if (e.w + w[e.i + 1] <= W)			//剪枝：检查左孩子结点
		{
			e1.no = total++; e1.i = e.i + 1;		//建立左孩子结点
			e1.w = e.w + w[e1.i];
			e1.v = e.v + v[e1.i];
			for (j = 1; j <= n; j++)			//复制解向量
				e1.x[j] = e.x[j];
			e1.x[e1.i] = 1;
			bound(e1);				//求左孩子结点的上界
			EnQueue(e1, qu);			//左孩子结点进队操作
		}
		e2.no = total++;				//建立右孩子结点
		e2.i = e.i + 1;
		e2.w = e.w; e2.v = e.v;
		for (j = 1; j <= n; j++)			//复制解向量
			e2.x[j] = e.x[j];
		e2.x[e2.i] = 0;
		bound(e2);				//求右孩子结点的上界
		if (e2.ub > maxv)		//若右孩子结点可行,则进队,否则被剪枝
			EnQueue(e2, qu);
	}
}

int main()
{
	bfs();
	printf("最大价值为：%d, 放入物品编号为：", maxv);
	for (int j = 1; j <= n; j++) if (bestx[j]) printf(" %d", j);
	return 0;
}