#pragma once

#include "tools.h"

struct Photon {

    Coords u { 0, 0, 1 };
    Coords r { 0, 0, 0 };
    double w { 1 };
    bool life { true };
    int layer { 1 };

    void change_direction(double cos_theta, double phi);
    void move_photon(double l);
    void change_w(double delta_w);
    int get_new_layer();
    void check_boundaries(int current_layer, double l, double& R, double& T);
    void check_for_end_of_life(double delta, double& A);
    void check_for_strong_absorbtion(Object& o, double& A);
    void check_for_strong_scattering(Object& o, double l);

};
