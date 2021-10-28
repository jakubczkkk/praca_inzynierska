#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Photon
{
    struct temp
    {
        double x, y, z;
        void print()
        {
            cout << x << " " << y << " " << z << endl;
        }
    };

    public:

    temp u { 0, 0, 1 };
    temp r { 0, 0, 0 };

    double w { 1 };

    bool life { true };

    int layer { 1 };

    void change_direction(double cos_theta, double phi);
    void move_photon(double l);
    void change_w(double delta_w);

    bool zmiana_osrodka(double z1, double z2);

};