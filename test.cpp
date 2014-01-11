#include <iostream>
#include <string>
#include <list>

using namespace std;

enum Operation
{
	EQUAL, DELETE, INSERT
};

class Diff
{
public:
	Operation operation;
	string text;
	Diff(){}
	Diff(Operation _operation, string _text)
	{
		operation = _operation;
		text = _text;
	}
};

class Snake
{
public:
	int bx;
	int by;
	int mx;
	int my;
	int ex;
	int ey;
	Snake(){}
	Snake(int _bx, int _by, int _mx, int _my, int _ex, int _ey)
	{
		bx = _bx;
		by = _by;
		mx = _mx;
		my = _my;
		ex = _ex;
		ey = _ey;
	}
};

list<Diff*> diffs;


void cmp_files(string text1, int N, string text2, int M)
{
	/*if(N==0 && M>0)
	{
	   diffs.push_back(new Diff(INSERT, text2));
		return;
	}
	if(M==0 && N>0)
	{
		diffs.push_back(new Diff(DELETE, text1));
		return;
	}*/
	if(N<=0 || M<=0)
		return;

	int delta = N - M;
	int max_d = (N + M + 1) / 2;
	int *V1 = new int[2*max_d];
  	int *V2 = new int[2*max_d];
  	int base = max_d;

  	V1[base+1]=0;
  	V2[base+1]=0;
	for(int d=0; d<=max_d; d++)
	{
		for(int k=-d; k<=d; k+=2)
		{
			bool down = ( k == -d || ( k != d && V1[base+ k - 1 ] < V1[base+ k + 1 ] ) );

			int kPrev = down ? k + 1 : k - 1;

			// start point
			int xStart = V1[base+ kPrev];
			int yStart = xStart - kPrev;

			// mid point
			int xMid = down ? xStart : xStart + 1;
			int yMid = xMid - k;

			// end point
			int xEnd = xMid;
			int yEnd = yMid;

			// follow diagonal

			while ( xEnd < N && yEnd < M && text1[ xEnd ] == text2[ yEnd ] )
			{ xEnd++; yEnd++; }
			//cout<<d<<" odd "<<xEnd<<":"<<yEnd<<endl;

			V1[base+ k ] = xEnd;

			if((delta%2)!=0 && (k>= delta - (d-1) && k <= delta + (d-1)))
			{
				
				int r_xEnd = N - V2[base + delta-k];
				if(xEnd >= r_xEnd)
				{
					/*delete [] V1;
					delete [] V2;*/
					int D = 2*d -1;
					//cout<<"o********"<<D<<"  "<<((M+N)-D)/2<<endl;
					//cout<<xStart<<" "<<yStart<<" "<<xMid<<" "<<yMid<<" "<<xEnd<<" "<<yEnd<<endl;
					if(D >= 1)
					{
						string text1a = text1.substr(0,xStart);
						string text1b = "";
						if(xEnd<N)
							text1b= text1.substr(xEnd);
						string text2a = text2.substr(0,yStart);
						
						string text2b="";
						if(yEnd<N)
							text2b= text2.substr(yEnd);
						
						//cout<<"t1a:"<<text1a<<endl;
						//cout<<"t1b:"<<text1b<<endl;
						//cout<<"t2a:"<<text2a<<endl;
						//cout<<"t2b:"<<text2b<<endl;

						cmp_files(text1a,text1a.size(),text2a,text2a.size());
						diffs.push_back(new Diff(EQUAL, text1.substr(xMid,xEnd-xMid)));
						//diffs.push_back(new Diff(INSERT, text2));
						cmp_files(text1b,text1b.size(),text2b,text2b.size());
					}
					else if(D ==0)
					{
						diffs.push_back(new Diff(EQUAL, text1));
					}


					
					return;
					//***********************************
				}
			}

		}

		for(int k=-d; k<=d; k+=2)
		{
			bool down = ( k == -d || ( k != d && V2[base+ k - 1 ] < V2[base+ k + 1 ] ) );

			int kPrev = down ? k + 1 : k - 1;

			// start point
			int xStart = V2[base+ kPrev];
			int yStart = xStart - kPrev;

			// mid point
			int xMid = down ? xStart : xStart + 1;
			int yMid = xMid - k;

			// end point
			int xEnd = xMid;
			int yEnd = yMid;

			// follow diagonal

			while ( xEnd < N && yEnd < M && text1[N - xEnd -1] == text2[M - yEnd -1] )
			{ xEnd++; yEnd++; }

			//cout<<d<<" eve "<<xEnd<<":"<<yEnd<<endl;
			V2[base+ k] = xEnd;

			if((delta%2)==0 && (k>= -d && k <= d ))//去掉了delta
			{
				
				int r_xEnd = V1[base + delta-k];
				if(N-xEnd <= r_xEnd)//<=???????
				{
					/*delete [] V1;
					delete [] V2;*/
					int D = 2*d;
					//cout<<"e******"<<D<<" "<<((M+N)-D)/2<<endl;
					if(D >= 1)
					{	
						xStart = N - xStart;
						yStart = M - yStart;
						xEnd = N - xEnd;
						yEnd = M -yEnd;
						xMid = N -xMid;
						yMid = M -yMid;
						//cout<<xStart<<" "<<yStart<<" "<<xMid<<" "<<yMid<<" "<<xEnd<<" "<<yEnd<<endl;
						string text1a = text1.substr(0,xEnd);
						string text1b = text1.substr(xStart);
						string text2a = text2.substr(0,yEnd);
						string text2b = text2.substr(yStart);
						//cout<<"t1a:"<<text1a<<endl;
						//cout<<"t1b:"<<text1b<<endl;
						//cout<<"t2a:"<<text2a<<endl;
						//cout<<"t2b:"<<text2b<<endl;

						cmp_files(text1a,text1a.size(),text2a,text2a.size());
						//cout<<"here1"<<endl;
						string temp = text1.substr(xEnd,xMid-xEnd);
						if(!temp.empty())
						diffs.push_back(new Diff(EQUAL, temp));
						//diffs.push_back(new Diff(INSERT, text2));
						cmp_files(text1b,text1b.size(),text2b,text2b.size());
						//cout<<"here2"<<endl;
					}
					else if(D ==0)
					{
						if(!text1.empty())
						diffs.push_back(new Diff(EQUAL, text1));
						//cout<<"here3"<<endl;
					}
					//cout<<"here4"<<endl;
					
					//cout<<"e"<<D<<" "<<((M+N)-D)/2<<endl;
					return;
					//***********************************
				}
			}
		}
	}

}

//for debug
int main()
{
    string a,b;
	freopen("in.txt","r",stdin);
	cin>>a;
	freopen("in2.txt","r",stdin);
    cin>>b;
	cout<<a.size()<<"     "<<b.size()<<endl;
	cmp_files(a,a.size(),b,b.size());
	list<Diff*>::iterator it = diffs.begin();
	cout<<"--------------------"<<endl;
	for(;it != diffs.end(); it++)
	{
		cout<<(*it)->text;
	}
	cout<<"\n--------------------"<<endl;
	return 0;
}


