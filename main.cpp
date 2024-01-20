#define MENU

#include "filtre.h"

#include "image.h"

#include "menu.h"

#include <fstream>

#include <iostream>

#include <stdexcept>

#include <string>

// https://thomasebsmith.github.io/ppm-converter/

using namespace std;

#ifdef MENU
int main() {
    // -------DECLARATIONS DES VARIABLES UTILES -------
    const vector < vector <float> > action = {
        {
            1.0 / 16,
            1.0 / 8,
            1.0 / 16
        },
        {
            1.0 / 8,
            1.0 / 4,
            1.0 / 8
        },
        {
            1.0 / 16,
            1.0 / 8,
            1.0 / 16
        }
    };
    int rayon = 1;
    Filtre Flou(action, rayon);
    string imageName;
    char choix;
    bool poursuite = true;
    vector < Image > historique;
    // ------------------------------------------------

    cout << endl <<
        "----------- Bienvenue sur votre editeur d'image ----------" << endl <<
        endl;

    cout << " ----- Fonctionnement -----" << endl;
    cout << " - Les Images sources doivent se trouver dans le dossier 'Sources' " <<
        endl;
    cout << " - Le Resultat de vos modifications se trouverons dans le dossier "
    "'Resultat' " <<
    endl;
    cout << " - ATTENTION : Lors de l'enregistrement, si le nom est deja utilise "
    "l'image precedente sera ecrasee" <<
    endl;
    cout << " --------------------------" << endl << endl;

    imageName = choixImage();
    Image Image(imageName);
    historique.push_back(Image);
    do {
        choix = menu();

        cout << endl;
        switch (choix) {
        case 'A':
            cout << "Reglages en cours... ";
            Image = Image.reglageAuto();
            cout << "Reglages termine !" << endl;
            break;
        case 'r':
            cout << "Isolation du rouge... ";
            Image = Image.composanteRouge();
            cout << "Isolation terminee !" << endl;
            break;
        case 'G':
            cout << "Application du niveau de gris... ";
            Image = Image.NiveauGris();
            cout << "Application terminee !" << endl;
            break;
        case 'B':
            cout << "Mise en noir et blanc... ";
            Image = Image.noirEtBlanc();
            cout << "Application terminee !" << endl;
            break;
        case 'L':
            cout << "Voulez vous augmenter ou diminuer la luminosite ?" << endl;
            cout << "A augmente ; D diminuer" << endl;
            cout << "Faites votre choix : ";
            char changeL;
            cin >> changeL;
            switch (tolower(changeL)) {
            case 'd':
                Image = Image.luminosityDown();
                cout << "La luminosite a ete baissee" << endl << endl;
                break;
            case 'a':
                Image = Image.luminosityUp();
                cout << "La luminosite a ete augmentee" << endl << endl;
                break;
            default:
                cout << "Changements annules" << endl;
                break;
            }
            break;
        case 'C':
            cout << "Voulez vous augmenter ou diminuer le contraste ?" << endl;
            cout << "A augmente ; D diminuer" << endl;
            cout << "Faites votre choix : ";
            char changeC;
            cin >> changeC;
            switch (tolower(changeC)) {
            case 'd':
                Image = Image.contrasteDown();
                cout << "Le constraste a ete baisse" << endl << endl;
                break;
            case 'a':
                Image = Image.contrasteUp();
                cout << "Le contraste a ete augmente" << endl << endl;
                break;
            default:
                cout << "Changements annules" << endl;
                break;
            }
            break;
        case 'R':
            char rognage;
            cout << "Comment voulez vous rogner ? " << endl;
            cout << "H : rognage depuis le haut" << endl;
            cout << "B : rognage depuis le bas" << endl;
            cout << "D : rognage depuis la droite" << endl;
            cout << "G : rognage depuis la gauche" << endl;
            cout << "autre : annulation" << endl;
            cout << "Faites votre choix : ";
            cin >> rognage;
            int valeurRognage;
            switch (rognage) {
            case 'H':
                cout << "Entrez une valeur a rogner (>0): ";
                cin >> valeurRognage;
                Image = Image.rognerH(valeurRognage);
                break;
            case 'B':
                cout << "Entrez une valeur a rogner (>0): ";
                cin >> valeurRognage;
                Image = Image.rognerB(valeurRognage);
                break;
            case 'D':
                cout << "Entrez une valeur a rogner (>0): ";
                cin >> valeurRognage;
                Image = Image.rognerD(valeurRognage);
                break;
            case 'G':
                cout << "Entrez une valeur a rogner (>0): ";
                cin >> valeurRognage;
                //                        Image = Image.rognerG(valeurRognage);
                break;
            default:
                cout << "Annulation" << endl;
                break;
            }
            break;
        case 'T':
            cout << "Dans quel sens voulez-vous effectuer la rotation ?" << endl;
            cout << "D vers la droite ; G vers la gauche" << endl;
            cout << "Faites votre choix : ";
            char sens;
            cin >> sens;
            switch (tolower(sens)) {
            case 'd':
                Image = Image.rotationD();
                cout << "La rotation vers la droite a ete effectue" << endl << endl;
                break;
            case 'g':
                Image = Image.rotationG();
                cout << "La rotation vers la gauche a ete effectue" << endl << endl;
                break;
            default:
                cout << "Rotation annulee" << endl;
                break;
            }
            break;
        case 'P':
            cout << "Dans quel sens voulez-vous effectuer le retournement ?" << endl;
            cout << "V vertical ; H horizontal" << endl;
            cout << "Faites votre choix : ";
            cin >> sens;
            switch (tolower(sens)) {
            case 'v':
                Image = Image.retournementV();
                cout << "Le retournement vertical a ete effectue" << endl << endl;
                break;
            case 'h':
                Image = Image.retournementH();
                cout << "La retournement horizontal a ete effectue" << endl << endl;
                break;
            default:
                cout << "Retournement annule" << endl;
                break;
            }
            break;
        case 't':
            cout << "Voulez-vous agrandir ou retrecir l'image ?" << endl;
            cout << "A agrandir ; R retrecir" << endl;
            cout << "Faites votre choix : ";
            cin >> sens;
            int facteur;
            switch (tolower(sens)) {
            case 'a':
                cout << "Entrez un facteur d'agrandissement (>0) : ";
                cin >> facteur;
                Image = Image.agrandissement(facteur);
                cout << "Le changement a ete effectue" << endl << endl;
                break;
            case 'r':
                cout << "Entrez un facteur de reduction (>0) : ";
                cin >> facteur;
                Image = Image.retrecissement(facteur);
                cout << "Le changement a ete effectue" << endl << endl;
                break;
            default:
                cout << "changement de taille annule" << endl;
                break;
            }
            break;
        case 'F':
            cout << "Floutage en cours... ce processus peut prendre un certain "
            "temps..." <<
            endl;
            Image = Flou.application(Image);
            cout << "Floutage termine !" << endl;
            break;
        case 'H':
            displayHistogramme(Image.histogrammeGris());
            break;
        case 'N':
            cout << "Voulez vous faire une copie de l'image orginale ou de l'image actuelle ?" << endl;
            cout << "O originale ; A actuel" << endl;
            cout << "Faites votre choix : ";
            cin >> sens;
            switch (tolower(sens)) {
            case 'a':
                cout << "Vous allez enregistrer l'image actuelle " << endl;
                enregistrement(Image);
                break;
            case 'o':
                cout << "Vous allez enregistrer l'image originale " << endl;
                enregistrement(historique[0]);
                break;
            default:
                cout << "changement de taille annule" << endl;
                break;
            }
            break;
        case 'Z':
            if (historique.size() > 1) {
                historique.pop_back();
                Image = historique[historique.size() - 1];
            }
            break;
        case 'Q':
            cout << "Quitter " << endl;
            break;
        default:
            cout << "Votre choix n'opere aucune action" << endl;
        }
        if (choix != 'Z') {
            historique.push_back(Image);
        }
        cout << endl;
        cout << "Voulez-vous continuer l'edition ? Oui O; le reste quittera "
        "l'edition. " <<
        "Votre choix : ";
        cin >> choix;
        poursuite = tolower(choix) == 'o';

    } while (poursuite);

    choix = enregistrement(Image);

    return 0;
}

