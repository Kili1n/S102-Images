#include "filtre.h"

#include "image.h"

#include <fstream>

#include <iostream>

#include <sstream>

#include <stdexcept>

#include <string>

#include <vector>

using namespace std;

Filtre::Filtre(vector < vector < float >> action, int rayon) {
    if (action.size() == (1 + 2 * rayon) &&
        action[rayon].size() == (1 + 2 * rayon)) {
        _action = action;
        _rayon = rayon;
    } else {
        throw invalid_argument(
            string("l'action n'est pas compatible avec le rayon fourni"));
    }
}

Image Filtre::application(const Image & ImageOrigine) const {
    vector < vector < int >> compRouge = ImageOrigine.getVectRouge();
    vector < vector < int >> compVert = ImageOrigine.getVectVert();
    vector < vector < int >> compBleu = ImageOrigine.getVectBleu();
    float pixelRouge = 0;
    float pixelVert = 0;
    float pixelBleu = 0;

    for (int i = _rayon; i < compRouge.size() - _rayon; i++) { // on parcours sans toucher aux bords ou aux coins
        for (int j = _rayon; j < compRouge[0].size() - _rayon; j++) { // idem
            pixelRouge = 0;
            pixelVert = 0;
            pixelBleu = 0;
            for (int k = -_rayon; k <= _rayon; k++) {
                for (int n = -_rayon; n <= _rayon; n++) {
                    if ((0 <= i + k <= compRouge.size()) &&
                        (0 <= j + n <= compRouge.size())) {
                        pixelRouge += _action[abs(k)][abs(n)] * ImageOrigine.getRouge(i + k, j + n);
                        pixelVert += _action[abs(k)][abs(n)] * ImageOrigine.getVert(i + k, j + n);
                        pixelBleu += _action[abs(k)][abs(n)] * ImageOrigine.getBleu(i + k, j + n);
                    }
                }
            }
            compRouge[i][j] = max(0, min(255, int(pixelRouge)));
            compVert[i][j] = max(0, min(255, int(pixelVert)));
            compBleu[i][j] = max(0, min(255, int(pixelBleu)));
        }
    }

    Image NouvelleImage(compRouge, compVert, compBleu);
    return NouvelleImage;
}
