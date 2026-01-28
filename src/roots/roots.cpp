#include <iostream>
#include <functional>
#include <cmath>

bool bisection(std::function<double(double)> f, double a, double b, double *root) 
{
    //Calculate number of iterations needed for 1e-6 accuracy
    int n = std::log2((b-a)/(1e-6)) + 1;

    double c = 0;

    for (int i = 0; i < n; i++)
    {
        //Calculate midpoint c
        c = (a+b)/2;

        //Check if c is close enough to 0 to be a root, otherwise assign a new a or b depending on if c is positive or negative
        if (std::abs(f(c)) <= 1e-6) 
        {
            *root = c;
            return true;
        }
        else if (f(c) > 0) 
        {
            b = c;
        }
        else 
        {
            a = c;
        }
    }

    return false;
}

bool regula_falsi(std::function<double(double)> f, double a, double b, double *root) 
{
    double c = 0;

    
    //Check if a solution should exist assuming f is continuous
    if (f(a)>0 || f(b)<0) {
        return false;
    }
    
 
    //If f(c) is close enough to 0 it is a root, otherwise set c as the new a or b depending on its sign
    while(std::abs(f(c)) >= 1e-6) 
    {
        //Calculate a new midpoint c
        c = a - (f(a)*(b-a))/(f(b)-f(a));

        if (f(c) > 0)
        {
            b = c;
        }
        else 
        {
            a = c;
        }
    }
    *root = c;
    return true;
}

bool newton_raphson(std::function<double(double)> f, std::function<double(double)> g, double a, double b, double c, double *root)
{
    // Calculates a tangent line that gets closer and closer to 0
    while(std::abs(f(c))>=1e-6) 
    {
        if (g(c) == 0 || c > b || c < a)
        {
            return false;
        } 
        c = c - f(c)/g(c);
        
    }
    *root = c;
    return true;
}

bool secant(std::function<double(double)> f, double a, double b, double c, double *root) 
{
     
    // Calculates a secant line that gets closer and closer to the root
    while(std::abs(f(c)) >= 1e-6) 
    {
        c = a - ((b - a) / (f(b) - f(a))) * f(a);
        a = b;
        b = c;
    }
    *root = c;
    return true;
}
