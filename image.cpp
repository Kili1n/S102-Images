#include "image.h"

#include <fstream>

#include <iostream>

#include <sstream>

#include <stdexcept>

#include <string>

#include <vector>

using namespace std;

// Constructeur de l'imaFge
Image::Image(const vector < vector < int >> & rouge,
    const vector < vector < int >> & vert,
        const vector < vector < int >> & bleu) {
    cout << "Construction de l'image" << endl;
    if (rouge.size() != vert.size() || rouge.size() != bleu.size()) {
        throw invalid_argument(string("les vecteurs n'ont pas la meme taille"));
    }
    _rouge = rouge;
    _vert = vert;
    _bleu = bleu;
    _longueur = rouge.size();
    _largeur = rouge[0].size();
}

Image::Image() {
    _rouge = {};
    _vert = {};
    _bleu = {};
    _longueur = 0;
    _largeur = 0;
}

Image::Image(const string & name) {
    vector < vector < int >> rouge;
    vector < vector < int >> vert;
    vector < vector < int >> bleu;
    loadPicture(name, rouge, vert, bleu);
    _rouge = rouge;
    _vert = vert;
    _bleu = bleu;
    _longueur = rouge.size();
    _largeur = rouge[0].size();
    cout << "Image importee" << endl;
}

// Image::~Image() {
// cout << endl
//    << "*************** - Destruction de l'image - "
//      "********************************"
//<< endl;
//}

// ces methode permettre d'acceder aux composant d'une pixels grace à leur
// absysse et ordonnée dans l'image Utilisation de .at() pour que cela renvoie
// une erreur en cas d'indice invalide
int Image::getRouge(int x, int y) const {
    return (_rouge.at(x)).at(y);
}
int Image::getVert(int x, int y) const {
    return (_vert.at(x)).at(y);
}
int Image::getBleu(int x, int y) const {
    return (_bleu.at(x)).at(y);
}

// Ces methodes renvoient tout le vecteur d'une composante couleur d'une image
vector < vector < int >> Image::getVectRouge() const {
    return _rouge;
}
vector < vector < int >> Image::getVectVert() const {
    return _vert;
}
vector < vector < int >> Image::getVectBleu() const {
    return _bleu;
}

// Ces methodes permettent de modifier la valeur d'une composante d'un pixel
// identifié par son absysse et ordonnée
void Image::modifRouge(int index1, int index2, int valeur) {
    _rouge[index1][index2] = valeur;
}
void Image::modifVert(int index1, int index2, int valeur) {
    _vert[index1][index2] = valeur;
}
void Image::modifBleu(int index1, int index2, int valeur) {
    _bleu[index1][index2] = valeur;
}

// Créer une nouvelle image en gardant que les pixels rouge.
Image Image::composanteRouge() const {
    Image ImageRouge(_rouge, _vert, _bleu);
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[0].size(); j++) {
            // mise a 0 du vert et du bleu
            ImageRouge.modifVert(i, j, 0);
            ImageRouge.modifBleu(i, j, 0);
        }
    }
    return ImageRouge;
}

// renvoie VRAI si la couleur donnée en paramètre existe dans le vecteur
bool Image::estPresent(int rouge, int vert, int bleu) {
    bool present = false;
    int i = 0;
    // parcours tant que la couleur n'est pas trouvée ou que l'on n'a pas parcouru
    // toute l'image
    while (!(present) && i < _rouge.size()) {
        for (int j = 0; j < _rouge.size(); j++) {
            present = ((_rouge[i][j] == rouge) && (_vert[i][j] == vert) &&
                (_bleu[i][j] == bleu));
        }
        i++;
    }
    return present;
}

// affiche les 3 vector de l'image
void Image::display() {
    cout << "vecteur rouge : " << endl;
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[i].size() - 1; j++) {
            cout << _rouge[i][j] << " - ";
        }
        cout << _rouge[i][_rouge[i].size() - 1] << endl;
    }
    cout << "vecteur bleu : " << endl;
    for (int i = 0; i < _bleu.size(); i++) {
        for (int j = 0; j < _bleu[i].size() - 1; j++) {
            cout << _bleu[i][j] << " - ";
        }
        cout << _bleu[i][_bleu[i].size() - 1] << endl;
    }
    cout << "vecteur vert : " << endl;
    for (int i = 0; i < _bleu.size(); i++) {
        for (int j = 0; j < _bleu[i].size() - 1; j++) {
            cout << _bleu[i][j] << " - ";
        }
        cout << _bleu[i][_vert[i].size() - 1] << endl;
    }
}

