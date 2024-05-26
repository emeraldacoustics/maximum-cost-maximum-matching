#include <cstring>

int n;
int w[maxn][maxn];
int ulnk[maxn];
int vlnk[maxn];
int ulvl[maxn];
int vlvl[maxn];
bool uflg[maxn];
bool vflg[maxn];

inline bool found(const int & u)
{
	uflg[u] = true;
	for(int v = 0 ; v < n ; ++ v)
	{
		if(ulvl[u] + vlvl[v] == w[u][v] && !vflg[v])
		{
			vflg[v] = true;

			if(vlnk[v] == -1 || found(vlnk[v]))
			{
				ulnk[u] = v;
				vlnk[v] = u;
				return true;
			}
		}
	}

	return false;
}

inline void update(void)
{
	int d;

	d = pinf;
	for(int i = 0; i < n; ++ i)
	{
		if(uflg[i])
		{
			for(int j = 0; j < n; ++ j)
			{
				if(!vflg[j])
					d = min(d, ulvl[i] + vlvl[j] - w[i][j]);
			}
		}
	}

	for(int i = 0; i < n; ++ i)
	{
		if(uflg[i])
			ulvl[i] -= d;

		if(vflg[i])
			vlvl[i] += d;
	}
}

int km(void)
{
	int rlt;

	memset(ulnk, -1, sizeof(ulnk[0]) * n);
	memset(vlnk, -1, sizeof(vlnk[0]) * n);
	memset(vlvl, 0, sizeof(vlvl[0]) * n);
	for(int i = 0; i < n; ++ i)
	{
		ulvl[i] = w[i][0];
		for(int j = 1; j < n; ++ j)
			ulvl[i] = max(ulvl[i], w[i][j]);
	}

	for(int i = 0; i < n; ++ i)
	{
		for(; ; )
		{
			memset(uflg, false, sizeof(uflg[0]) * n);
			memset(vflg, false, sizeof(vflg[0]) * n);
			if(found(i))
				break;
			else
				update();
		}
	}

	rlt = 0;
	for(int i = 0; i < n; ++ i)
		rlt += w[i][ulnk[i]];

	return rlt;
}