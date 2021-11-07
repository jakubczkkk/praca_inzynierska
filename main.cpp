#include <iostream>
#include <random>
#include <fstream>
#include "photon.h"
#include <sys/resource.h>

using namespace std;
      
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0, 1);

double get_random()
{
    return dis(gen);
}

double mi_a(int n)
{
    return n == 1 ? mia1 : mia2;
}

double mi_s(int n)
{
    return n == 1 ? mis1 : mis2;
}

double get_g(int n)
{
    return n == 1 ? g1 : g2;
}

double get_R(double n1, double n2, double cos_theta1)
{
    double sin_theta1 = sqrt(1 - pow(cos_theta1, 2));
    double sin_theta2 = sin_theta1 * (n1 / n2);
    double cos_theta2 = sqrt(1 - pow(sin_theta1, 2));

    return (
        pow(sin_theta1 * cos_theta2 - cos_theta1 * sin_theta2, 2) / 2 *
        (pow(cos_theta1 * cos_theta2 + sin_theta1 * sin_theta2, 2) + pow(cos_theta1 * cos_theta2 - sin_theta1 * sin_theta2, 2)) /
        (pow(sin_theta1 * cos_theta2 + cos_theta1 * sin_theta2, 2) * pow(cos_theta1 * cos_theta2 + sin_theta1 * sin_theta2, 2))
    );

}

int main()
{

    double A[100][100] {};
    double Abs = 0;
    double Rd = 0;
    double Tr = 0;

    for (int it = 0; it < 1e4; ++it)
    {
        Photon a = Photon();

        double l0 = -log(get_random()) / (mi_a(1) + mi_s(1));
        double delta_w = a.w * mi_a(1) / (mi_a(1) + mi_s(1));

        a.move_photon(l0);
        a.change_w(delta_w);
        
        double t = sqrt(pow(a.r.x, 2) + pow(a.r.y, 2));
        int i = floor(t / dr);
        int j = floor(a.r.z / dz);
        A[i][j] += delta_w;

        while (a.life)
        {
            double mi_t = mi_a(a.layer) + mi_s(a.layer);
            double g = get_g(a.layer);

            double cos_theta = (1 + pow(g, 2) - pow((1 - pow(g, 2)) / (1 - g + 2 * g * get_random()), 2)) / (2 * g);
            double phi = 2 * M_PI * get_random();

            a.change_direction(cos_theta, phi);

            double ksi = get_random();
            double l = - (log(ksi)) / mi_t;

            a.move_photon(l);

            if (a.check_if_layer_changes())
            {
                int new_layer = a.get_new_layer();
                int old_layer = a.layer;

                if (old_layer == 1 && new_layer == 0)
                {
                    //cout << "do n0 " << a.r.z << endl;
                    double R = get_R(n1, n0, abs(a.u.z));                   
                    if (get_random() < R)
                    {
                        a.u.z *= -1;
                    }
                    else
                    {
                        Rd += a.w;
                        a.life = false;
                        break;
                    }
                }

                if (old_layer == 2 && new_layer == 3)
                {
                    //cout << "do n3 " << a.r.z << endl;
                    Tr += a.w;
                    a.life = false;
                    break;
                }

                if (old_layer == 1 && new_layer == 2)
                {
                    //cout << "do n2 " << a.r.z << endl;
                    double R = get_R(n1, n2, abs(a.u.z));
                    if (get_random() < R)
                    {
                        a.u.z *= -1;
                    }
                    else
                    {
                        a.layer = 2;
                    }
                    
                }

            }

            double mia = mi_a(a.layer);
            delta_w = a.w * mia / mi_t;

            a.change_w(delta_w);
            
            double t = sqrt(pow(a.r.x, 2) + pow(a.r.y, 2));
            int i = floor(t / dr);
            int j = floor(a.r.z / dz);
            if (i >= 100)
            {
                i = 99;
            }
            if (j >= 100)
            {
                j = 99;
            }
            A[i][j] += delta_w;

            if (a.w < 1e-4) // mało fotonów
            {   
                double m = get_random();
                if (m < 0.1)
                {
                    a.w /= m;
                }
                else
                {
                    A[i][j] += delta_w;
                    a.life = false;
                }
            }

        }

    }

    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            Abs += A[i][j];
        }
    }

    cout << Abs << " + " << Rd << " + " << Tr << " = " << (Abs + Rd + Tr) / 1e4 << endl;

}