// Créer une nouvelle image en niveaux de gris
Image Image::NiveauGris() const {
    int moyenne;
    Image ImageGris(_rouge, _vert, _bleu);
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[i].size(); j++) {
            // moyenne des 3 composantes du pixel pour donner du gris
            moyenne = (_rouge[i][j] + _bleu[i][j] + _vert[i][j]) / 3;
            ImageGris.modifRouge(i, j, moyenne);
            ImageGris.modifVert(i, j, moyenne);
            ImageGris.modifBleu(i, j, moyenne);
        }
    }
    return ImageGris;
}

// Télécharge l'image cible dans un fichier du nom entré en parametre en .ppm
// (!!! ne pas besoin de spécifier l'extension)
void Image::download(const string & name) const {
    cout << "creation du .ppm" << endl;
    ofstream output;
    string fileName = "Resultat/" + name + ".ppm";
    int hauteur = _rouge.size();
    int largeur = _rouge[0].size();
    output.open(fileName);
    output << "P3" << endl; // "P3" est la valeur pour spécifier que le format est
    // PPM (couleur) et ASCII
    output << largeur << " " << hauteur << endl; // Dimension de l'image
    output << 255 << endl; // valeur max de couleur
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            output << _rouge[i][j] << " " << _vert[i][j] << " " << _bleu[i][j] << " ";
        }
        output << endl;
    }
    output.close();
}

