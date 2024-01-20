#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <fstream>

#include <string>

#include <vector>

using namespace std;

class Image {
    // Vecteur 2D RVB de l'image
    vector < vector <int> > _rouge;
    vector < vector <int> > _vert;
    vector < vector <int> > _bleu;
    // Taille de l'image
    int _longueur;
    int _largeur;

    public:
        // Constructeur
        Image(const vector < vector <int> > & rouge,
            const vector < vector <int> > & vert,
                const vector < vector <int> > & bleu);
    Image();
    Image(const string & name);
    // Constructeur vide
    // DESTRUCTEUR //~Image();
    // Prend en parametre une valeur x et y et renvoie la valeur du pixel
    // correspondant
    int getRouge(int x, int y) const;
    int getVert(int x, int y) const;
    int getBleu(int x, int y) const;

    // renvoie le vecteur entier d'une couleur de l'image
    vector < vector <int> > getVectRouge() const;
    vector < vector <int> > getVectVert() const;
    vector < vector <int> > getVectBleu() const;

    // Creer une nouvelle image a partir de l'image cible seulement avec la
    // couleur rouge
    Image composanteRouge() const;

    // renvoie un booleen si les couleurs rentre en parametre sont present dans
    // l'image
    bool estPresent(int, int, int);

    // Change la valeur du pixel de couleur donne en parametre par la valeur
    // donnee par le dernier int en parametre
    void modifRouge(int, int, int);
    void modifVert(int, int, int);
    void modifBleu(int, int, int);

    // Affiche l'ensemble des 3 vecteurs de l'image
    void display();
    // Télécharge l'image cible dans un fichier du nom entré en parametre en .ppm
    void download(const string & name) const;

    // Mets l'image en noir et blanc
    Image noirEtBlanc() const;

    // Renvoie une l'image cible en niveaux de gris
    Image NiveauGris() const;

    // Abaisse la luminosité de l'image cible
    Image luminosityDown() const;

    // Augmente la luminosité de l'image cible
    Image luminosityUp() const;

    // Augmente le constrate de l'image cible
    Image contrasteUp() const;

    // Réduit le constrate de l'image cible
    Image contrasteDown() const;

    // Renvoie un vecteur representant l'histogramme de l'image en niveau de gris
    vector < int > histogrammeGris() const;

    // rogne l'image par le bas
    Image rognerB(const int & );

    // rogne l'image pas la droite
    Image rognerD(const int & );

    // rogne l'image par le haut
    Image rognerH(const int & );

    // rogne l'image par la gauche
    Image rognerG(const int & );

    // fait une rotation de l'images de 90 degrés vers la droite
    Image rotationD() const;

    // fait une rotation de l'images de 90 degrés vers la gauche
    Image rotationG() const;

    // retourne l'image en systétrie verticale
    Image retournementV() const;

    // retourne l'image en systétrie horizontale
    Image retournementH() const;

    // Créer une nouvelle image agrandit à partir d'un facteur d'entier.
    Image agrandissement(int facteur) const;

    // Créer une nouvelle image rétrecis à partir d'un facteur d'entier.
    Image retrecissement(int facteur) const;

    // Le réglage automatique effectue un réglage de l’image de
    // la façon suivante :
    //   - La luminosité est changée de façon à avoir une luminosité moyenne de
    //   l’ensemble des pixels de 128.
    //   - Le contraste est augmenté autant que possible sans que la valeur d’une
    //   composante d’un pixel de l’image dépasse 255 ou 0.
    Image reglageAuto() const;

    // redefinition de l'operateur == pour tester l'équalité entre 2 imagex
    bool operator == (const Image & );

    // créer une copie de l'image d'origine
    Image copie();
};
// affiche le vecteur représentant l'histogramme de l'image en niveau de gris
void displayHistogramme(const vector <int> & );

// permets d'importer une image ppm
void loadPicture(const string & picture, vector < vector <int> > & red,
    vector < vector <int> > & green, vector < vector <int> > & blue);

#endif
