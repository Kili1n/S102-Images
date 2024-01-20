# Projet S102 - Traitement d'images

Ceci est un guide pour l'utilisation de notre programme. Vous y retrouverez une liste des fonctionnalités ainsi que des recommandations d'usage. 
Vous y trouverez également une presentation du projet. 

## Sommaire

- [Présentation du Projet](#presentation-du-projet)
- [Guide de Fonctionnement](#guide-de-fonctionnement)
- [Recommandations d'usage](#recommandations-dusage)
- [Les Fonctionnalités](#les-fonctionnalités)
  - [Réglage Automatique](#réglage-automatique)
  - [Isolation du Rouge](#isolation-du-rouge)
  - [Niveau de Gris](#niveau-de-gris)
  - [Noir et Blanc](#noir-et-blanc)
  - [Histogramme Gris](#histogramme-gris)
  - [Luminosité](#luminosité)
  - [Contraste](#contraste)
  - [Rognage](#rognage)
  - [Rotation](#rotation)
  - [Retournement](#retournement)
  - [Agrandissement](#Agrandissement)
  - [Retrecissement](#retrecissement)
  - [Taille](#taille)
  - [Flou](#flou)
  - [Copie](#copie)
  - [Historique](#annulation)
- [Auteur](#auteur)


## Presentation du Projet 

Le but de ce projet est de se familiariser avec les classes, le language c++ et de manipuler des vecteurs à plusieurs dimensions. 
Le projet est réalisé en groupe de deux pour apprendre à collaborer sur un meme projet. 

Le coeur du projet est la réalisation d'un programme de "traitement" d'image au format PPM en implémentant un certain nombre de fonctionnalités. 

## Guide de Fonctionnement 

### À savoir 

Le programme traite les images **.PPM** lisible par l'etre humain, l'entête de ce fichier doit donc contenir **P3** en premiere ligne. 
Ensuite la seconde ligne doit contenir les **dimensions de l'images**. La troisième ligne contient la **composante de couleur maximale** (généralement 255). 
Le fichier peut eventuellement contenir un commentaire **entre le type de fichier et les dimensions**.

### Emplacement des Fichiers 

Il existe deux dossiers d'emplacements : **Sources** et **Resultat**. 
Dans le dossier **Sources** se trouve l'entrée des images, les images à traiter doivent être placées dans ce dossier pour être lues. 
Dans le dossier **Resultat**, comme son nom l'indique, va se trouver les fichiers sauvegardés lors de l'execution. 

### Déroulement du programme 

Au lancement du programme, il vous sera demandé d'entrer un nom de fichier, il n'est pas necessaire d'entrer l'extension (.ppm). Ce fichier doit **IMPERATIVEMENT** se trouver dans le dossier **Sources**. Des images sont déjà à votre disposition dans ce dernier mais vous pouvez toujours en importer en les placant dans ce dossier. 

En fois le nom de fichier entré, un menu presentant les differentes fonctionnalités apparaitra. Vous devrez rentrer le caractere correspondant à la fonctionnalité et **UNIQUEMENT** ce caractère. Le programme est la majeur partie du temps sensible à la casse. 

En fonction de votre choix un nouveau sous menu apparaitra pour vous proposer des variantes de la fonctionnalite. De meme vous devrez rentrer le caractere correspondant. 
Il est possible qu'une valeur vous soit demandée, si une contrainte est spécifier vous devez **IMPERATIVEMENT** la respecter ou votre modification ne sera pas effectuée. 

Une fois votre modification effectuée, vous pourrez continuer l'édition en entrant **O** ou quitter en entrant un autre caractère. 
Si vous faites le choix de continuer **O**, le menu des fonctionnalité apparaitra à nouveau. 

Lorsque que vous quitterez vous pourrez soit enregistrer les modifcations avec **O** ou ne pas sauvegarder avec **N**. 
Si vous choississez de ne pas sauvegarder **N**, le programme s'arretera. 

Si vous choississez d'enregistrer votre nouvelle images, il vous sera demandé d'entrer un nom pour votre nouvelle image. 
**ATTENTION : Si vous enregister votre image avec un nom déjà attribué, l'ancienne image sera DEFINITIVEMENT SUPPRIMÉE**

Un fois l'image enregistrer, le programme s'arretera. Libre à vous ensuite de le relancer pour éditer une nouvelle image. 

## Recommandations d'usage

Si vous importez une image, veillez à ce qu'elle ne soit pas trop volumineuse pour éviter les problèmes de mémoire ou des temps de chargement très longs. Nous vous conseillons une **taille < 5 000 Ko**.

**ATTENTION : Si vous enregister votre image avec un nom déjà attribué, l'ancienne image sera DEFINITIVEMENT SUPPRIMÉE**

Veillez à ce que votre image .PPM soit bien au format lisible par l'etre humain ASCII (P3) et non au format brut (P6). 
Si votre image est au format P6, vous pouvez la convertir au format P3 ici : [thomasebsmith-ppm-converter-github](https://github.com/thomasebsmith/ppm-converter) (un grand merci à thomasebsmith pour ce merveilleux outil).

## Les Fonctionnalités

### Réglage automatique

Le réglage automatique effectue un réglage de l’image de
la façon suivante :
- La luminosité est changée de façon à avoir une luminosité moyenne de l’ensemble
des pixels de 128.
- Le contraste est augmenté autant que possible sans que la valeur d’une composante
d’un pixel de l’image dépasse 255 ou 0.

### Composante Rouge

Cette fonctionnalité garde uniquement la composante rouge de l'image. 

### Niveau de gris 

Cette commande mets l'image en noir et blanc en égalisant les composantes RVB de chaque pixels. 

### NoirEtBlanc

Permets de créer une variante en noir et blanc à partir d'une image.

### HistogrammeGris

Renvoie un vecteur d'entiers représentant l'histogramme de l'image en niveau de Gris.

### Luminosité 

Cette fonctionnalité augmente ou diminue la luminosité de chaque pixel. 
Facteur d'augmentation de 1.5 et facteur de diminution de 2.
*Possible de modifier les facteurs en modifiant la CONSTANTE LUM*

### Contraste 

Augmente ou diminue le contraste de l'image d'un facteur 3. 
*Possible de modifier les facteurs en modifiant la CONSTANTE CONTRAST*

### Rognage

Supprime une partie de l'image du nombre de pixel demandé par l'utilsateur

### Rotation 

Effectue une rotation de 90° vers la gauche ou vers la droite

### Retournement 

Procède à une symétrie de l'image selon un axe horizontal ou vertical.

### Agrandissement

Créer une nouvelle image agrandit à partir d'un facteur d'entier.

### Retrecissement

Créer une nouvelle image rétrecis à partir d'un facteur d'entier.

### Flou

Créer une nouvelle image résultante de l'application d'un filtre sur l'image d'origine.

### Copie

Créer une copie de l'image d'origine ou de l'image actuelle. 

### Historique

Appeler "Annulation dans le programme". 
Permets de gérer un historique des modifications.
Et permets d'annule la dernière modification de l'image. L'annulation est itérable autant de fois qu'il y a eu de modification. 


## Les Auteurs

Ce programme a été réalisé dans le cadre d'un projet en première année à **l'IUT d'ORSAY** par **Richard Kylian** et **Lentz Kilian**