// Mets l'image en noir et blanc
Image Image::noirEtBlanc() const {
    int moyenne;
    Image ImageNoirEtBlanc(_rouge, _vert, _bleu);
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[i].size(); j++) {
            moyenne = (_rouge[i][j] + _bleu[i][j] + _vert[i][j]) / 3;
            if (moyenne <= 128) {
                ImageNoirEtBlanc.modifRouge(i, j, 0);
                ImageNoirEtBlanc.modifVert(i, j, 0);
                ImageNoirEtBlanc.modifBleu(i, j, 0);
            } else {
                ImageNoirEtBlanc.modifRouge(i, j, 255);
                ImageNoirEtBlanc.modifVert(i, j, 255);
                ImageNoirEtBlanc.modifBleu(i, j, 255);
            }
        }
    }
    return ImageNoirEtBlanc;
}
// Abaisse la luminosité de l'image
Image Image::luminosityDown() const {
    // facteur de baisse
    const int LUM = 2;
    Image ImageLumDown(_rouge, _vert, _bleu);
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge.size(); j++) {
            ImageLumDown.modifRouge(i, j, ImageLumDown.getRouge(i, j) / LUM);
            ImageLumDown.modifVert(i, j, ImageLumDown.getVert(i, j) / LUM);
            ImageLumDown.modifBleu(i, j, ImageLumDown.getBleu(i, j) / LUM);
        }
    }
    return ImageLumDown;
}
// Augmente la luminosité de l'image
Image Image::luminosityUp() const {
    // facteur d'augmentation
    const int LUM = 2;
    Image ImageLumUp(_rouge, _vert, _bleu);
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge.size(); j++) {
            // on vérifie a chaque fois que la valeur de la composante est inférieure
            // à 255 sinon on bloque a 255
            if (ImageLumUp.getRouge(i, j) * LUM <= 255) {
                ImageLumUp.modifRouge(i, j, ImageLumUp.getRouge(i, j) * LUM);
            } else {
                ImageLumUp.modifRouge(i, j, 255);
            }
            if (ImageLumUp.getVert(i, j) * LUM <= 255) {
                ImageLumUp.modifVert(i, j, ImageLumUp.getVert(i, j) * LUM);
            } else {
                ImageLumUp.modifVert(i, j, 255);
            }
            if (ImageLumUp.getBleu(i, j) * LUM <= 255) {
                ImageLumUp.modifBleu(i, j, ImageLumUp.getBleu(i, j) * LUM);
            } else {
                ImageLumUp.modifBleu(i, j, 255);
            }
        }
    }
    return ImageLumUp;
}
// Augmente le constrate de l'image cible
Image Image::contrasteUp() const {
    const int CONSTRAST = 3;
    int distRouge;
    int distVert;
    int distBleu;
    int newRouge;
    int newVert;
    int newBleu;
    Image ContrasteUp(_rouge, _vert, _bleu);
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[i].size(); j++) {
            // on calcule les distances à 128
            distRouge = ContrasteUp.getRouge(i, j) - 128;
            distVert = ContrasteUp.getVert(i, j) - 128;
            distBleu = ContrasteUp.getBleu(i, j) - 128;
            // la nouvelle couleur est issue du produit de la distance par le facteur
            // de contraste et de la somme de 128
            newRouge = distRouge * CONSTRAST + 128;
            newVert = distVert * CONSTRAST + 128;
            newBleu = distBleu * CONSTRAST + 128;
            // On vérifie que la nouvelle couleur est comprise entre 0 et 255 sinon on
            // bloque
            if (0 <= newRouge && newRouge <= 255) {
                ContrasteUp.modifRouge(i, j, newRouge);
            } else if (0 > newRouge) {
                ContrasteUp.modifRouge(i, j, 0);
            } else {
                ContrasteUp.modifRouge(i, j, 255);
            }
            if (0 <= newVert && newVert <= 255) {
                ContrasteUp.modifVert(i, j, newVert);
            } else if (0 > newVert) {
                ContrasteUp.modifVert(i, j, 0);
            } else {
                ContrasteUp.modifVert(i, j, 255);
            }
            if (0 <= newBleu && newBleu <= 255) {
                ContrasteUp.modifBleu(i, j, newBleu);
            } else if (0 > newBleu) {
                ContrasteUp.modifBleu(i, j, 0);
            } else {
                ContrasteUp.modifBleu(i, j, 255);
            }
        }
    }
    return ContrasteUp;
}
// Diminue le constrate de l'image cible
Image Image::contrasteDown() const {
    const int CONSTRAST = 3;
    int distRouge;
    int distVert;
    int distBleu;
    int newRouge;
    int newVert;
    int newBleu;
    Image ContrasteDown(_rouge, _vert, _bleu);
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[i].size(); j++) {
            // on calcule les distance à 128
            distRouge = ContrasteDown.getRouge(i, j) - 128;
            distVert = ContrasteDown.getVert(i, j) - 128;
            distBleu = ContrasteDown.getBleu(i, j) - 128;
            // la nouvelle couleur est issue du produit de la distance par le facteur
            // de contraste et de la somme de 128
            newRouge = distRouge / CONSTRAST + 128;
            newVert = distVert / CONSTRAST + 128;
            newBleu = distBleu / CONSTRAST + 128;
            // On vérifie que la nouvelle couleur est comprise entre 0 et 255 sinon on
            // bloque
            if (0 <= newRouge && newRouge <= 255) {
                ContrasteDown.modifRouge(i, j, newRouge);
            } else if (0 > newRouge) {
                ContrasteDown.modifRouge(i, j, 0);
            } else {
                ContrasteDown.modifRouge(i, j, 255);
            }
            if (0 <= newVert && newVert <= 255) {
                ContrasteDown.modifVert(i, j, newVert);
            } else if (0 > newVert) {
                ContrasteDown.modifVert(i, j, 0);
            } else {
                ContrasteDown.modifVert(i, j, 255);
            }
            if (0 <= newBleu && newBleu <= 255) {
                ContrasteDown.modifBleu(i, j, newBleu);
            } else if (0 > newBleu) {
                ContrasteDown.modifBleu(i, j, 0);
            } else {
                ContrasteDown.modifBleu(i, j, 255);
            }
        }
    }
    return ContrasteDown;
}

