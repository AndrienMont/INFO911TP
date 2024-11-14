#pragma once
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
using namespace cv;

struct ColorDistribution {
    float data[8][8][8]; // l'histogramme
    int nb;                     // le nombre d'�chantillons

    ColorDistribution() { reset(); }
    ColorDistribution& operator=(const ColorDistribution& other) = default;
    // Met � z�ro l'histogramme    
    void reset();
    // Ajoute l'�chantillon color � l'histogramme:
    // met +1 dans la bonne case de l'histogramme et augmente le nb d'�chantillons
    void add(Vec3b color);
    // Indique qu'on a fini de mettre les �chantillons:
    // divise chaque valeur du tableau par le nombre d'�chantillons
    // pour que case repr�sente la proportion des picels qui ont cette couleur.
    void finished();
    // Retourne la distance entre cet histogramme et l'histogramme other avec la m�thode Chi2
    float distance(const ColorDistribution& other) const;
	// Retourne la distribution de couleur entre les points p1 et p2
    ColorDistribution getColorDistribution(Mat input, Point p1, Point p2);
	//Retourne la plus petite distance entre h et les histogrammes de col_hists
    float minDistance(const ColorDistribution& h, const std::vector<ColorDistribution>& hists);
};