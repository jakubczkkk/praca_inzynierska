#include "photon.h"

using namespace std;
      
int main() {

    auto A = new double [N][N]();

    for (int it = 0; it < Nfot; ++it) {

        Photon p = Photon();
        Object o = Object(0.15, 0.15, 0.1, 0.03);

        do {

            int current_layer = p.layer;
            double mi_t = mi_a(current_layer) + mi_s(current_layer);
            double l = - log(get_random()) / mi_t;
            p.move_photon(l);

            p.do_boundaries_check(current_layer);
            if (!p.life) break;

            if (p.check_for_object_collision(o)) {
                // cout << p.r.x << " " << p.r.y << " " << p.r.z << endl;
                break;
            }

            double delta_w = p.w * mi_a(current_layer) / mi_t;
            p.change_w(delta_w);

            // double t = sqrt(pow(p.r.x, 2) + pow(p.r.y, 2));
            // int i = floor(t / dr);      i = i < N ? i : N - 1;
            int i = floor(p.r.x / dz);  i = i < N ? i : N - 1;
            int j = floor(p.r.z / dz);  j = j < N ? j : N - 1;
             A[i][j] += delta_w;

            double g = get_g(current_layer);
            double cos_theta = (1 + pow(g, 2) - pow((1 - pow(g, 2)) / (1 - g + 2 * g * get_random()), 2)) / (2 * g);
            double phi = 2 * M_PI * get_random();
            p.change_direction(cos_theta, phi);

            p.check_for_end_of_life(1e-4);
            
        } while (p.life);

    }

    write_photon_data_to_file(A);
    
    delete[] A;

}
