#include "AutreMethodeCompression.h"
#include <vector>
#include <cmath>

// Constructeur par défaut
AutreMethodeCompression::AutreMethodeCompression() {}

// Fonction pour appliquer la DCT sur un bloc 8x8
void dct8x8(const std::vector<std::vector<int>>& bloc, std::vector<std::vector<double>>& blocDCT) {
    for (int u = 0; u < 8; ++u) {
        for (int v = 0; v < 8; ++v) {
            double sum = 0.0;
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    sum += bloc[x][y] * std::cos((2 * x + 1) * u * M_PI / 16) * std::cos((2 * y + 1) * v * M_PI / 16);
                }
            }
            double alpha_u = (u == 0) ? (1 / std::sqrt(2)) : 1.0;
            double alpha_v = (v == 0) ? (1 / std::sqrt(2)) : 1.0;
            blocDCT[u][v] = 0.25 * alpha_u * alpha_v * sum;
        }
    }
}

// Fonction pour appliquer l'IDCT sur un bloc 8x8
void idct8x8(const std::vector<std::vector<double>>& blocDCT, std::vector<std::vector<int>>& bloc) {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            double sum = 0.0;
            for (int u = 0; u < 8; ++u) {
                for (int v = 0; v < 8; ++v) {
                    double alpha_u = (u == 0) ? (1 / std::sqrt(2)) : 1.0;
                    double alpha_v = (v == 0) ? (1 / std::sqrt(2)) : 1.0;
                    sum += alpha_u * alpha_v * blocDCT[u][v] * std::cos((2 * x + 1) * u * M_PI / 16) * std::cos((2 * y + 1) * v * M_PI / 16);
                }
            }
            bloc[x][y] = std::round(0.25 * sum);
        }
    }
}

// Méthode de compression utilisant la DCT
std::vector<std::vector<int>> AutreMethodeCompression::compresserCanal(const std::vector<std::vector<int>>& canal) {
    int largeur = canal[0].size();
    int hauteur = canal.size();
    std::vector<std::vector<int>> canalCompresse(hauteur, std::vector<int>(largeur));

    // Parcourir l'image par blocs de 8x8
    for (int i = 0; i < hauteur; i += 8) {
        for (int j = 0; j < largeur; j += 8) {
            std::vector<std::vector<int>> bloc(8, std::vector<int>(8));
            std::vector<std::vector<double>> blocDCT(8, std::vector<double>(8));

            // Extraire le bloc 8x8
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    bloc[x][y] = canal[i + x][j + y];
                }
            }

            // Appliquer la DCT sur le bloc
            dct8x8(bloc, blocDCT);

            // Stocker les coefficients DCT dans le canal compressé
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    canalCompresse[i + x][j + y] = static_cast<int>(blocDCT[x][y]);
                }
            }
        }
    }

    return canalCompresse;
}

// Méthode de décompression utilisant l'IDCT
std::vector<std::vector<int>> AutreMethodeCompression::decompresserCanal(const std::vector<std::vector<int>>& canal) {
    int largeur = canal[0].size();
    int hauteur = canal.size();
    std::vector<std::vector<int>> canalDecompresse(hauteur, std::vector<int>(largeur));

    // Parcourir l'image par blocs de 8x8
    for (int i = 0; i < hauteur; i += 8) {
        for (int j = 0; j < largeur; j += 8) {
            std::vector<std::vector<int>> bloc(8, std::vector<int>(8));
            std::vector<std::vector<double>> blocDCT(8, std::vector<double>(8));

            // Extraire le bloc DCT
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    blocDCT[x][y] = static_cast<double>(canal[i + x][j + y]);
                }
            }

            // Appliquer l'IDCT sur le bloc
            idct8x8(blocDCT, bloc);

            // Stocker les valeurs décompressées
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    canalDecompresse[i + x][j + y] = bloc[x][y];
                }
            }
        }
    }

    return canalDecompresse;
}
