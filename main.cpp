#include "photon.h"

using namespace std;

int main(int argc, char * argv[]) {

    if (argc > 1) initialize_parameters(argv);

    cout << "****************************************************" << endl;
    cout << "Wczytano paramtetry użytkownika" << endl;

    auto absorbtion_data = array<array<double, N>, N>();
    auto position_data = vector<vector<double>>();

    double A = 0;
    double R = 0;
    double T = 0;

    cout << "Rozpoczęto symulacje" << endl;

for (int it = 0; it < Nfot; ++it) {

    Photon p = Photon();
    Object o = Object(x, y, z, r);

    while (p.life) {

        int current_layer = p.layer;
        double mi_t = get_mi_a(current_layer) + get_mi_s(current_layer);
        double l = - log(get_random()) / mi_t;
        p.move_photon(l);

        p.check_boundaries(current_layer, l, R, T);
        if (mode == 2) { p.check_for_strong_absorbtion(o, A); }
        if (mode == 3) { p.check_for_strong_scattering(o, l); }

        if (!p.life) break;

        double delta_w = p.w * get_mi_a(current_layer) / mi_t;
        p.change_w(delta_w);

        int i = floor((p.r.x - xmin) / dx);     set_to_range(i);
        int j = floor(p.r.z / dz);              set_to_range(j);
        absorbtion_data[i][j] += delta_w;
        A += delta_w;

        double g = get_g(current_layer);
        double cos_theta = 
            (1 + pow(g, 2) - pow((1 - pow(g, 2)) / 
            (1 - g + 2 * g * get_random()), 2)) / (2 * g);
        double phi = 2 * M_PI * get_random();
        p.change_direction(cos_theta, phi);

        p.check_for_end_of_life(1e-4, A);

        if (mode == 1) position_data.push_back(
            {p.r.x, p.r.y, p.r.z, p.w});
        
    }

}

    cout << "Zakończono " << Nfot << " iteracji" << endl;

    write_photon_data_to_file(absorbtion_data);
    if (mode == 1)  { write_photon_pos_data_to_file(position_data); }

    cout << "Zapisano dane do plików" << endl;

    cout << "Otrzymane wartości parametrów A, R i T dla podanego układu: " << endl;
    cout << "Absorpcja:    " << A / Nfot << endl;
    cout << "Reflektancja: " << R / Nfot << endl;
    cout << "Transmijsa:   " << T / Nfot << endl;
    cout << "Nfot*(A+R+T) = (powinno wynieść Nfot):   " << T + A + R << endl;
    cout << "Koniec działania symulacji" << endl;
    cout << "****************************************************" << endl;

}