void loadPicture(const string & picture, vector < vector < int >> & red,
    vector < vector < int >> & green, vector < vector < int >> & blue) {
    // Declaration des variables
    string line; // pour recuperer les lignes du fichier image au format .ppm, qui
    // est code en ASCII.
    string format; // pour recuperer le format de l'image : celui-ci doit être de
    // la forme P3
    string name; // au cas où l'utilisateur se trompe dans le nom de l'image a
    // charger, on redemande le nom.
    int taille;
    vector < int > mypixels; // pour recuperer les donnees du fichier de maniere
    // lineaire. On repartira ensuite ces donnees dans les
    // tableaux correspondants
    ifstream entree; // Declaration d'un "flux" qui permettra ensuite de lire les
    // donnees de l'image.
    int hauteur; // pour bien verifier que l'image est carree, et de taille
    // respectant les conditions fixees par l'enonce
    // Initialisation des variables
    name = "Sources/" + picture + ".ppm";
    // Permet d'ouvrir le fichier portant le nom picture
    // ouverture du fichier portant le nom picture
    entree.open(name);
    // On verifie que le fichier a bien ete ouvert. Si cela n'est pas le cas, on
    // redemande un nom de fichier valide
    while (!entree) {
        // cin.rdbuf(oldbuf);
        cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
        cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention, le fichier "
        "doit etre au format .ppm (P3)" <<
        endl;
        cout << "Nom de l'image : ";
        cin >> name;
        name = "Sources/" + name + ".ppm";
        entree.open(name); // relance
    }
    // Lecture du nombre definissant le format (ici P3)
    entree >> format;
    // on finit de lire la ligne (caractere d'espacement)
    getline(entree, line);
    // Verification de la présence du commentaire
    // si present on l'esquive sinon on recupere les dimmensions
    getline(entree, line);
    if (line[0] != '#') {
        istringstream iss(line);
        iss >> taille >> hauteur;
    } else {
        entree >> taille >> hauteur;
    }
    // lecture des dimensions
    getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    // On verifie que l'image a une taille qui verifie bien les conditions
    // requises par l'enonce. Si cela n'est pas le cas, on redemande un fichier
    // valide, et ce, tant que necessaire.
    while (format != "P3") {
        if (format != "P3") {
            cerr << "Erreur! L'image que vous nous avez donnee a un format ne "
            "verifiant pas les conditions requises." <<
            endl;
            cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et "
            "non en brut." <<
            endl;
        }
        entree.close();
        // On va redemander un nom de fichier valide.
        do {
            cerr << "Veuillez redonner un nom de fichier qui respecte les conditions "
            "de format et de taille. Attention, le fichier doit etre au "
            "format .ppm (P3)" <<
            endl;
            cout << "Nom de l'image : ";
            cin >> name;
            name = "Sources/" + name + ".ppm";
            entree.open(name); // relance
        } while (!entree);
        // Lecture du nombre definissant le format (ici P3)
        entree >> format;
        getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
        // Lecture du commentaire
        getline(entree, line);
        // lecture des dimensions
        entree >> taille >> hauteur; // relance
        getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    }
    // Lecture de la valeur max
    getline(entree, line);
    // Lecture des donnees et ecriture dans les tableaux :
    //  Pour plus de simplicite, on stocke d'abord toutes les donnees dans
    //  mypixels dans l'ordre de lecture puis ensuite on les repartira dans les
    //  differents tableaux.
    // Les donnees stockees dans mypixels sont de la forme RGB RGB RGB ....
    //  Il faudra donc repartir les valeurs R correspondant a la composante rouge
    //  de l'image dans le tableau red, de même pour G et B.
    int pix;
    mypixels.resize(3 * taille *
        hauteur); // taille fixe : on alloue une fois pour toutes
    for (int i = 0; i < 3 * taille * hauteur; i++) {
        entree >> pix;
        mypixels[i] = pix;
    }
    // Remplissage des 3 tableaux : on repartit maintenant les valeurs dans les
    // bonnes composantes Comme dans mypixels, les donnees sont stockees de la
    // maniere suivante : RGB RGB RGB, il faut mettre les valeurs correspondant a
    // la composante rouge dans red, ... Ainsi, les valeurs de la composante rouge
    // correspondent aux valeurs stockes aux indices congrus a 0 mod 3 dans
    // mypixels, que les valeurs de la composante verte correspond aux valeurs
    // stockes aux indices sont congrus a 1 mod 3, ...
    // les valeurs d'une ligne
    int val;
    red.resize(hauteur);
    green.resize(hauteur);
    blue.resize(hauteur);
    for (int i = 0; i < hauteur; i++) {
        vector < int > ligneR(taille);
        vector < int > ligneB(taille); // les lignes ont toutes la même taille
        vector < int > ligneG(taille);
        for (int j = 0; j < taille; j++) {
            val = mypixels[3 * j + 3 * taille * i];
            ligneR[j] = val;
            val = mypixels[3 * j + 1 + 3 * taille * i];
            ligneG[j] = val;
            val = mypixels[3 * j + 2 + 3 * taille * i];
            ligneB[j] = val;
        }
        red[i] = ligneR;
        green[i] = ligneG;
        blue[i] = ligneB;
    }
    // Informations a l'utilisateur pour dire que tout s'est bien passe
    cout << " L'image " << name << " a bien ete chargee dans les tableaux ." <<
        endl;
    entree.close();
}
// supprime le nombre de ligne rentrée en paramètre en bas de l'image
Image Image::rognerB(const int &val) {
    vector<vector<int>> rougeRogner = _rouge;
    vector<vector<int>> vertRogner = _vert;
    vector<vector<int>> bleuRogner = _bleu;
    Image ImageRognerB;

    if (val <= 0) {
        ImageRognerB = Image(rougeRogner, vertRogner, bleuRogner);
        cout << endl <<
            "La valeur entrée n'est pas valide, l'image n'a pas été modifiée " <<
            endl <<
            endl;
    } else if (val <= rougeRogner.size()) {  // Ajout de la vérification
        for (int i = 0; i < val; i++) {
            rougeRogner.pop_back();
            vertRogner.pop_back();
            bleuRogner.pop_back();
        }
        ImageRognerB = Image(rougeRogner, vertRogner, bleuRogner);
    } else {
        cout << endl <<
            "La valeur entree n'est pas valide, l'image n'a pas ete modifiee  " <<
            endl <<
            endl;
    }
    return ImageRognerB;
}


