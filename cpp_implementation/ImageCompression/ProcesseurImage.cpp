#include "ProcesseurImage.h"
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

// Fonction pour appliquer un filtrage à un bloc 8x8
Mat Filtrage(const Mat& M, int f) {
    Mat M_filtree = M.clone();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i + j >= f) {
                M_filtree.at<double>(i, j) = 0;
            }
        }
    }
    return M_filtree;
}

// Fonction pour appliquer le filtrage complet à une image
Mat FiltrageComplet(const Mat& M, int f) {
    Mat Mfilt = Mat::zeros(M.size(), CV_64F);
    for (int i = 0; i < M.rows; i += 8) {
        for (int j = 0; j < M.cols; j += 8) {
            Mat bloc = M(Rect(j, i, 8, 8));
            Mat blocFiltre = Filtrage(bloc, f);
            blocFiltre.copyTo(Mfilt(Rect(j, i, 8, 8)));
        }
    }
    return Mfilt;
}

// Fonction pour calculer le taux de compression
double TauxCompression(const Mat& Rouge, const Mat& Vert, const Mat& Bleu, int f) {
    int total_pixels = Rouge.rows * Rouge.cols;
    int seuil = 0;  // Seuil pour considérer un coefficient comme nul

    // Compresser et filtrer les canaux
    Mat RougeComp = FiltrageComplet(Rouge, f);
    Mat VertComp = FiltrageComplet(Vert, f);
    Mat BleuComp = FiltrageComplet(Bleu, f);
    
    // Compter les coefficients non nuls en appliquant un seuil
    int non_zero_rouge = countNonZero(abs(RougeComp) > seuil);
    int non_zero_vert = countNonZero(abs(VertComp) > seuil);
    int non_zero_bleu = countNonZero(abs(BleuComp) > seuil);
    
    // Calculer le taux de compression pour chaque canal
    double taux_rouge = 1.0 - static_cast<double>(non_zero_rouge) / total_pixels; // Conversion avec static_cast<double> afin d'avoir une division float et non entiere 
    double taux_vert = 1.0 - static_cast<double>(non_zero_vert) / total_pixels;
    double taux_bleu = 1.0 - static_cast<double>(non_zero_bleu) / total_pixels;
    
    // Calcul de la moyenne des taux de compression et conversion en pourcentage
    double taux_compression_moyen = (taux_rouge + taux_vert + taux_bleu) / 3.0;
    return taux_compression_moyen * 100;  // Retourner le taux en pourcentage
}




// Fonction pour calculer l'erreur de compression
double ErreurCompression(const Mat& original, const Mat& decompresse) {
    // Conversion des matrices en CV_64F pour précision
    Mat original64, decompresse64;
    original.convertTo(original64, CV_64F);
    decompresse.convertTo(decompresse64, CV_64F);
    
    // Calculer la différence entre les deux matrices
    Mat diff = original64 - decompresse64;
    
    // Norme Euclidienne (L2) de la différence
    double erreur = norm(diff, NORM_L2);
    
    // Retourner l'erreur normalisée
    return erreur / (original.rows * original.cols);
}


