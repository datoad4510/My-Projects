#include <iostream> 
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
    double marcx = 0, marjv = 2, t=0, T=7;
    double alfa[n+1], beta[n+1], y[n+1],y_old[n+1];
    double a[n+1],b[n+1],c[n+1],F[n+1];
    double h, tau, gama;
    h = (marjv - marcx)/n;
    tau = h;
    int m = T/tau;
    gama = tau/(h*h);
    for(int i = 1; i < n; i++)
    {
        a[i] = gama; b[i] = gama; c[i] = 1+2*gama;
    }
    alfa[1] = 0;

    for(int i = 1; i < n; i++)
    {
        alfa[i+1] = b[i]/(c[i]-alfa[i]*a[i]);
    }
    for(int i = 0; i<=n; i++)
    {
        y[i]=u0(marcx+i*h);
    }
    for(int i = 0; i < m; i++)
    {
        for(int i = 0; i<=n;i++)
        {
            y_old[i]=y[i];
        }
        t += tau;
        for(int i = 1; i<n;i++)
        {
            F[i]=- y_old[i]-tau*f(marcx+i*h,t);
        }
        beta[1] = miu1(t);
        for(int i = 1; i<n; i++)
        {
            beta[i+1] = (a[i]*beta[i] - F[i])/(c[i]-a[i]*alfa[i]);
        }
        y[n] = miu2(t);
        for(int i = n-1; i>0; i--)
        {
            y[i] = alfa[i+1]*y[i+1]+beta[i+1];
        }
        y[0] = miu1(t);
    }
    cout <<"    i       y       u_zusi"<<endl;
    for(int i = 0; i<=n;i++)
    {
        printf("%4d %10.4lf %10.4lf \n",i,y[i],u_zusti(marcx+i*h,t));
    }

    return 0;
}
