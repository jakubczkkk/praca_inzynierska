#include <iostream>
#include <random>
#include <fstream>

#include "photon.h"

using namespace std;

double n0 = 1;
double n1 = 1.3;
double n2 = 1.5;
double n3 = 1;

double g1 = 0.5;
double g2 = 0.3;

double h1 = 1.3;
double h2 = 1.5;

double mia1 = 10;
double mia2 = 20;
double mis1 = 90;
double mis2 = 90;

double romax = 1;

double Nfot = 1e6;

double z1 = 0.1;
double z2 = 0.1;

double dz = (z1 + z2) / 100;
double dr = romax / 100;


int main()
{
    ofstream photon_pos;
    photon_pos.open("photon_pos.csv");
        
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);

    double A[100][100] {};

    Photon a = Photon();
    a.move_photon(- (log(dis(gen))) / (mia1 + mis1));

    double delta_w = a.w * mia1 / (mia1 + mis1);

    a.change_w(delta_w);
    
    double t = sqrt(pow(a.r.x, 2) + pow(a.r.y, 2));
    int i = floor(t / dr);
    int j = floor(a.r.z / dz);
    A[i][j] += delta_w;

    photon_pos << a.r.x << "," << a.r.y << "," << a.r.z << endl;

    while (a.life)
    {
        double ksi = dis(gen);

        double mit = a.layer == 1 ? mia1 + mis1 : mia2 + mis2;

        double l = - (log(ksi)) / mit;

        double g = a.layer == 1 ? g1 : g2;

        double cos_theta = (1 + pow(g, 2) - pow((1 - pow(g, 2)) / (1 - g + 2 * g * dis(gen)), 2)) / 2 * g;

        double phi = 2 * M_PI * dis(gen);

        a.change_direction(cos_theta, phi);
        a.move_photon(l);

        double mia = a.layer == 1 ? mia1 : mia2;
        delta_w = a.w * mia / mit;

        a.change_w(delta_w);
        
        double t = sqrt(pow(a.r.x, 2) + pow(a.r.y, 2));
        int i = floor(t / dr);
        int j = floor(a.r.z / dz);
        A[i][j] += delta_w;

        photon_pos << a.r.x << "," << a.r.y << "," << a.r.z << endl;

        if(a.zmiana_osrodka(z1, z2))
        {

        }

        if (a.w < 0.00001)
        {
            a.life = false;
        }

    }

    ofstream myfile;
    myfile.open("test.csv");
    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            myfile << A[i][j];
            if (j < 99)
            {
                myfile << ",";
            }
        }

        myfile << endl;
    }
    myfile.close();

    photon_pos.close();
}