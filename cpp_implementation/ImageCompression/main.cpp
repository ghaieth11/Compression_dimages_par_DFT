#include <opencv2/opencv.hpp>
#include "CompresseurFactory.h"
#include "ProcesseurImage.h"
#include "GestionnaireImage.h"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // Chemin de l'image à charger
    string cheminImage = "/Users/g_aloui/Documents/MyFiles(G.aloui)/Bureau_DocumentsUtiles/Projet MAM3/Compression_dimages_par_DFT/cpp_implementation/ImageCompression/new.png";

    // Charger l'image
    Mat image = GestionnaireImage::chargerImage(cheminImage);
    if (image.empty()) {
        cerr << "Erreur : impossible de charger l'image." << endl;
        return -1;
    }

    // Afficher la taille de l'image initiale
    double tailleInitiale = GestionnaireImage::tailleFichier(cheminImage);
    if (tailleInitiale > 0) {
        cout << "Taille de l'image initiale : " << tailleInitiale << " kB" << endl;
    }

    // Redimensionner l'image pour la tronquer
    int largeurTronquee = (image.cols / 8) * 8;
    int longueurTronquee = (image.rows / 8) * 8;
    resize(image, image, Size(largeurTronquee, longueurTronquee));

    // Demander à l'utilisateur d'entrer la fréquence de filtrage
    int f;
    cout << "Entrez la fréquence de filtrage (ex: 10), plus la fréquence est basse, plus l'image va être compressée !: ";
    cin >> f;

    // Créer un compresseur avec la factory
    CompresseurAbstrait* compresseur = CompresseurFactory::creerCompresseur(TypeCompresseur::COMPRESSION_IMAGE);
    if (!compresseur) {
        cerr << "Erreur : impossible de créer le compresseur." << endl;
        return -1;
    }

    // Extraire les canaux de couleur
    Mat Rouge, Vert, Bleu;
    mesurerTempsExecution("Extraction des canaux de couleur", [&]() {
        tie(Rouge, Vert, Bleu) = compresseur->ExtractionCouleurs(image);
    });

    // Ajustement des canaux
    Rouge.convertTo(Rouge, CV_64F);
    Vert.convertTo(Vert, CV_64F);
    Bleu.convertTo(Bleu, CV_64F);
    Rouge -= 128;
    Vert -= 128;
    Bleu -= 128;

    // Calculer la matrice DCT
    Mat Pass;
    mesurerTempsExecution("Calcul de la matrice DCT", [&]() {
        Pass = compresseur->CalculerPass();
    });

    // Compression
    Mat RougeComp, VertComp, BleuComp;
    mesurerTempsExecution("Compression des canaux", [&]() {
        RougeComp = compresseur->Compression(Rouge, Pass, f);
        VertComp = compresseur->Compression(Vert, Pass, f);
        BleuComp = compresseur->Compression(Bleu, Pass, f);
    });

    // Décompression
    Mat RougeDec, VertDec, BleuDec;
    mesurerTempsExecution("Décompression des canaux", [&]() {
        RougeDec = compresseur->Decompression(RougeComp, Pass) + 128;
        VertDec = compresseur->Decompression(VertComp, Pass) + 128;
        BleuDec = compresseur->Decompression(BleuComp, Pass) + 128;
    });

    // Recomposition de l'image décompressée
    Mat imageRecomposee;
    mesurerTempsExecution("Recomposition de l'image", [&]() {
        imageRecomposee = compresseur->Recomposition(RougeDec, VertDec, BleuDec);
        imageRecomposee.convertTo(imageRecomposee, CV_8U);
    });

    // Sauvegarder l'image décompressée
    string cheminImageDecomp = "/Users/g_aloui/Downloads/codefinal/newC++.png";
    GestionnaireImage::sauvegarderImage(cheminImageDecomp, imageRecomposee, 70);

    // Afficher la taille de l'image finale
    double tailleFinale = GestionnaireImage::tailleFichier(cheminImageDecomp);
    if (tailleFinale > 0) {
        cout << "Taille de l'image décompressée : " << tailleFinale << " kB" << endl;
    }

    // Afficher la différence de taille
    if (tailleInitiale > 0 && tailleFinale > 0) {
        cout << "L'image a bien été compressée, elle est passée de " << tailleInitiale << " kB à " << tailleFinale << " kB." << endl;
    }

    // Calcul et affichage du taux de compression
    mesurerTempsExecution("Calcul du taux de compression", [&]() {
        double tauxComp = TauxCompression(RougeComp, VertComp, BleuComp, f);
        cout << "Taux de compression : " << tauxComp << "%" << endl;
    });

    // Calcul et affichage de l'erreur de compression
    mesurerTempsExecution("Calcul de l'erreur de compression", [&]() {
        double erreurRouge = ErreurCompression(Rouge + 128, RougeDec);
        double erreurVert = ErreurCompression(Vert + 128, VertDec);
        double erreurBleu = ErreurCompression(Bleu + 128, BleuDec);
        double erreurMoyenne = (erreurRouge + erreurVert + erreurBleu) / 3.0;
        cout << "Erreur de compression (moyenne) : " << erreurMoyenne << endl;
    });

    // Afficher les images
    GestionnaireImage::afficherImage("Image Originale", image);
    GestionnaireImage::afficherImage("Image Décompressée", imageRecomposee);

    // Attendre la fermeture des fenêtres
    waitKey(0);
    destroyAllWindows();

    // Libérer la mémoire
    delete compresseur;

    return 0;
}
