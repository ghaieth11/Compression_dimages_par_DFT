#include "GestionnaireImage.h"
#include <opencv2/opencv.hpp>  // Bibliothèque OpenCV pour manipuler les images
#include <stdexcept>           // Pour utiliser les exceptions std::runtime_error

// Constructeur du gestionnaire d'image
// Initialise le chemin de l'image à charger
GestionnaireImage::GestionnaireImage(const std::string& cheminImage) 
    : cheminImage(cheminImage) {}

// Fonction pour charger une image à partir du chemin spécifié
void GestionnaireImage::chargerImage() {
    // Charger l'image à partir du chemin en utilisant OpenCV
    cv::Mat image = cv::imread(cheminImage);
    
    // Vérifier si l'image a bien été chargée
    if (image.empty()) {
        // Si l'image ne peut pas être chargée, lever une exception
        throw std::runtime_error("Erreur lors du chargement de l'image.");
    }

    // Obtenir la largeur et la hauteur de l'image
    largeur = image.cols;
    hauteur = image.rows;

    // Tronquer la largeur et la hauteur pour les rendre multiples de 8
    largeurTronquee = (largeur / 8) * 8;
    hauteurTronquee = (hauteur / 8) * 8;
}

// Fonction pour sauvegarder l'image finale après recompression/décompression
void GestionnaireImage::sauvegarderImage(const std::string& cheminSortie, const cv::Mat& imageFinale) {
    // Utilise OpenCV pour sauvegarder l'image dans le fichier spécifié
    cv::imwrite(cheminSortie, imageFinale);
}

// Extraire les trois canaux de couleur (Rouge, Vert, Bleu) de l'image
std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<std::vector<int>>> GestionnaireImage::extraireCouleurs() {
    // Recharger l'image pour l'extraction des couleurs
    cv::Mat image = cv::imread(cheminImage);
    
    // Vérifier que l'image est bien chargée
    if (image.empty()) {
        throw std::runtime_error("Erreur lors de la lecture de l'image.");
    }

    // Créer des vecteurs pour les trois canaux de couleurs
    std::vector<std::vector<int>> Rouge(hauteurTronquee, std::vector<int>(largeurTronquee));
    std::vector<std::vector<int>> Vert(hauteurTronquee, std::vector<int>(largeurTronquee));
    std::vector<std::vector<int>> Bleu(hauteurTronquee, std::vector<int>(largeurTronquee));

    // Parcourir chaque pixel de l'image et extraire les couleurs
    for (int i = 0; i < hauteurTronquee; ++i) {
        for (int j = 0; j < largeurTronquee; ++j) {
            // Obtenir le pixel sous forme de triplet BGR
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            
            // Stocker les valeurs des canaux rouge, vert, bleu dans les vecteurs correspondants
            Rouge[i][j] = pixel[2];  // Le canal rouge est le 3e élément (indice 2)
            Vert[i][j] = pixel[1];   // Le canal vert est le 2e élément (indice 1)
            Bleu[i][j] = pixel[0];   // Le canal bleu est le 1er élément (indice 0)
        }
    }

    // Retourner les trois canaux sous forme de tuple
    return std::make_tuple(Rouge, Vert, Bleu);
}

// Recomposer une image à partir des trois canaux (Rouge, Vert, Bleu)
cv::Mat GestionnaireImage::recomposerImage(const std::vector<std::vector<int>>& r, 
                                           const std::vector<std::vector<int>>& g, 
                                           const std::vector<std::vector<int>>& b) {
    // Créer une nouvelle image OpenCV (cv::Mat) avec les dimensions de l'image tronquée
    cv::Mat imageFinale(hauteurTronquee, largeurTronquee, CV_8UC3);  // 8 bits par canal, 3 canaux (BGR)

    // Parcourir chaque pixel pour recomposer l'image à partir des canaux
    for (int i = 0; i < hauteurTronquee; ++i) {
        for (int j = 0; j < largeurTronquee; ++j) {
            // Remplir chaque pixel avec les valeurs des canaux correspondants
            imageFinale.at<cv::Vec3b>(i, j)[2] = r[i][j];  // Canal rouge
            imageFinale.at<cv::Vec3b>(i, j)[1] = g[i][j];  // Canal vert
            imageFinale.at<cv::Vec3b>(i, j)[0] = b[i][j];  // Canal bleu
        }
    }

    // Retourner l'image recomposée
    return imageFinale;
}
