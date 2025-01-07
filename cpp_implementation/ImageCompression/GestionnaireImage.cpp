#include "GestionnaireImage.h"
#include <sys/stat.h>  // Pour obtenir la taille du fichier
#include <opencv2/opencv.hpp>  // Inclure OpenCV pour la gestion des images

using namespace cv;
using namespace std;

// Charger une image depuis un fichier
Mat GestionnaireImage::chargerImage(const string& cheminImage) {
    return imread(cheminImage, IMREAD_COLOR);  //Cela permet de lire l'image en couleur
}

// Sauvegarder une image avec qualité spécifiée
void GestionnaireImage::sauvegarderImage(const string& cheminImage, const Mat& image, int qualite) {
    vector<int> params = { IMWRITE_JPEG_QUALITY, qualite };  //Ce sont les  paramètres pour la qualité JPEG
    imwrite(cheminImage, image, params);  // Imwrite permet de sauvegarde l'image 
}

// Afficher une image dans une fenêtre
void GestionnaireImage::afficherImage(const string& fenetre, const Mat& image) {
    imshow(fenetre, image);  // Afficher l'image dans la fenêtre spécifié
}

// Obtenir la taille du fichier en kilooctets
double GestionnaireImage::tailleFichier(const string& cheminFichier) {
    struct stat stat_buf;
    int rc = stat(cheminFichier.c_str(), &stat_buf);  // Obtenir les infos du fichier
    return rc == 0 ? stat_buf.st_size / 1024.0 : -1;  // Retourner la taille en kB ou -1 si erreur

    /*
    stat() permet de récupérer les infos sur le fichier et les stocké dans stat_buf, si l'opération réussi (rc==0), la taille du fichier 
    est converti en kilooctets et renvoyée. Si stat() échoue la fonction renvoie -1 pour signaler un pb.
    
    cheminFichier.c_str() converti le chemin du fichier (de type string) en une chaine de caracteres (const *char) pour la fonction stat()
    &stat_buf : c'est un pointeur vers la structure stat qui sera repmpli par la fonction stat().
    Le retour de stat() est stocké dans un int rc.
    
    */
}
