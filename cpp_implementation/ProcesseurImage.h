#ifndef PROCESSEURIMAGE_H
#define PROCESSEURIMAGE_H

#include "CompresseurAbstrait.h"
#include <vector>

class ProcesseurImage {
private:
    CompresseurAbstrait* compresseur;
    std::vector<std::vector<int>> canalRouge;
    std::vector<std::vector<int>> canalVert;
    std::vector<std::vector<int>> canalBleu;

public:
    // Constructeur
    ProcesseurImage(CompresseurAbstrait* compresseur);

    // Méthode pour initialiser les canaux
    void setCanaux(const std::vector<std::vector<int>>& rouge, const std::vector<std::vector<int>>& vert, const std::vector<std::vector<int>>& bleu);

    // Appliquer la compression sur les trois canaux
    void appliquerCompression(int filtre);

    // Appliquer un filtrage sur un canal donné
    std::vector<std::vector<int>> appliquerFiltrage(const std::vector<std::vector<int>>& canal, int f);

    // Calculer le taux de compression pour un canal
    float calculerTauxCompression(const std::vector<std::vector<int>>& canal);

    // Calculer l'erreur de compression
    float calculerErreur(const std::vector<std::vector<int>>& nouvelleRouge, const std::vector<std::vector<int>>& nouvelleVert, const std::vector<std::vector<int>>& nouvelleBleu,
                         const std::vector<std::vector<int>>& originalRouge, const std::vector<std::vector<int>>& originalVert, const std::vector<std::vector<int>>& originalBleu);
};

#endif

