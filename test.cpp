#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
#include <stack>
#define MAXLEN 600
#define base 300
using namespace std;

int **V;
//map<int,int> V;

class POINT
{
public:
  int X;
  int Y;
  POINT(){}
  POINT(int x,int y)
  {
    X=x;
    Y=y;
  }
};
class Snake
{
public:
  POINT start;
  POINT mid;
  POINT end;
  Snake(int ax,int ay,int bx,int by,int cx,int cy)
  {
      start.X=ax;
      start.Y=ay;
      mid.X=bx;
      mid.Y=by;
      end.X=cx;
      end.Y=cy;
  }
};

stack<Snake*> snakes;

void solution(int N,int M,int D,int **V)
{
    POINT *p = new POINT( N, M ); // start at the end

    for ( int d = D ; p->X > 0 || p->Y > 0 ; d-- )
    {

      int k = p->X - p->Y;

      // end point is in V
      int xEnd = V[1+d][ k+base ];
      int yEnd = xEnd - k;
     // cout<<k<<" D:"<<d<<" xend:"<<xEnd<<" yend:"<<yEnd<<endl;

      // down or right?
      bool down = ( k == -d || ( k != d && V[d][ k - 1+base ] < V[d][ k + 1 +base] ) );

      int kPrev = down ? k + 1 : k - 1;

      // start point
      int xStart = V[d][ kPrev+base ];
      int yStart = xStart - kPrev;

      // mid point
      int xMid = down ? xStart : xStart + 1;
      int yMid = xMid - k;

      snakes.push(new Snake( xStart,yStart,xMid,yMid,xEnd,yEnd ) );

      p->X = xStart;
      p->Y = yStart;
    }
}

//  
int main()
{
  V = new int* [base];
  for(int i=0;i<base;i++)
    V[i]=new int [MAXLEN];
  V[0][ base+1 ] = 0;
  string A,B;
  freopen("in.txt","r",stdin);
  cin>>A;
  
  freopen("in2.txt","r",stdin);
  cin>>B;
  //cout<<A<<"-"<<B<<"-"<<endl;
  int N = A.size();
  int M = B.size();
  cout<<N<<" -------- "<<M<<endl;
  clock_t begin,end;
  begin=clock();

  for ( int d = 0 ; d <= N + M ; d++ )
  {
    for ( int k = -d ; k <= d ; k += 2 )
    {
      // down or right?
      bool down = ( k == -d || ( k != d && V[1+d-1][base+ k - 1 ] < V[1+d-1][base+ k + 1 ] ) );

      int kPrev = down ? k + 1 : k - 1;

      // start point
      int xStart = V[1+d-1][base+ kPrev ];
      int yStart = xStart - kPrev;

      // mid point
      int xMid = down ? xStart : xStart + 1;
      int yMid = xMid - k;

      // end point
      int xEnd = xMid;
      int yEnd = yMid;

      // follow diagonal
      
      while ( xEnd < N && yEnd < M && A[ xEnd ] == B[ yEnd ] )
      { xEnd++; yEnd++; }

      // save end point
      V[1+d][base+ k ] = xEnd;

      // check for solution
      if ( xEnd >= N && yEnd >= M ) /* solution has been found */
      {
        end = clock();
        cout<<end-begin<<endl;
        cout<<d<<" |--| "<<((M+N)-d)/2<<endl;
        
//**********
        solution(N,M,d,V);
        
        while(!snakes.empty())
        {
            Snake *temp = snakes.top();
            int mx=temp->mid.X;
            int my=temp->mid.Y;
            int ex=temp->end.X;
            int ey=temp->end.Y;
            while(mx!=ex&&my!=ey)
            {
                mx++;my++;
                //cout<<mx<<":"<<my<<endl;
                cout<<A[mx-1];
            }
            snakes.pop();
        }
//*********


        for(int i=0;i<base;i++)
          delete []V[i];
        delete []V;
        V= NULL;
        return 0;
      }
    }
    //printf("%d\n",d);
  }
  //delete V;
  return 0;
}
