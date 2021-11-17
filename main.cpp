#include <iostream>
#include <random>
#include <fstream>
#include "photon.h"

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
    double Abs_c = 0;
    double Rd_c = 0;
    double Rd_c_square = 0;
    double Tr_c = 0;
    double Tr_c_square = 0;

    for (int it = 0; it < Nfot; ++it)
    {
        // ofstream f;
        // f.open("photon.dat");

        Photon p = Photon();

        double A[100][100] {};
        double Abs = 0;
        double Rd = 0;
        double Tr = 0;

        do
        {
            int current_layer = p.layer;

            double mi_t = mi_a(current_layer) + mi_s(current_layer);
            double l = -log(get_random()) / mi_t;
            p.move_photon(l);

            if (p.check_if_layer_changes())
            {
                int new_layer = p.get_new_layer();
                int old_layer = current_layer;

                if (old_layer == 1 && new_layer == 0)
                {
                    // cout << "do n0 " << p.r.z << endl;
                    double R = get_R(n1, n0, abs(p.u.z));                   
                    if (get_random() < R)
                    {
                        // cout << R << endl;
                        p.r.z = 0;
                        p.u.z *= -1;
                    }
                    else
                    {
                        Rd += p.w;
                        p.life = false;
                        break;
                    }
                }

                if (old_layer == 2 && new_layer == 3)
                {
                    // cout << "do n3 " << p.r.z << endl;
                    Tr += p.w;
                    p.life = false;
                    break;
                }

                if (old_layer == 1 && new_layer == 2)
                {
                    // cout << "do n2 " << p.r.z << endl;
                    double R = get_R(n1, n2, abs(p.u.z));
                    if (get_random() < R)
                    {
                        p.u.z *= -1;
                    }
                    else
                    {
                        p.layer = 2;
                    }
                }

                if (old_layer == 2 && new_layer == 1)
                {
                    // cout << "do n1 " << p.r.z << endl;
                    double R = get_R(n2, n1, abs(p.u.z));
                    if (get_random() < R)
                    {
                        p.u.z *= -1;
                    }
                    else
                    {
                        p.layer = 1;
                    }
                }

            }

            double delta_w = p.w * mi_a(current_layer) / mi_t;
            p.change_w(delta_w);

            // zapis do tablicy A
            double t = sqrt(pow(p.r.x, 2) + pow(p.r.y, 2));
            int i = floor(t / dr);
            i = i < 100 ? i : 99;
            int j = floor(p.r.z / dz);
            j = j < 100 ? j : 99;
            A[i][j] += delta_w;

            // zmiana kierunku
            double g = get_g(current_layer);
            double cos_theta = (1 + pow(g, 2) - pow((1 - pow(g, 2)) / (1 - g + 2 * g * get_random()), 2)) / (2 * g);
            double phi = 2 * M_PI * get_random();
            p.change_direction(cos_theta, phi);

            // f << p.r.x << " " << p.r.y << " " << p.r.z << endl;

            // sprawdzamy ile pozostało fotonów
            if (p.w < 1e-6)
            {   
                double m = get_random();
                if (m < 0.1)
                {
                    p.w /= m;
                }
                else
                {
                    A[i][j] += delta_w;
                    p.life = false;
                }
            }

        } while (p.life);

        for (int i = 0; i < 100; ++i)
        {
            for (int j = 0; j < 100; ++j)
            {
                Abs += A[i][j];
            }
        }

        // cout << Abs << " + " << Rd << " + " << Tr << " = " << Abs + Rd + Tr << endl;
        Abs_c += Abs;
        Tr_c += Tr;
        Rd_c += Rd;
        Rd_c_square += Rd * Rd;
        Tr_c_square += Tr * Tr;

        // f.close();

    }

    cout << "<Rd> = " << Rd_c / Nfot << endl;
    cout << "<Rd^2> = " << Rd_c_square / Nfot << endl;
    cout << "Var{Rd} = " << Rd_c / Nfot - Rd_c_square / Nfot << endl;
    cout << "Odch std Rd = " << sqrt((Rd_c / Nfot - Rd_c_square / Nfot) / Nfot) << endl;

    cout << "<Tr> = " << Tr_c / Nfot << endl;
    cout << "<Tr^2> = " << Tr_c_square / Nfot << endl;
    cout << "Var{Tr} = " << Tr_c / Nfot - Tr_c_square / Nfot << endl;
    cout << "Odch std Tr = " << sqrt((Tr_c / Nfot - Tr_c_square / Nfot) / Nfot) << endl;

}