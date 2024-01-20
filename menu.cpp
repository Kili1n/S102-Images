#include "menu.h"

#include "filtre.h"

#include "image.h"

#include <fstream>

#include <iostream>

#include <stdexcept>

#include <string>

#include <vector>

using namespace std;

string choixImage() {
    string imageName;
    cout << "Entrez le nom de l'image a modifier : ";
    cin >> imageName;
    if (imageName.length() >= 4 &&
        imageName.substr(imageName.length() - 4) == ".ppm") {
        imageName = imageName.substr(0, imageName.length() - 4);
    }
    cout << "Nous allons travailler sur : " << imageName << endl;
    return imageName;
}

char menu() {
    // DECLARATION DES VARIABLES NECESSAIRES AU MENU
    char choix;
    // --------------------------------------------

    cout << endl << "Voici les differents traitements possible : " << endl;
    cout << " A : reglage auto" << endl;
    cout << " r : isoler le rouge" << endl;
    cout << " G : appliquer un niveau de gris" << endl;
    cout << " B : mettre en noir et blanc" << endl;
    cout << " L : modifier la luminosite" << endl;
    cout << " C : modifier le contraste" << endl;
    cout << " R : rogner l'image" << endl;
    cout << " T : faire une rotation" << endl;
    cout << " P : retourner l'image" << endl;
    cout << " t : modifier la taille" << endl;
    cout << " H : afficher l'Histogramme gris" << endl;
    cout << " F : appliquer un filtre flou" << endl;
    cout << " N : Faire une copie" << endl;
    cout << " Z : annuler la derniere modification " << endl;
    cout << " Q : Quitter l'edition " << endl;
    cout << "Que voulez vous faire ? Entrez la lettre correspondante : ";
    cin >> choix;

    switch (choix) {
    case 'A':
        cout << "Reglage automatique de la luminosite et du contraste" << endl;
        break;
    case 'r':
        cout << "Vous avez choisi d'isoler le rouge" << endl;
        break;
    case 'G':
        cout << "Vous avez choisi d'appliquer un niveau de gris" << endl;
        break;
    case 'B':
        cout << "Vous avez choisi de mettre en noir et blanc" << endl;
        break;
    case 'L':
        cout << "Vous avez choisi d'augmenter la luminosite" << endl;
        break;
    case 'l':
        cout << "Vous avez choisi de diminuer la luminosite" << endl;
        break;
    case 'C':
        cout << "Vous avez choisi d'augmenter le contraste" << endl;
        break;
    case 'c':
        cout << "Vous avez choisi de diminuer le contraste" << endl;
        break;
    case 'R':
        cout << "Vous avez choisi de rogner l'image" << endl;
        break;
    case 'T':
        cout << "Vous avez choisi d'effectuer une rotation" << endl;
        break;
    case 'P':
        cout << "Vous avez choisi de retourner l'image" << endl;
        break;
    case 't':
        cout << "Vous avez choisi de modifier la taille de l'image" << endl;
        break;
    case 'H':
        cout << "Vous avez choisi d'afficher l'histogramme Gris de l'image" << endl;
        break;
    case 'Z':
        cout << "Annulation de la derniere modification" << endl;
        break;
    case 'N':
        cout << "Vous avez choisi de copier l'image" << endl;
        break;
    case 'F':
        cout << "Vous avez choisi de flouter l'image" << endl;
        break;
    case 'Q':
        cout << "Quitter " << endl;
        break;
    default:
        cout << "autre" << endl;
    }
    //     SI BESOIN D'UN ENREGISTREMENT INTERMEDAIRE
    //    cout << "Voulez vous enregistrer les modifications ? (O/N)" << endl;
    //    cin >> choix;
    //    if (tolower(choix) == 'o'){
    //        string newName;
    //        cout << "Entrez un nom pour l'image : ";
    //        cin >> newName;
    //        Image.download(newName);
    //    }
    return choix;
}

char enregistrement(const Image & Image) {
    char choix;
    cout << "Voulez vous enregistrer l'image ? (Oui : O ; Non N)" <<
        endl;
    cout << "Entrez votre choix : ";
    cin >> choix;
    cout << endl;
    while (choix != 'O' && choix != 'N') {
        cout << "Ce n'est pas un choix correcte, Oui : O ; Non N " << endl <<
            "Reessayez : ";
        cin >> choix;
    }
    if (choix == 'O') {
        string newName;
        cout << endl << "Entrez un nom pour votre nouvelle image. " << endl;
        cout << "ATTENTION, un enregistrement avec un nom deja attribue ECRASERA "
        "l'image existante " <<
        endl;
        cout << "Entrez un nom :";
        cin >> newName;
        cout << "L'image sera enregistre sous le nom \" " << newName << " \". " <<
            endl;
        cout << "Validez vous cette action ? Oui O ; autre annule l'action " <<
            " Faites votre choix : ";
        cin >> choix;
        if (choix == 'O') {
            Image.download(newName);
            cout << "Enregistrement effectue !!!" << endl << endl;
        } else {
            cout << "Action annulee" << endl << endl;
        }
    }
    return choix;
}
