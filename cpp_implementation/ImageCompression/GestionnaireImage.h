#ifndef GESTIONNAIREIMAGE_H
#define GESTIONNAIREIMAGE_H

#include <opencv2/opencv.hpp>
#include <string>

class GestionnaireImage {
public:
    // Charger une image à partir d'un fichier sur le disque en utilisant son chemin
    static cv::Mat chargerImage(const std::string& cheminImage);

    // Sauvegarder une image avec paramètres, OpenCV encode l'image dans un format comme JPEG
    static void sauvegarderImage(const std::string& cheminImage, const cv::Mat& image, int qualite = 95);

    // Le parametre qualité est optionnel, il permet de controler la qualité de la compression pour les formats comme JPEG



    // Afficher une image dans une fenêtre graphique à l'aide des fonctions OpenCV 
    static void afficherImage(const std::string& fenetre, const cv::Mat& image);

    // Obtenir la taille du fichier en kB en lisant les métadonnées du fichier
    static double tailleFichier(const std::string& cheminFichier);
};

#endif // GESTIONNAIREIMAGE_H

/* 
Les méthodes sont statiques, elle peuvent être appelées sans créer d'instance de la classe.

OpenCV ouvre les fichiers images de différents formats(JPEG,PNG etc) et les converti en objets cv::Mat 
pour la manipulation.





*/