#include <iostream> //CXADI
#include <cmath>
#include <cstdio>

using namespace std;
const int n = 100;
double u_zusti(double x, double t)
{
    return (sin(x)+sin(t))*sin(cos(x*t));
}

double f(double x, double t)
{
    return t*t*cos(t*x)*cos(cos(t*x))*(sin(t)+sin(x))+2*t*cos(x)*cos(cos(t*x))*sin(t*x)-x*cos(cos(t*x))*(sin(t)+sin(x))*sin(t*x)+cos(t)*sin(cos(t*x))+sin(x)*sin(cos(t*x))+t*t*(sin(t)+sin(x))*sin(t*x)*sin(t*x)*sin(cos(t*x));
}

double miu1(double t)
{
    return u_zusti(0,t);
}

double miu2(double t) //t aris 0dan 7mde
{
    return u_zusti(2,t);
}

double u0(double x) // x aris 0dan 2mde
{
    return u_zusti(x,0);
}

int main()
{
    double a = 0, b = 2, T0 = 0, T1 = 7;
    double x = a, t = T0;
    double h = (b-a)/n;
    double tau = h*h/3;
    int m = (T1-T0)/tau;
    double tauh = tau/(h*h);
    double y0[n+1],y1[n+1];
    for(int i = 0; i <=n; i++)
    {
        y0[i] = u0(a+i*h);
    }
    for(int j = 1; j < m; j++)
    {
        t = T0 + j*tau;
        y1[0] = miu1(t);
        for(int i = 1; i < n; i++)
        {
            x = a+i*h;
            y1[i] = tauh*y0[i+1]+(1-2*tauh)*y0[i]+tauh*y0[i-1]+tau*f(x,t);
        }
        y1[n] = miu2(t);

        for(int i = 0; i <=n; i++)
            y0[i] = y1[i];
    }

    for(int i = 0; i <= n; i++)
    {
        x = a + i*h;
        printf("%8.5lf %12.6lf %12.6lf \n", x,y1[i],u_zusti(x,T1));
    }
    return 0;
}
