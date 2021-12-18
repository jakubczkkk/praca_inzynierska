#pragma once

#include "tools.h"

struct Photon {

    struct temp {
        double x, y, z;
    };

    temp u { 0, 0, 1 };
    temp r { 0, 0, 0 };
    
    double w { 1 };
    bool life { true };
    int layer { 1 };

    void print_pos() { cout << "(" << r.x << ", " << r.y << ", " << r.z << ")" << endl; }

    void change_direction(double cos_theta, double phi);
    void move_photon(double l);
    void change_w(double delta_w);

    void do_boundaries_check(int current_layer, double l);
    void check_for_end_of_life(double delta);

    int get_new_layer();
    bool check_if_layer_changes();

    bool check_for_object_collision(Object& o);
    void check_for_strong_scattering(Object& o, double l);

};