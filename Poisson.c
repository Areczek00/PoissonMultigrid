#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846264338327

double ro = 0.0;
int nx = 128;
int ny = 128;
double delta = 0.2;
double TOL = 1e-8;
int count = 1;

double licz_warunek_stopu(double V[][ny+1], int k);

//Dirichlet, warunki brzegowe

void WB (double V[][ny+1]);

void relaksacja_siatkowa(double V[][ny+1], int k, FILE *fp, FILE *fp2);

void zageszczanie_siatki(double V[][ny+1], int k);

void procedura_ogolna(double V[][ny+1], int k);



int main(void){
    double V[nx+1][ny+1];
    //warunki brzegowe Dirichleta
    WB(V);
    //zerowanie
    for (int i = 1; i < nx; i++){
        for(int j = 1; j < ny; j++){
            V[i][j] = 0.0;
        }
    }
    double k = 16;
    procedura_ogolna(V, k);
    system("python3 plotf2.py");
    return 0;
}





void WB (double V[][ny+1]){

    for (int j = 0; j < ny+1; j++){
        //VB1 (0,y)
        V[0][j] = sin(M_PI*(delta*j)/(delta*ny));
        //VB3 (xmax,y)
        V[nx][j] = sin(M_PI*(delta*j)/(delta*ny));
    }
    for (int i = 0; i < nx+1; i++){
        //VB2(x,ymax)
        V[i][ny] =  -1*sin(2*M_PI*(delta*i)/(delta*nx));
        //VB4 (x, 0)
        V[i][0] = sin(2*M_PI*(delta*i)/(delta*nx));
    }
}

void procedura_ogolna(double V[][ny+1], int k){
    while (k >= 1){
        char filename [30];
        char filename2 [30];
        sprintf(filename, "potencjalk_%d.txt", k);
        sprintf(filename2, "S(it)k_%d.txt", k);
        FILE *fp = fopen(filename, "w");
        FILE *fp2 = fopen(filename2, "w");
        relaksacja_siatkowa(V, k, fp, fp2);
        k /= 2;
        fclose(fp);
        fclose(fp2);
    }
}




void relaksacja_siatkowa(double V[][ny+1], int k, FILE *fp, FILE *fp2){
    double Sold = 1.0;
    double Snew = 10.0;
    while(fabs((Snew - Sold) / Sold) >= TOL){
           Sold = Snew;
            for (int i = k; i <= nx-k; i += k){
                for (int j = k; j <= ny - k; j += k){
                    V[i][j] = (V[i+k][j] + V[i-k][j] + V[i][j+k] + V[i][j-k])/4.0;
                }
            }
            Snew = licz_warunek_stopu(V,k);
 
            fprintf(fp2, "%d\t%lf\n", count, Snew);
            count++;
    }
    for (int i = 0; i <= nx - k; i+= k){
        for (int j = 0; j <= ny - k; j+= k){
            fprintf(fp, "%lf\t%lf\t%lf\n", i*delta, j*delta, V[i][j]);
        }
    }
    zageszczanie_siatki(V, k);
}

double licz_warunek_stopu(double V[][ny+1], int k){
    //S(k)
    double Sk = 0;
    for (int i = 0; i <= nx - k; i += k){
        for (int j = 0; j <= ny - k; j += k){
            Sk += pow(k*delta,2)*(pow((V[i+k][j] - V[i][j] + V[i+k][j+k] - V[i][j+k])/(2.0*k*delta),2)+ pow((V[i][j+k] - V[i][j] + V[i+k][j+k] - V[i+k][j])/(2.0*k*delta),2))/2.0;
        }
    }
    return Sk;
}
void zageszczanie_siatki(double V[][ny+1], int k){
    int nk = k/2;
    for (int i = 0; i <= nx-k; i += k){
        for (int j = 0; j <= ny-k; j += k){
            V[i+nk][j+nk] = (V[i][j] + V[i+k][j] + V[i][j+k] + V[i+k][j+k])/4.0;
            if (i != nx - k)
                V[i+k] [j+nk] = (V[i+k][j] + V[i+k][j+k])/2.0;
            if (j != ny - k)
                V[i+nk] [j+k] = (V[i][j+k] + V[i+k][j+k])/2.0;
            if (j != 0)
                V[i+nk]   [j] = (V[i][j] + V[i+k][j])/2.0;
            if (i != 0)
                V[i]   [j+nk] = (V[i][j] + V[i][j+k])/2.0;
        }
    }
}


