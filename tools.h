#pragma once

#include <iostream>
#include <random>
#include <fstream>
#include <cmath>

#include "quaternion.h"

#define N 1000

using namespace std;

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

extern random_device rd;
extern mt19937 gen;
extern uniform_real_distribution<> dis;

double mi_a(int n);
double mi_s(int n);
double get_g(int n);
double get_R(double n1, double n2, double cos_theta1);
double get_random();

void write_photon_data_to_file(double A[N][N]);
void write_photon_pos_data_to_file(vector<vector<double>>& v);
void set_to_range(int& value);

vector<double> get_t(double xp, double yp, double zp, double a, double b, double c, double xk, double yk, double zk, double r);

struct Object {
    double x, y, z, r;
    Object(double _x, double _y, double _z, double _r) : x(_x), y(_y), z(_z), r(_r) { }
} ;