// supprime le nombre de ligne rentrée en paramètre à droite de l'image
Image Image::rognerD(const int &val) {
    vector<vector<int>> rougeRogner = _rouge;
    vector<vector<int>> vertRogner = _vert;
    vector<vector<int>> bleuRogner = _bleu;
    Image ImageRognerD;

    if (val <= 0) {
        ImageRognerD = Image(rougeRogner, vertRogner, bleuRogner);
        cout << endl <<
            "La valeur entree n'est pas valide, l'image n'a pas ete modifiee  " <<
            endl <<
            endl;
    } else {
        const int MAX = _rouge.size();
        for (int i = 0; i < MAX; i++) {
            if (val <= rougeRogner[i].size()) {  // vérification
                for (int j = 0; j < val; j++) {
                    rougeRogner[i].pop_back();
                    vertRogner[i].pop_back();
                    bleuRogner[i].pop_back();
                }
            } else {
                cout << endl <<
            "La valeur entree n'est pas valide, l'image n'a pas ete modifiee  " << endl << endl;
            }
        }
        ImageRognerD = Image(rougeRogner, vertRogner, bleuRogner);
    }
    return ImageRognerD;
}

// supprime le nombre de ligne rentrée en paramètre à gauche de l'image
Image Image::rognerG(const int &val) {
    vector<vector<int>> rougeRogner = _rouge;
    vector<vector<int>> vertRogner = _vert;
    vector<vector<int>> bleuRogner = _bleu;
    Image ImageRognerG;

    if (val <= 0 || val >= rougeRogner[0].size()) {
        ImageRognerG = Image(rougeRogner, vertRogner, bleuRogner);
        cout << endl <<
            "La valeur entree n'est pas valide, l'image n'a pas ete modifiee " <<
            endl <<
            endl;
    } else {
        const int MAX = _rouge.size();

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < val; j++) {
                rougeRogner[i].erase(rougeRogner[i].begin());
                vertRogner[i].erase(vertRogner[i].begin());
                bleuRogner[i].erase(bleuRogner[i].begin());
            }
        }
    }

    ImageRognerG = Image(rougeRogner, vertRogner, bleuRogner);
    return ImageRognerG;
}


