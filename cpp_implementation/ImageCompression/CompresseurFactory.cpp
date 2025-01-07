#include "CompresseurFactory.h"
#include "CompressionImage.h"

CompresseurAbstrait* CompresseurFactory::creerCompresseur(TypeCompresseur type) {
    switch (type) { // Compare le type du compresseur demandé (type) et determine quelle classe de compresseur instancier 
        case TypeCompresseur::COMPRESSION_IMAGE: // Si c'est notre méthode DCT, la fonction crée une nouvelle instance de CompressionImage avec new et renvoie un pointeur vers cette instance
            return new CompressionImage();
        // Si on veut ajouter d'autres méthode de compression, on les ajoute ici 
        default:
            return nullptr; // Par défaut on renvoie NULL si on reconnait aucun type 
    }
}

