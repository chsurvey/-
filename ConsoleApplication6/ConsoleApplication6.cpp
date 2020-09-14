#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int> > dfs(int p[][50], int n,int y,int x)
{
    vector<pair<int,int> > v;
    vector<pair<int, int> > went;
    stack<pair<int,int> > s;
    s.push(make_pair(x, y));
    while (!s.empty())
    {
        int n_y=s.top().second, n_x=s.top().first;
        s.pop();

        if (find(went.begin(), went.end(), make_pair(n_x, n_y)) != went.end())
            continue;
        //cout << "y : " << n_y << ", x : " << n_x << ", "<<v.size()<<"\n";
        
        went.push_back(make_pair(n_x, n_y));
        if (p[n_y][n_x] == 0)
        {
            if (n_y > 0)
            {
                s.push(make_pair(n_x, n_y - 1));
            }
            if (n_y < n-1)
            {
                s.push(make_pair(n_x, n_y + 1));
            }
            if (n_x > 0)
            {
                s.push(make_pair(n_x - 1, n_y));
            }
            if (n_x < n-1)
            {
                s.push(make_pair(n_x + 1, n_y));
            }

            if (n_y > 0&& n_x > 0)
            {
                s.push(make_pair(n_x-1, n_y - 1));
            }
            if (n_y < n - 1&& n_x > 0)
            {
                s.push(make_pair(n_x-1, n_y + 1));
            }
            if (n_y > 0 && n_x < n - 1)
            {
                s.push(make_pair(n_x + 1, n_y-1));
            }
            if (n_y < n - 1 && n_x < n - 1)
            {
                s.push(make_pair(n_x + 1, n_y+1));
            }
            if (find(v.begin(), v.end(), make_pair(n_x, n_y)) == v.end())
                v.push_back(make_pair(n_x, n_y));
            continue;
        }
        else
        {
            if(find(v.begin(),v.end(),make_pair(n_x,n_y))==v.end())
                v.push_back(make_pair(n_x, n_y));
            continue;
        }
    }
    return v;
}

int main()
{
    srand(time(NULL));
    int board[50][50] = { 0, };
    int n, k;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            k = rand() % 8 + 1;
            if (k == 1)
            {
                board[i][j] = 1;
            }
        }
    }
    int sum = 0;
    int num[50][50] = { 0, };
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 1)
            {
                num[i][j] = -1;
                continue;
            }

            sum = 0;
            if (i > 0)
            {
                sum += board[i - 1][j];
            }
            if (j > 0)
            {
                sum += board[i][j - 1];
            }
            if (i < n - 1)
            {
                sum += board[i + 1][j];
            }
            if (j < n - 1)
            {
                sum += board[i][j + 1];
            }
            if (i > 0 && j > 0)
            {
                sum += board[i - 1][j - 1];
            }
            if (i > 0 && j < n - 1)
            {
                sum += board[i - 1][j + 1];
            }
            if (i < n - 1 && j>0)
            {
                sum += board[i + 1][j - 1];
            }
            if (i < n - 1 && j < n - 1)
            {
                sum += board[i + 1][j + 1];
            }
            num[i][j] = sum;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(3) << num[i][j];
        }
        cout << "\n";
    }

    int click[50][50] = { 0, };
    while (true)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        
        if (num[y][x] == -1)
        {
            cout << "폭탄\n";
            return 0;
        }
        
        if (num[y][x] == 0)
        {
            //cout << "0\n";
            vector<pair<int,int> > v=dfs(num, n, y, x);
            for (int i = 0; i < v.size(); i++)
            {
                int a = v[i].first, b = v[i].second;
                click[b][a] = 1;
            }
        }
        else
        {
            click[y][x] = 1;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (click[i][j] == 0)
                {
                    cout << setw(3) << "*";
                }
                else
                    cout << setw(3) << num[i][j];
            }
            cout << "\n";
        }
    }
}