// supprime le nombre de colonnes rentrées en paramètre en haut de l'image
Image Image::rognerH(const int &val) {
    vector<vector<int>> rougeRogner = _rouge;
    vector<vector<int>> vertRogner = _vert;
    vector<vector<int>> bleuRogner = _bleu;
    Image ImageRognerH;

    if (val <= 0) {
        ImageRognerH = Image(rougeRogner, vertRogner, bleuRogner);
        cout << endl <<
            "La valeur entrée n'est pas valide, l'image n'a pas été modifiée " <<
            endl <<
            endl;
    } else if (val <= rougeRogner.size()) {  // Ajout de la vérification
        rougeRogner.erase(rougeRogner.begin(), rougeRogner.begin() + val);
        vertRogner.erase(vertRogner.begin(), vertRogner.begin() + val);
        bleuRogner.erase(bleuRogner.begin(), bleuRogner.begin() + val);
    } else {
        cout << endl <<
            "La valeur entrée est trop grande, l'image n'a pas été modifiée " <<
            endl <<
            endl;
    }

    ImageRognerH = Image(rougeRogner, vertRogner, bleuRogner);
    return ImageRognerH;
}



// fait une rotation de l'images de 90 degrés vers la droite
Image Image::rotationD() const {
    // Definition des nouvelles dimensions, la hauteur devient la largeur et
    // inversement
    vector < vector < int >> rougeRotation(_rouge[0].size(),
        vector < int > (_rouge.size(), 0));
    vector < vector < int >> vertRotation(_vert[0].size(),
        vector < int > (_vert.size(), 0));
    vector < vector < int >> bleuRotation(_bleu[0].size(),
        vector < int > (_bleu.size(), 0));
    // les lignes deviennt les colonnes et les colonnes deviennent les lignes
    for (int i = 0; i < rougeRotation.size(); i++) {
        for (int j = _rouge.size() - 1; j >= 0; j--) {
            rougeRotation[i][j] = _rouge[_rouge[0].size() - 1 - j][i];
            vertRotation[i][j] = _vert[_vert[0].size() - 1 - j][i];
            bleuRotation[i][j] = _bleu[_bleu[0].size() - 1 - j][i];
        }
    }

    Image rotatedImage(rougeRotation, vertRotation, bleuRotation);
    return rotatedImage;
}
// fait une rotation de l'images de 90 degrés vers la gauche
Image Image::rotationG() const {
    // Definition des nouvelles dimensions, la hauteur devient la largeur et
    // inversement
    vector < vector < int >> rougeRotation(_rouge[0].size(),
        vector < int > (_rouge.size(), 0));
    vector < vector < int >> vertRotation(_vert[0].size(),
        vector < int > (_vert.size(), 0));
    vector < vector < int >> bleuRotation(_bleu[0].size(),
        vector < int > (_bleu.size(), 0));
    // les lignes deviennt les colonnes et les colonnes deviennent les lignes
    for (int i = 0; i < rougeRotation.size(); i++) {
        for (int j = 0; j < _rouge.size(); j++) {
            rougeRotation[i][j] = _rouge[j][_rouge[0].size() - 1 - i];
            vertRotation[i][j] = _vert[j][_vert[0].size() - 1 - i];
            bleuRotation[i][j] = _bleu[j][_bleu[0].size() - 1 - i];
        }
    }

    Image rotatedImage(rougeRotation, vertRotation, bleuRotation);
    return rotatedImage;
}
// retourne l'image en systétrie verticale
Image Image::retournementV() const {
    vector < vector < int >> rougeRetourne(_rouge.size(),
        vector < int > (_rouge[0].size(), 0));
    vector < vector < int >> vertRetourne(_vert.size(),
        vector < int > (_vert[0].size(), 0));
    vector < vector < int >> bleuRetourne(_bleu.size(),
        vector < int > (_bleu[0].size(), 0));
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = _rouge[0].size() - 1; j >= 0; j--) {
            rougeRetourne[i][j] = _rouge[i][_rouge[0].size() - 1 - j];
            vertRetourne[i][j] = _vert[i][_rouge[0].size() - 1 - j];
            bleuRetourne[i][j] = _bleu[i][_rouge[0].size() - 1 - j];
        }
    }
    Image ImageRetourne(rougeRetourne, vertRetourne, bleuRetourne);
    return ImageRetourne;
}
// retourne l'image en systétrie horizontale
Image Image::retournementH() const {
    vector < vector < int >> rougeRetourne(_rouge.size(),
        vector < int > (_rouge[0].size(), 0));
    vector < vector < int >> vertRetourne(_vert.size(),
        vector < int > (_vert[0].size(), 0));
    vector < vector < int >> bleuRetourne(_bleu.size(),
        vector < int > (_bleu[0].size(), 0));
    for (int i = 0; i < _rouge.size(); i++) {
        rougeRetourne[i] = _rouge[_rouge[0].size() - 1 - i];
        vertRetourne[i] = _vert[_rouge[0].size() - 1 - i];
        bleuRetourne[i] = _bleu[_rouge[0].size() - 1 - i];
    }
    Image ImageRetourne(rougeRetourne, vertRetourne, bleuRetourne);
    return ImageRetourne;
}

