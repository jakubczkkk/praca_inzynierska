#include "photon.h"

void Photon::change_direction(double cos_theta, double phi)
{
    double sin_theta = sqrt(1 - pow(cos_theta, 2));
    double rho = sqrt(1 - pow(u.z, 2));
    double cos_phi = cos(phi);
    double sin_phi = sin(phi);

    temp u_old = u;

    if (u.x == 0.0 && u.y == 0.0 && (abs(u.z) >= 1.0 - 1e6))
    {
        u.x = sin_theta * cos_phi;
        u.y = sin_theta * sin_phi;
        u.z = cos_theta; 
    }
    else
    {
        u.x = (sin_theta * (u_old.x * u_old.z * cos_phi - u_old.y * sin_phi)) / rho + u_old.x * cos_theta;
        u.y = (sin_theta * (u_old.y * u_old.z * cos_phi + u_old.x * sin_phi)) / rho + u_old.y * cos_theta;
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

int Photon::get_new_layer()
{
    int new_layer;
    if (r.z <= 0)
    {
        new_layer = 0;
    }
    else if (r.z <= z1)
    {
        new_layer = 1;
    }
    else if (r.z <= z1 + z2)
    {
        new_layer = 2;
    }
    else
    {
        new_layer = 3;
    }
    return new_layer;
}

bool Photon::check_if_layer_changes()
{
    return !(layer == get_new_layer());
} 

void Photon::clear_photon()
{
    u = temp { 0, 0, 1 };
    r = temp { 0, 0 ,0 };
    
    w = 1;
    life = true;
    layer = 1;
}