#else
/// main de test automatique pour l'activer il faut commenter la ligne 1 (#define MENU)
int main() {
    cout << endl <<
        "----- Initialisation de l'Image "
    "-----------------------------------------" <<
    endl;
    Image PremiereImage({
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            255,
            255
        },
        {
            0,
            255,
            255,
            255
        },
        {
            255,
            255,
            255,
            255
        }
    }, {
        {
            0,
            0,
            255,
            255
        },
        {
            0,
            255,
            255,
            255
        },
        {
            255,
            255,
            255,
            0
        },
        {
            255,
            255,
            0,
            0
        }
    }, {
        {
            255,
            255,
            0,
            0
        },
        {
            255,
            0,
            0,
            0
        },
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            0,
            0
        }
    });

    Image ImageComposanteRouge({
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            255,
            255
        },
        {
            0,
            255,
            255,
            255
        },
        {
            255,
            255,
            255,
            255
        }
    }, {
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            0,
            0
        }
    }, {
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            0,
            0
        }
    });
    cout
        <<
        endl <<
        "----- test Composante rouge -----------------------------------------" <<
        endl;
    Image PrmComposanteRouge;
    PrmComposanteRouge = PremiereImage.composanteRouge();
    if (ImageComposanteRouge == PrmComposanteRouge)
        cout << "TEST REUSSI : ImageComposanteRouge fonctionne correctement" <<
        endl;
    else
        cout <<
        "ECHEC DU TEST : ImageComposanteRouge ne fonctionne pas correctement" <<
        endl;

    cout << endl <<
        "----- test Niveau de gris -----------------------------------------" <<
        endl;

    Image ImageNiveauGris({
        {
            85,
            85,
            85,
            85
        },
        {
            85,
            85,
            170,
            170
        },
        {
            85,
            170,
            170,
            85
        },
        {
            170,
            170,
            85,
            85
        }
    }, {
        {
            85,
            85,
            85,
            85
        },
        {
            85,
            85,
            170,
            170
        },
        {
            85,
            170,
            170,
            85
        },
        {
            170,
            170,
            85,
            85
        }
    }, {
        {
            85,
            85,
            85,
            85
        },
        {
            85,
            85,
            170,
            170
        },
        {
            85,
            170,
            170,
            85
        },
        {
            170,
            170,
            85,
            85
        }
    });

    Image PrmNiveauGris;
    PrmNiveauGris = PremiereImage.NiveauGris();
    if (ImageNiveauGris == PrmNiveauGris)
        cout << "TEST REUSSI : ImageNiveauGris fonctionne correctement" << endl;
    else
        cout << "ECHEC DU TEST : ImageNiveauGris ne fonctionne pas correctement" <<
        endl;
    cout << endl <<
        "----- test Rogner Bas -----------------------------------------" <<
        endl;

    Image ImageRognerBas({
        {
            0,
            0,
            0,
            0
        },
        {
            0,
            0,
            255,
            255
        },
        {
            0,
            255,
            255,
            255
        }
    }, {
        {
            0,
            0,
            255,
            255
        },
        {
            0,
            255,
            255,
            255
        },
        {
            255,
            255,
            255,
            0
        }
    }, {
        {
            255,
            255,
            0,
            0
        },
        {
            255,
            0,
            0,
            0
        },
        {
            0,
            0,
            0,
            0
        }
    });

    Image PrmRognerBas;
    PrmRognerBas = PremiereImage.rognerB(1);
    if (ImageRognerBas == PrmRognerBas)
        cout << "TEST REUSSI : ImageRognerBas fonctionne correctement" << endl;
    else
        cout << "ECHEC DU TEST : ImageRognerBas ne fonctionne pas correctement" <<
        endl;

    cout << endl << "------- TESTS MANUELS DES FONCTIONNALITES -------" << endl << endl;

    PremiereImage.noirEtBlanc().download("test-noirEtBlanc");
    cout << "Test noirEtBlanc - EFFECTUE" << endl;

    PremiereImage.luminosityDown().download("test-luminosityDown");
    cout << "Test luminosityDown - EFFECTUE" << endl << endl;

    PremiereImage.luminosityUp().download("test-luminosityUp");
    cout << "Test luminosityUp - EFFECTUE" << endl;

    PremiereImage.contrasteUp().download("test-contrasteUp");
    cout << "Test contrasteUp - EFFECTUE" << endl << endl;

    PremiereImage.contrasteDown().download("test-contrasteDown");
    cout << "Test contrasteDown - EFFECTUE" << endl << endl;

    PremiereImage.rognerH(1).download("test-rognerH");
    cout << "Test rognerH - EFFECTUE" << endl << endl;

    PremiereImage.rognerD(1).download("test-rognerD");
    cout << "Test rognerD - EFFECTUE" << endl << endl;

    PremiereImage.rognerG(1).download("test-rognerG");
    cout << "Test rognerG - EFFECTUE" << endl << endl;

    PremiereImage.rotationD().download("test-noirEtBlanc");
    cout << "Test rotationD - EFFECTUE" << endl << endl;

    PremiereImage.rotationG().download("test-rotationG");
    cout << "Test rotationG - EFFECTUE" << endl << endl;

    PremiereImage.retournementV().download("test-retournementV");
    cout << "Test retournementV - EFFECTUE" << endl << endl;

    PremiereImage.retournementH().download("test-retournementH");
    cout << "Test retournementH - EFFECTUE" << endl << endl;

    PremiereImage.agrandissement(2).download("test-agrandissement");
    cout << "Test agrandissement - EFFECTUE" << endl << endl;

    PremiereImage.retrecissement(2).download("test-retrecissement");
    cout << "Test retrecissement - EFFECTUE" << endl << endl;

    PremiereImage.reglageAuto().download("test-reglageAuto");
    cout << "Test reglageAuto - EFFECTUE" << endl << endl;

    PremiereImage.copie().download("test-copie");
    cout << "Test copie - EFFECTUE" << endl << endl;

    const vector < vector <float> > action = {
        {
            1.0 / 16, 1.0 / 8, 1.0 / 16
        },
        {
            1.0 / 8,
            1.0 / 4,
            1.0 / 8
        },
        {
            1.0 / 16,
            1.0 / 8,
            1.0 / 16
        }
    };
    int rayon = 1;
    Filtre Flou(action, rayon);

    Flou.application(PremiereImage).download("test-flou");
    cout << "Test noirEtBlanc - EFFECTUE" << endl << endl;

    return 0;
}

#endif
