#include "photon.h"

using namespace std;

int main(int argc, char * argv[]) {

    if (argc > 1) initialize_parameters(argv);

    cout << "Wczytano paramtetry użytkownika" << endl;

    auto A = array<array<double, N>, N>();
    auto B = vector<vector<double>>();

    cout << "Rozpoczęto symulacje" << endl;

    for (int it = 0; it < Nfot; ++it) {

        Photon p = Photon();
        Object o = Object(x, y, z, r);

        while (p.life) {

            int current_layer = p.layer;
            double mi_t = mi_a(current_layer) + mi_s(current_layer);
            double l = - log(get_random()) / mi_t;
            p.move_photon(l);

            p.do_boundaries_check(current_layer, l);
            if (!p.life) break;

            if (mode == 2) { if (p.check_for_object_collision(o)) p.life = false; }
            if (mode == 3) { p.check_for_strong_scattering(o, l); }

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

            if (mode == 1) B.push_back({p.r.x, p.r.y, p.r.z, p.w});
            
        }

    }

    cout << "Zakończono " << Nfot << " iteracji" << endl;

    write_photon_data_to_file(A);
    if (mode == 1)  { write_photon_pos_data_to_file(B); }

    cout << "Zapisano dane do plików" << endl;

}
