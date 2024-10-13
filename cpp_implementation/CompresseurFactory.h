#ifndef COMPRESSEURFACTORY_H
#define COMPRESSEURFACTORY_H

#include "CompresseurAbstrait.h"
#include <string>  // Ajout pour la gestion des chaînes de caractères

class CompresseurFactory {
public:
    static CompresseurAbstrait* getCompresseur(const std::string& type);  // Utilisation de std::string
};

#endif