Image Image::agrandissement(int facteur) const {
    // Calculer les dimensions de la nouvelle image rétrécie
    int largeur = _rouge[0].size() * facteur;
    int hauteur = _rouge.size() * facteur;
    if (facteur <= 0) {
        // Renvoie une copie de l'image si le facteur n'est pas valide
        cout << "Le facteur d'agrandissement entre n'est pas valide, l'image n'a "
        "pas ete modifie " <<
        endl;
        return * this;
    }
    // Initialiser les matrices de couleurs rétrécis
    vector < vector < int >> rougeAgrandit(largeur, vector < int > (hauteur, 0));
    vector < vector < int >> vertAgrandit(largeur, vector < int > (hauteur, 0));
    vector < vector < int >> bleuAgrandit(largeur, vector < int > (hauteur, 0));

    // Boucles pour dupliquer les pixels de l'image d'origine
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[0].size(); j++) {
            for (int x = 0; x < facteur; x++) {
                for (int y = 0; y < facteur; y++) {
                    rougeAgrandit[i * facteur + x][j * facteur + y] = _rouge[i][j];
                    vertAgrandit[i * facteur + x][j * facteur + y] = _vert[i][j];
                    bleuAgrandit[i * facteur + x][j * facteur + y] = _bleu[i][j];
                }
            }
        }
    }

    Image ImageAgrandit(rougeAgrandit, vertAgrandit, bleuAgrandit);
    return ImageAgrandit;
}

Image Image::retrecissement(int facteur) const {
    // Calculer les dimensions de la nouvelle image rétrécie
    int newWidth = _rouge[0].size() / facteur;
    int newHeight = _rouge.size() / facteur;
    // Initialiser les matrices de couleurs rétrécis
    std::vector < std::vector < int >> rougeRetreci(newHeight,
        std::vector < int > (newWidth, 0));
    std::vector < std::vector < int >> vertRetreci(newHeight,
        std::vector < int > (newWidth, 0));
    std::vector < std::vector < int >> bleuRetreci(newHeight,
        std::vector < int > (newWidth, 0));
    if (facteur <= 0) {
        // Renvoie une copie de l'image si le facteur n'est pas valide
        cout << "Le facteur de retrecissement entre n'est pas valide, l'image n'a "
        "pas ete modifie " <<
        endl;
        return * this;
    }
    // Boucles pour parcourir l'image d'origine et fusionner les pixels
    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++) {
            // Variables pour calculer la moyenne des pixels dans le carré d'origine
            int sumRouge = 0, sumVert = 0, sumBleu = 0;
            // Parcourir le "carré" d'origine de taille "facteur"
            for (int x = 0; x < facteur; x++) {
                for (int y = 0; y < facteur; y++) {
                    // Accumuler les valeurs des pixels dans le carré d'origine
                    sumRouge += _rouge[i * facteur + x][j * facteur + y];
                    sumVert += _vert[i * facteur + x][j * facteur + y];
                    sumBleu += _bleu[i * facteur + x][j * facteur + y];
                }
            }
            // Calculer la moyenne des valeurs des pixels et les assigner à la
            // nouvelle image
            rougeRetreci[i][j] = sumRouge / (facteur * facteur);
            vertRetreci[i][j] = sumVert / (facteur * facteur);
            bleuRetreci[i][j] = sumBleu / (facteur * facteur);
        }
    }
    // Créer et retourner la nouvelle image rétrécie
    return Image(rougeRetreci, vertRetreci, bleuRetreci);
}

