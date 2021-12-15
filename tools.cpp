#include "tools.h"

double n0 = 1;
double n1 = 1.3;
double n2 = 1.6;
double n3 = 1;

double g1 = 0.2;
double g2 = 0.6;

double h1 = 1.3;
double h2 = 1.5;

double mia1 = 10;
double mis1 = 100;

double mia2 = 20;
double mis2 = 100;

double romax = 1;

double Nfot = 1e6;

double z1 = 0.1;
double z2 = 0.1;

double dz = (z1 + z2) / N;
double dr = romax / N;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0, 1);

double get_random() {
    return dis(gen);
}

double mi_a(int n) {
    return n == 1 ? mia1 : mia2;
}

double mi_s(int n) {
    return n == 1 ? mis1 : mis2;
}

double get_g(int n) {
    return n == 1 ? g1 : g2;
}

double get_R(double n1, double n2, double cos_theta1) {
    double sin_theta1 = sqrt(1 - pow(cos_theta1, 2));
    double sin_theta2 = sin_theta1 * (n1 / n2);
    double cos_theta2 = sqrt(1 - pow(sin_theta1, 2));

    return (
        pow(sin_theta1 * cos_theta2 - cos_theta1 * sin_theta2, 2) / 2 *
        (pow(cos_theta1 * cos_theta2 + sin_theta1 * sin_theta2, 2) + pow(cos_theta1 * cos_theta2 - sin_theta1 * sin_theta2, 2)) /
        (pow(sin_theta1 * cos_theta2 + cos_theta1 * sin_theta2, 2) * pow(cos_theta1 * cos_theta2 + sin_theta1 * sin_theta2, 2))
    );
}

void write_photon_data_to_file(double A[N][N]) {

    ofstream f;
    f.open("photon.dat");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            f << A[i][j];
            if (j < N - 1) f << " ";
        }
        f << endl;
    }
    f.close();

}