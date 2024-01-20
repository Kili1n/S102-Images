#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>
#include "filtre.h"
#include "image.h"
using namespace std;

string choixImage();

char menu();

char enregistrement(const Image & Image);

#endif // MENU_H_INCLUDED
