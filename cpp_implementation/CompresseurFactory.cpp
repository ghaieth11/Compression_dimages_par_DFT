#include "CompresseurFactory.h"
#include "CompresseurDCT.h"
#include "AutreMethodeCompression.h"
#include <string>  // Ajout de la bibliothèque string

CompresseurAbstrait* CompresseurFactory::getCompresseur(const std::string& type) {
    if (type == "DCT") {  // Comparaison de chaîne correcte
        return new CompresseurDCT();
    } else if (type == "Autre") {  // Comparaison de chaîne correcte
        return new AutreMethodeCompression();
    }
    return nullptr;
}