Image Image::reglageAuto() const {
    // Calcul de la luminosité moyenne de l'image
    double luminositeMoyenne = 0.0;
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[0].size(); j++) {
            luminositeMoyenne += (_rouge[i][j] + _vert[i][j] + _bleu[i][j]) / 3.0;
        }
    }
    luminositeMoyenne /= (_rouge.size() * _rouge[0].size());

    // Calcul des facteurs d'ajustement
    double facteurLuminosite = 128.0 / luminositeMoyenne;
    double facteurContraste = 255.0 / (255.0 - luminositeMoyenne);

    // Création de matrices pour stocker les valeurs ajustées
    vector < vector < int >> rougeAjuste(_rouge.size(),
        vector < int > (_rouge[0].size(), 0));
    vector < vector < int >> vertAjuste(_vert.size(), vector < int > (_vert[0].size(), 0));
    vector < vector < int >> bleuAjuste(_bleu.size(), vector < int > (_bleu[0].size(), 0));

    // Ajustement de chaque pixel de l'image
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[0].size(); j++) {
            // Ajustement de la luminosité
            rougeAjuste[i][j] = int(_rouge[i][j] * facteurLuminosite);
            vertAjuste[i][j] = int(_vert[i][j] * facteurLuminosite);
            bleuAjuste[i][j] = int(_bleu[i][j] * facteurLuminosite);

            // Ajustement du contraste
            rougeAjuste[i][j] =
                int((rougeAjuste[i][j] - luminositeMoyenne) * facteurContraste +
                    luminositeMoyenne);
            vertAjuste[i][j] =
                int((vertAjuste[i][j] - luminositeMoyenne) * facteurContraste +
                    luminositeMoyenne);
            bleuAjuste[i][j] =
                int((bleuAjuste[i][j] - luminositeMoyenne) * facteurContraste +
                    luminositeMoyenne);

            // Clipping des valeurs dans la plage [0, 255]
            rougeAjuste[i][j] = max(0, min(255, rougeAjuste[i][j]));
            vertAjuste[i][j] = max(0, min(255, vertAjuste[i][j]));
            bleuAjuste[i][j] = max(0, min(255, bleuAjuste[i][j]));
        }
    }

    // Création et retour d'une nouvelle instance d'Image avec les valeurs
    // ajustées
    return Image(rougeAjuste, vertAjuste, bleuAjuste);
}
// renvoie un vecteur correspondant a l'histogramme de l'image en niveau de gris
vector < int > Image::histogrammeGris() const {
    Image ImageHistogramme(_rouge, _vert, _bleu);
    ImageHistogramme = ImageHistogramme.NiveauGris(); /// récupération de limage en niveau de gris
    vector < int > histogramme(255); /// creation du vecteur histogramme
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[i].size(); j++)
            histogramme[ImageHistogramme.getRouge(i, j)] += 1;
    } /// ajoute 1 a chaque case du vecteur histogramme dans son pixel correspondant
    return histogramme;
}
// affiche le vecteur histogramme
void displayHistogramme(const vector < int > & histo) {
    vector < int > index;
    cout << "Histogramme : " << endl << "{";
    for (int i = 0; i < histo.size() - 1; i++) {
        cout << histo[i] << ", ";
        if (histo[i] != 0)
            index.push_back(i);
    }
    cout << histo[histo.size()] << " }" << endl;
}
// redefinition de l'opérateur == pour comparer 2 Image entre elles.
bool Image::operator == (const Image & img) {
    bool vecEqualRouge = true;
    bool vecEqualVert = true;
    bool vecEqualBleu = true;
    int i = 0;

    const int MAX = _rouge.size();

    vector < vector < int >> VectRouge = img.getVectRouge();
    vector < vector < int >> VectVert = img.getVectVert();
    vector < vector < int >> VectBleu = img.getVectBleu();

    if (MAX != VectRouge.size() || MAX != VectBleu.size() ||
        MAX != VectVert.size()) {
        return false;
    }
    while (i < MAX && (vecEqualRouge && vecEqualBleu && vecEqualVert)) {
        vecEqualRouge = (_rouge[i] == VectRouge[i]);
        vecEqualBleu = (_bleu[i] == VectBleu[i]);
        vecEqualVert = (_vert[i] == VectVert[i]);
        i++;
    }

    return (vecEqualRouge && vecEqualBleu && vecEqualVert);
}

// créer une copie de l'image d'origine
Image Image::copie() {
    Image ImageCp(_rouge, _vert, _bleu);
    return ImageCp;
}
