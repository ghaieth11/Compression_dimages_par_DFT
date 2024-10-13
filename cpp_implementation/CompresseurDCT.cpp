#include "CompresseurDCT.h"
#include <vector>
#include <cmath>

// Compression utilisant DCT
std::vector<std::vector<int>> CompresseurDCT::compresserCanal(const std::vector<std::vector<int>>& canal) {
    int largeur = canal[0].size();
    int hauteur = canal.size();
    std::vector<std::vector<int>> canalCompresse(hauteur, std::vector<int>(largeur));

    // Simulation simple d'une compression
    for (int i = 0; i < hauteur; i += 8) {
        for (int j = 0; j < largeur; j += 8) {
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    canalCompresse[i + x][j + y] = static_cast<int>(canal[i + x][j + y] * 0.5);  // Exemple de compression
                }
            }
        }
    }

    return canalCompresse;
}

// Décompression utilisant DCT
std::vector<std::vector<int>> CompresseurDCT::decompresserCanal(const std::vector<std::vector<int>>& canal) {
    int largeur = canal[0].size();
    int hauteur = canal.size();
    std::vector<std::vector<int>> canalDecompresse(hauteur, std::vector<int>(largeur));

    // Simulation simple d'une décompression
    for (int i = 0; i < hauteur; i += 8) {
        for (int j = 0; j < largeur; j += 8) {
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    canalDecompresse[i + x][j + y] = static_cast<int>(canal[i + x][j + y] * 2.0);  // Exemple de décompression
                }
            }
        }
    }

    return canalDecompresse;
}
