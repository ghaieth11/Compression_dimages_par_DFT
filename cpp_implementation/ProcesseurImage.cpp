#include "ProcesseurImage.h"
#include "CompresseurAbstrait.h"
#include <cmath>      // Pour la fonction sqrt
#include <numeric>    // Pour std::accumulate
#include <algorithm>  // Pour std::count_if

// Constructeur de la classe ProcesseurImage
// Initialise un processeur d'image avec un compresseur donné
ProcesseurImage::ProcesseurImage(CompresseurAbstrait* compresseur)
    : compresseur(compresseur) {}  // Le compresseur est stocké dans un attribut de la classe

// Fonction pour initialiser les canaux Rouge, Vert et Bleu de l'image
void ProcesseurImage::setCanaux(const std::vector<std::vector<int>>& rouge, 
                                const std::vector<std::vector<int>>& vert, 
                                const std::vector<std::vector<int>>& bleu) {
    canalRouge = rouge;
    canalVert = vert;
    canalBleu = bleu;
}

// Appliquer la compression sur les trois canaux (Rouge, Vert, Bleu)
// Utilise le compresseur associé pour compresser chaque canal
void ProcesseurImage::appliquerCompression(int filtre) {
    canalRouge = compresseur->compresserCanal(canalRouge);
    canalVert = compresseur->compresserCanal(canalVert);
    canalBleu = compresseur->compresserCanal(canalBleu);
}

// Appliquer un filtrage sur un canal d'image
// Met à zéro les valeurs dans le bloc 8x8 pour lesquelles i + j >= f
std::vector<std::vector<int>> ProcesseurImage::appliquerFiltrage(const std::vector<std::vector<int>>& canal, int f) {
    std::vector<std::vector<int>> canalFiltre = canal;  // Copie du canal d'origine
    // Parcourir les éléments 8x8 du canal
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Si la somme des indices est supérieure ou égale à f, on met la valeur à 0
            if (i + j >= f) {
                canalFiltre[i][j] = 0;
            }
        }
    }
    return canalFiltre;  // Retourne le canal filtré
}

// Calculer le taux de compression d'un canal
// Renvoie le ratio des éléments non nuls par rapport au nombre total d'éléments
float ProcesseurImage::calculerTauxCompression(const std::vector<std::vector<int>>& canal) {
    int nonZeroElements = 0;  // Compteur d'éléments non nuls
    int totalElements = canal.size() * canal[0].size();  // Nombre total d'éléments

    // Compter les éléments non nuls dans le canal
    for (const auto& row : canal) {
        // Utilise std::count_if pour compter les éléments non nuls dans chaque ligne
        nonZeroElements += std::count_if(row.begin(), row.end(), [](int val) { return val != 0; });
    }

    // Calculer et retourner le taux de compression
    return static_cast<float>(nonZeroElements) / totalElements;
}

// Calculer l'erreur de compression entre les canaux décompressés et originaux
// Utilise la norme de chaque canal pour calculer l'erreur relative entre l'image d'origine et l'image décompressée
float ProcesseurImage::calculerErreur(const std::vector<std::vector<int>>& nouvelleRouge, 
                                      const std::vector<std::vector<int>>& nouvelleVert, 
                                      const std::vector<std::vector<int>>& nouvelleBleu,
                                      const std::vector<std::vector<int>>& originalRouge, 
                                      const std::vector<std::vector<int>>& originalVert, 
                                      const std::vector<std::vector<int>>& originalBleu) {

    // Lambda fonction pour calculer la norme d'un canal
    // La norme est la racine carrée de la somme des carrés des éléments du canal
    auto calculerNorme = [](const std::vector<std::vector<int>>& canal) {
        int somme = 0;
        // Pour chaque ligne, accumuler la somme des carrés des éléments
        for (const auto& row : canal) {
            somme += std::accumulate(row.begin(), row.end(), 0, [](int acc, int val) { return acc + val * val; });
        }
        // Retourner la racine carrée de la somme des carrés
        return std::sqrt(somme);
    };

    // Calculer les erreurs relatives pour chaque canal (Rouge, Vert, Bleu)
    float erreurR = calculerNorme(nouvelleRouge) / calculerNorme(originalRouge);
    float erreurV = calculerNorme(nouvelleVert) / calculerNorme(originalVert);
    float erreurB = calculerNorme(nouvelleBleu) / calculerNorme(originalBleu);

    // Retourner l'erreur moyenne sur les trois canaux
    return (erreurR + erreurV + erreurB) / 3.0f;
}
