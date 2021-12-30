#include "photon.h"

void Photon::change_direction(double cos_theta, double phi) {

    double sin_theta = sqrt(1 - pow(cos_theta, 2));
    double rho = sqrt(1 - pow(u.z, 2));
    double cos_phi = cos(phi);
    double sin_phi = sin(phi);
    
    Coords u_old = u;

    if (u.x == 0.0 && u.y == 0.0 && (abs(u.z) >= 1.0 - 1e6)) {
        u.x = sin_theta * cos_phi;
        u.y = sin_theta * sin_phi;
        u.z = cos_theta; 
    }
    else {
        u.x = (sin_theta * (u_old.x * u_old.z * cos_phi - u_old.y * sin_phi)) / rho + u_old.x * cos_theta;
        u.y = (sin_theta * (u_old.y * u_old.z * cos_phi + u_old.x * sin_phi)) / rho + u_old.y * cos_theta;
        u.z = - rho * sin_theta * cos_phi + u_old.z * cos_theta;
    }
                                              
}

void Photon::move_photon(double l) {

    r.x += u.x * l;
    r.y += u.y * l;
    r.z += u.z * l;

}

void Photon::change_w(double delta_w) {

    w -= delta_w;

}

int Photon::get_new_layer() {

    int new_layer;
    if (r.z <= 0) {
        new_layer = 0;
    }
    else if (r.z <= z1) {
        new_layer = 1;
    }
    else if (r.z <= z1 + z2) {
        new_layer = 2;
    }
    else {
        new_layer = 3;
    }
    return new_layer;

}

void Photon::check_boundaries(int old_layer, double l, double& R, double& T) {

    int new_layer = get_new_layer();

    if (layer == new_layer) {
        return;
    }

    if (old_layer == 1 && new_layer == 0) {

        double _R = get_R(n1, n0, abs(u.z));

        if (get_random() < _R) {

            move_photon(-l);
            double partial_step = abs(r.z / u.z);
            move_photon(partial_step);
            u.z *= -1;
            move_photon(l - partial_step);
        }
        else {

            R += w;
            life = false;
            return;
        }

    }

    if (old_layer == 2 && new_layer == 3) {

        T += w;
        life = false;
        return;

    }

    if (old_layer == 1 && new_layer == 2) {

        double R = get_R(n1, n2, abs(u.z));

        if (get_random() < R) {

            move_photon(-l);
            double partial_step = abs((z1 - r.z) / u.z);
            move_photon(partial_step);
            u.z *= -1;
            move_photon(l - partial_step);

        }
        else {

            layer = 2;
        }

    }

    if (old_layer == 2 && new_layer == 1) {

        double R = get_R(n2, n1, abs(u.z));

        if (get_random() < R) {

            move_photon(-l);
            double partial_step = abs((z2 - r.z) / u.z);
            move_photon(partial_step);
            u.z *= -1;
            move_photon(l - partial_step);

        }
        else  {
            layer = 1;
        }
    }

}

void Photon::check_for_end_of_life(double delta, double& A) {

    if (w < delta) { 

        double m = get_random();
        if (m < 0.1) {
            w /= m;
        }
        else {
            life = false;
        }

    }

}

void Photon::check_for_strong_absorbtion(Object& o, double& A) {

    if (sqrt(pow(r.x - o.x, 2) + pow(r.y - o.y, 2) + pow(r.z - o.z, 2)) < o.r) {

        life = false;
        A += w;

    }

}

void Photon::check_for_strong_scattering(Object& o, double l) {
    
    if (sqrt(pow(r.x - o.x, 2) + pow(r.y - o.y, 2) + pow(r.z - o.z, 2)) < o.r) {

        move_photon(-l);

        vector<double> T = get_t(r.x, r.y, r.z, u.x, u.y, u.z, o.x, o.y, o.z, o.r*o.r);
        Coords t1 = { r.x + u.x * T[0], r.y + u.y * T[0], r.z + u.z * T[0] };
        Coords t2 = { r.x + u.x * T[1], r.y + u.y * T[1], r.z + u.z * T[1] };
        double t1d = sqrt(pow(t1.x - r.x, 2) + pow(t1.y - r.y, 2) + pow(t1.z - r.z, 2));
        double t2d = sqrt(pow(t2.x - r.x, 2) + pow(t2.y - r.y, 2) + pow(t2.z - r.z, 2));
        Coords P = t1d < t2d ? t1 : t2;

        double partial_step = abs((r.z - P.z) / u.z);
        move_photon(partial_step);

        Coords ut { o.x - P.x, o.y - P.y, o.z - P.z};
        double ut_norm = sqrt(ut.x * ut.x + ut.y * ut.y + ut.z * ut.z);
        Coords t = { ut.x / ut_norm, ut.y / ut_norm, ut.z / ut_norm };

        Quaternion p = Quaternion(cos(M_PI / 2), sin(M_PI / 2) * t.x, sin(M_PI / 2) * t.y, sin(M_PI / 2) * t.z );
        Quaternion ps = Quaternion(cos(M_PI / 2), -sin(M_PI / 2) * t.x, -sin(M_PI / 2) * t.y, -sin(M_PI / 2) * t.z );
        Quaternion v1 = Quaternion(0, -u.x, -u.y, -u.z);
        Quaternion v2 = p * v1 * ps;

        u.x = v2.q1;
        u.y = v2.q2;
        u.z = v2.q3;

        move_photon(l - partial_step);

    }

}