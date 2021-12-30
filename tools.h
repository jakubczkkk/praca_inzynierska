#pragma once

#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include <vector>
#include <array>

using namespace std;

#define N 1000

extern double n0;
extern double n1;
extern double n2;
extern double n3;
extern double g1;
extern double g2;
extern double mia1;
extern double mis1;
extern double mia2;
extern double mis2;
extern double Nfot;
extern double z1;
extern double z2;
extern double xmin;
extern double xmax;
extern double dz;
extern double dx;
extern double x;
extern double y;
extern double z;
extern double r;
extern int mode;
extern random_device rd;
extern mt19937 gen;
extern uniform_real_distribution<> dis;

double get_mi_a(int n);
double get_mi_s(int n);
double get_g(int n);
double get_R(double n1, double n2, double cos_theta1);
double get_random();
void initialize_parameters(char * args[]);
void write_photon_data_to_file(array<array<double, N>, N>& A);
void write_photon_pos_data_to_file(vector<vector<double>>& v);
void set_to_range(int& value);
vector<double> get_t(double xp, double yp, double zp, double a, double b, double c, double xk, double yk, double zk, double r);

struct Object {
    double x, y, z, r;
    Object(double _x, double _y, double _z, double _r) : x(_x), y(_y), z(_z), r(_r) { }
};

struct Quaternion {

    double q0, q1, q2, q3;

    Quaternion(double a = 0, double b = 0, double c = 0, double d = 0) : q0(a), q1(b), q2(c), q3(d) { }

    Quaternion operator*(Quaternion q) {
        Quaternion r;
        r.q0 = q0 * q.q0 - q1 * q.q1 - q2 *  q.q2 - q3 * q.q3;
        r.q1 = q1 * q.q0 + q0 * q.q1 - q3 *  q.q2 + q2 * q.q3;
        r.q2 = q2 * q.q0 + q3 * q.q1 + q0 *  q.q2 - q1 * q.q3;
        r.q3 = q3 * q.q0 - q2 * q.q1 + q1 *  q.q2 + q0 * q.q3;
        return r;
    }

};

struct Coords {
    double x, y, z;
};
