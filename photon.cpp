#include "photon.h"

void Photon::change_direction(double cos_theta, double phi)
{
    double sin_theta = sqrt(1 - pow(cos_theta, 2));

    double rho = sqrt(1 - pow(u.z, 2));

    double cos_phi = cos(phi);

    double sin_phi = sin(phi);

    temp u_old = u;

    if (u.x == 0.0 && u.y == 0.0 && u.z == 1.0)
    {
        u.x = sin_theta * cos_phi;
        u.y = sin_theta * sin_phi;
        u.z = cos_theta; 
    }
    else
    {
        u.x = (sin_theta * (u_old.x * u_old.z * cos_phi - u_old.y * sin_phi)) / rho + u_old.x * cos_theta;
        u.x = (sin_theta * (u_old.y * u_old.z * cos_phi + u_old.x * sin_phi)) / rho + u_old.y * cos_theta;
        u.z = - rho * sin_theta * cos_phi + u_old.z * cos_theta;
    }

}

void Photon::move_photon(double l)
{
    r.x += u.x * l;
    r.y += u.y * l;
    r.z += u.z * l;

    
}

void Photon::change_w(double delta_w)
{
    w -= delta_w;
}

bool Photon::zmiana_osrodka(double na, double nb)
{
    return true;
}