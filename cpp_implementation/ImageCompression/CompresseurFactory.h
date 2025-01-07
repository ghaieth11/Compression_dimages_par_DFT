#ifndef COMPRESSEURFACTORY_H
#define COMPRESSEURFACTORY_H

#include "CompresseurAbstrait.h"

enum class TypeCompresseur {
    COMPRESSION_IMAGE
    // Si tu ajoutes d'autres types de compresseurs, déclare-les ici
};

class CompresseurFactory {
public:
    static CompresseurAbstrait* creerCompresseur(TypeCompresseur type);
};

#endif // COMPRESSEURFACTORY_H

/*
On utilise ce design pattern qu'est le factory pour qu'il puisse nous permettre la créations d'instances d'objets de différents types de compresseurs
Il nous permet de crée des objets sans avoir à spécifier la classe exacte de l'objet qui sera crée.
Il nous permet d'avoir un code plus extensible, on peut ajouter des méthodes de compréssion facilement.


enum class TypeCompresseur : énumération qui permet de spécifier différents type de compresseur 

COMPRESSION_IMAGE : une valeur de cette énumération, type de compresseur utilisé pour la compression d'image
Si on veut ajouté d'autres type de compresseur on a qu'a ajouté d'autres valeurs 


static CompresseurAbstrait* creerCompresseur(TypeCompresseur type);

Une méthode statique qui peut etre appelée sans qu'il soit nécessaire d'instancier un objet CompresseurFactory
Elle retourune un pointeur de type CompresseurAbstrait*, une instance d'une classe dérivée de CompresseurAbstrait

Paramètre : 
TypeCompresseur type : Un paramètre de type énumération(TypeCompresseur) qui indique quel type de compresseur doit être crée 




*/