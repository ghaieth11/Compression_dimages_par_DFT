#include "CompressionImage.h"
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Constructeur
CompressionImage::CompressionImage() {
    // Initialisation de la matrice de quantification
    Q = {
    {32, 33, 40, 51, 99, 99, 99, 99},
    {33, 36, 41, 66, 99, 99, 99, 99},
    {40, 41, 66, 99, 99, 99, 99, 99},
    {51, 66, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99}
};


}

CompressionImage::~CompressionImage() {}

// Extraction des canaux de couleur
tuple<Mat, Mat, Mat> CompressionImage::ExtractionCouleurs(const Mat& image) {
    vector<Mat> bgr;
    split(image, bgr); // Diviser l'image en 3 canaux : B, G et R
    return {bgr[2], bgr[1], bgr[0]}; // Retourne Rouge, Vert, Bleu
}

// Calcul de la matrice DCT
Mat CompressionImage::CalculerPass() {
    Mat Pass = Mat::zeros(8, 8, CV_64F);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 0) {
                Pass.at<double>(i, j) = (1.0 / sqrt(2.0)) * 0.5 * cos((2 * j + 1) * i * M_PI / 16);
            } else {
                Pass.at<double>(i, j) = 0.5 * cos((2 * j + 1) * i * M_PI / 16);  //at<double>(i,j) dans OpenCV permet d'acceder ou de modifier les elts d'une matrice de type spécifique, ici double.
            }
        }
    }
    return Pass;
}

// Compression via DCT et quantification
Mat CompressionImage::Compression(const Mat& M, const Mat& Pass, int f) {
    Mat PassT;
    transpose(Pass, PassT); // Calcul de la transposée de la matrice Pass
    Mat Mcomp = Mat::zeros(M.size(), CV_64F);
    for (int i = 0; i < M.rows; i += 8) {
        for (int j = 0; j < M.cols; j += 8) {
            Mat bloc = M(Rect(j, i, 8, 8));
            Mat dctBloc = Pass * bloc * PassT; // Appliquer la DCT
            // Appliquer le filtrage
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    if (x + y >= f) {
                        dctBloc.at<double>(x, y) = 0;  // Appliquer le filtrage en annulant certains coeffs
                    }
                    Mcomp.at<double>(i + x, j + y) = round(dctBloc.at<double>(x, y) / Q[x][y]);
                }
            }
        }
    }
    return Mcomp;
}

// Décompression via DCT inverse
Mat CompressionImage::Decompression(const Mat& Mcomp, const Mat& Pass) {
    Mat PassT;
    transpose(Pass, PassT);
    Mat Mdec = Mat::zeros(Mcomp.size(), CV_64F);
    for (int i = 0; i < Mcomp.rows; i += 8) {
        for (int j = 0; j < Mcomp.cols; j += 8) {
            Mat bloc = Mcomp(Rect(j, i, 8, 8));
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    bloc.at<double>(x, y) *= Q[x][y];  // Appliquer la matrice de quantification inverse
                }
            }
            Mat idctBloc = PassT * bloc * Pass;  // Appliquer la DCT inverse
            idctBloc.copyTo(Mdec(Rect(j, i, 8, 8))); // On copie les valeurs du bloc decompressé dans la zone correspondante de la matrice d'image décompressé Mdec.
        }
    }
    return Mdec;
}

// Recomposition d'une image à partir des canaux R, V, B
Mat CompressionImage::Recomposition(const Mat& R, const Mat& V, const Mat& B) {
    vector<Mat> bgr = {B, V, R}; // Recomposer en ordre B, G, R
    Mat image;
    merge(bgr, image); // La fonction merge permet de fusionner les trois canaux de couleur separé (bleu,vert,rouge) en une seule pour avoir uen image couleur complete.
    return image;
}





/**
  Explication 


   ExtractionCouleurs(const Mat& image):
     Cette fonction separe une image en trois canaux de couleur (rouge, vert, bleu) a l'aide de la fonction OpenCV `split()`. 
     Cela permet de traiter independamment chaque canal de couleur lors de la compression avec la DCT.
     La DCT est appliquee separement sur chaque canal, car les differentes composantes de couleur peuvent etre compressees differemment.
 
   CalculerPass():
     Cette fonction calcule la matrice de transformation DCT, souvent appelee matrice de base DCT, utilisee pour effectuer la DCT sur les blocs de l'image.
     La DCT transforme un bloc d'image (8x8 dans ce cas) de l'espace spatial vers l'espace frequentiel.
     La formule de la DCT utilisee ici est celle de la transformation de cosinus discrete 2D, adaptee pour des blocs de 8x8 pixels.
     La premiere ligne de la matrice DCT est calculee avec un facteur special (1/sqrt(2).
 
   Compression(const Mat& M, const Mat& Pass, int f):
     Cette methode applique la DCT a des blocs de 8x8 pixels de l'image `M`.
     - Chaque bloc de l'image est multiplie par la matrice DCT (`Pass`) et sa transposee (`PassT`) pour obtenir les coefficients DCT.
     - Apres la transformation, un filtrage est appliqué : seuls les coefficients de basse fréquence sont conserves, ceux qui representent des details fins de l'image.
     - Ensuite, la quantification est effectuée en divisant chaque coefficient DCT par une valeur de la matrice de quantification `Q`. Cela reduit encore plus les informations redondantes, car les petites variations dans les coefficients sont supprimées.
       Elle permet de reduire significativement la taille des données tout en conservant les informations essentielles pour la perception visuelle.
 
   Decompression(const Mat& Mcomp, const Mat& Pass):
    Cette methode effectue l'inverse de la compression.
   - Les coefficients quantifies sont d'abord **dequantifies** en les multipliant par les valeurs de la matrice de quantification `Q` pour retablir leurs valeurs d'origine.
    - Ensuite, la DCT inverse est appliquee a chaque bloc en utilisant la matrice DCT transposee et la matrice DCT originale. Cela reconvertit les donnees de l'espace frequentiel vers l'espace spatial,  l'image approximative d'origine est recrée.
    - Les blocs decompresses sont assembles dans la matrice finale `Mdec`, qui est l'image decompressée.
 - La DCT inverse est une etape cruciale pour retrouver les blocs d'images, et la multiplication avec la matrice transposee permet de recreer les valeurs de pixels a partir des coefficients DCT.
 
  Recomposition(const Mat& R, const Mat& V, const Mat& B):
     Apres la compression et decompression des canaux rouge, vert et bleu, cette fonction combine les trois canaux de couleur en une seule image couleur complete.
   - La fonction OpenCV `merge()` est utilisee pour fusionner les canaux B, G, R dans une matrice d'image couleur.
    - Cela permet de reformer l'image couleur complete apres avoir separe et compresse independamment chaque canal avec la DCT.
 */
