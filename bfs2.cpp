#include <bits/stdc++.h> 
using namespace std;
double eps = 0.0000001;
int m,n,state[100][100],x,z;
pair<int,int> source,goal,initparent;
map < pair<int,int>, pair<int,int> > mp;
map < pair<int,int>, double > d_map;
pair  < double,pair<int,int> > temp2,temp,start;
double ab;
stack < pair <int,int> > s;
int path[100][2];

priority_queue  < pair <double,pair<int,int> >, vector < pair <double,pair<int,int> > > ,greater< pair <double,pair<int,int> > > > pq;
void check_insert(pair<int,int> p,double dist)
{
	if((p.first >= 0 && p.first < m) && (p.second >=0 && p.second <n))
	{
		if(state[p.first][p.second] != 1)
		{
			pair < double ,pair<int,int> > temp1;
			temp1.second = p;
			if(mp.find(p) == mp.end())
			{
				mp[p] = temp.second;
				d_map[p] = dist;
					temp1.first = d_map[p];
			pq.push(temp1);
			}
			else
			{
				if(d_map[p] > dist)
				{
					d_map[p] = dist;
					mp[p]=temp.second;
						temp1.first = d_map[p];
			pq.push(temp1);
				}
			}
		
		}
	}
}
int main()
{
   	int t1;
	freopen("bfs2.txt","r",stdin);
    freopen("maze.txt","w",stdout);
   	cin >> t1;
   	int t=1;
   	while(t1--)
   	{
   		t=0;
   		int a,b,i,j,flag = 0;
   		cin >> m >> n;
   		for(i=0;i<m;i++)
   		{
   			for(j=0;j<n;j++)
   			{
   				cin >> state[i][j];
               cout<<state[i][j]<<" ";
   				if(state[i][j] == 2)
   				{
   					goal = make_pair(i,j);
   				}
   			}
            cout<<endl;
   		}
   		cin >> a >> b;
   		source = make_pair(a,b);
   		initparent = make_pair(-1,-1);
   		mp[source] = initparent;
   		d_map[source] = 0;
   		start.first = 0;
   		start.second = source;
   		pq.push(start);
   		while(!pq.empty())
   		{
   			temp = pq.top();
   			x = temp.second.first;
   			z = temp.second.second;
   			if(temp.second == goal)
   			 {
   			 	flag = 1;
   			 	break;
   			 }
   			double parent_dist = temp.first;
   			pq.pop();
   			check_insert(make_pair(x,z+1),parent_dist+1 + (t++)*eps);
   			//check_insert(make_pair(x+1,z+1),parent_dist+sqrt(2)+(t++)*eps);
   			check_insert(make_pair(x+1,z),parent_dist+1+(t++)*eps);
   			//check_insert(make_pair(x+1,z-1),parent_dist+sqrt(2)+(t++)*eps);
   			check_insert(make_pair(x,z-1),parent_dist+1+(t++)*eps);
   			//check_insert(make_pair(x-1,z-1),parent_dist+sqrt(2)+(t++)*eps);
   			check_insert(make_pair(x-1,z),parent_dist+1+(t++)*eps);
   			//check_insert(make_pair(x-1,z+1),parent_dist+sqrt(2)+(t++)*eps);
   		}
   		pair <int,int> parent = mp[goal];
   		while(parent != initparent)
   		{
   			s.push(parent);
   			parent = mp[parent];
   		}
   		int ctr = 0;
   		while(!s.empty())
   		{
   			path[ctr][0] = 15 - s.top().first +1 ;
   			path[ctr][1] = s.top().second +1;
   			ctr++;
   			s.pop();
   		}
   		path[ctr][0] = 15 - goal.first+1;
   		path[ctr][1] = goal.second+1;
   		ctr++;
   		cout << ctr << endl;
   		for(int i =0;i<ctr;i++)
   		{
   			cout << path[i][0] << " " << path[i][1] << endl;
   		}
   		while(!pq.empty())
   		{
   			pq.pop();
   		}
   		mp.clear();
   		d_map.clear();
   		
   	}
      
      freopen("game.txt","w",stdout);
      for(int i=0;i<m;i++)
      {
         for(int j=0;j<n;j++)
         {
            cout<<state[i][j]<<" ";
         }
         cout<<endl;
      }

      cout<<endl<<(15-source.first+1)<<" "<<(source.second+1)<<endl<<(15-goal.first+1)<<" "<<(goal.second+1)<<endl;
    return 0;
}

