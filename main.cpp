#include "photon.h"

#include <vector>

using namespace std;
      
int main() {

    // auto result = get_t(0, 0, 0, 1, 1, 1, 1, 4, 0, 16);
    // cout << result[0] << " " << result[1] << endl;

    auto A = new double [N][N]();
    auto B = vector<vector<double>>();

    for (int it = 0; it < Nfot; ++it) {

        // cout << it << endl;

        Photon p = Photon();
        Object o = Object(0, 0, 0.02, 0.01);

        while (p.life) {

            int current_layer = p.layer;
            double mi_t = mi_a(current_layer) + mi_s(current_layer);
            double l = - log(get_random()) / mi_t;
            p.move_photon(l);

            p.do_boundaries_check(current_layer, l);
            if (!p.life) break;

            // if (p.check_for_object_collision(o)) break;
            if (p.check_for_object_collision(o)) p.life = false;
            // p.check_for_strong_scattering(o, l);

            double delta_w = p.w * mi_a(current_layer) / mi_t;
            p.change_w(delta_w);

            int i = floor((p.r.x - xmin) / dx);
            set_to_range(i);

            int j = floor(p.r.z / dz); 
            set_to_range(j);

            A[i][j] += delta_w;

            double g = get_g(current_layer);
            double cos_theta = (1 + pow(g, 2) - pow((1 - pow(g, 2)) / (1 - g + 2 * g * get_random()), 2)) / (2 * g);
            double phi = 2 * M_PI * get_random();
            p.change_direction(cos_theta, phi);

            p.check_for_end_of_life(1e-4);

            // B.push_back({p.r.x, p.r.y, p.r.z, p.w});
            
        }

    }

    write_photon_data_to_file(A);
    // write_photon_pos_data_to_file(B);
    
    delete[] A;

}
