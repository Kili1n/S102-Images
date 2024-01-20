#ifndef FILTRE_H_INCLUDED
#define FILTRE_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>

#include "image.h"

using namespace std;

class Filtre {

private :

    vector < vector<float> > _action;
    int _rayon;

public :
    Filtre(vector < vector <float> > action, int rayon);
    Image application(const Image& ImageOrigine) const;

};

#endif // FILTRE_H_INCLUDED
