#include <stdio.h>
#include <stdlib.h>
#include <math.h>




/* Function Prototype */

int* reconstruct(int N, int M, int Xbeg, int Xend, int Ybeg, int Yend, int s[][], int N_s, int X_pf[], int Y_pf[], int f_s, int c, int my_delay);
void findHighest(int A[][], int n, int m);
int* linespace(int x_beg, int x_end, int N);



/* Main Function */
int main(){

int *p;

int N =10; int M = 10; int Xbeg=0; int Xend=10; int Ybeg= 0; int Yend=10; int N_s = 20; int f_s = 3000; int c = 300000000; int my_delay = 1;

int  X_pf[N]; int Y_pf[M]; int s[N_s][200];
p = reconstruct(N, M, Xbeg, Xend, Ybeg, Yend, s, N_s, X_pf, Y_pf, f_s,c, my_delay);


return 0;
}
/*End of Main */


/* Function definition */

int *reconstruct(N, M, Xbeg, Xend, Ybeg, Yend, s[][], N_s, X_pf[], Y_pf[], f_s,c, my_delay){


int x_grid[N] = linspace(Xbeg, Xend,N);
int y_grid[M] = linspace(Ybeg, Yend,M);



int Imagetotal1 [N][M] = {0};
int Imagetemp[N][M] = {0};
int indx;
int Dtotal[N][M] = {0};


int l;
int n;
int m;
int t;
int  b;

b= sizeof(s[0])/sizeof(int);

for (l=0; l<=N_s-1; l++){
	for (n=0; n<=N-1;n++){
		for (m=0; m<= M-1; m++){
			Dtotal[n][m] = 2 * (sqrt( pow((X_pf[l] - x_grid[n]),2) + pow((Y_pf[l] - y_grid[n]),2)) );
			t = Dtotal[n][m]/c + my_delay;
			indx =  (t/(1/f_s)) + 1;
			if (indx<b){
			Imagetemp[n][m] = s[l][indx];
			}
		}
	}
	Imagetotal1 = Imagetotal1 + Imagetemp;
}

/* Finding maximum of Imagetotal1 in absolute value */
Imagetotal1 = Imagetotal1/ findHighest(Imagetotal1,N,M);

return Imagetotal1;
}/* end of reconstruct*/



/* Maximum function */
void findHighest(int A[][], int n, int m)
{
     for (int i = 0; i < n; i++)
     {
         int max = abs(A[i][0]);
         for (int j = 1; j < m; j++)
         {
             if (abs(A[i][j]) > max)
             {
                max = abs(A[i][j]);
             }
         }
         // do something with max
     }

}

/* Linespace */
int* linespace(int x_beg, int x_end, int N)
{
	int step=(x_end-x_beg)/(N-1);
	int out[N];
	for (int i=0;i<N; i++){
		out[i]= x_beg +i*step;
	}
	return out;
}
