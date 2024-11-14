#include <cstdio>
#include <iostream>
#include <algorithm>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "ColorDistribution.h"

using namespace cv;
using namespace std;

std::vector<ColorDistribution> col_hists;
std::vector<ColorDistribution> col_hists_object;

Mat recoObject(Mat input, const std::vector<ColorDistribution>& col_hists,
    const std::vector<ColorDistribution>& col_hists_object, const std::vector<Vec3b>& colors, const int bloc) {
    Mat output = input.clone();
    for (int i = 0; i <= input.rows - bloc; i += bloc) {
        for (int j = 0; j <= input.cols - bloc; j += bloc) {
            ColorDistribution cd = cd.getColorDistribution(input, Point(j, i), Point(j + bloc, i + bloc));
            float d1 = cd.minDistance(cd, col_hists);
            float d2 = cd.minDistance(cd, col_hists_object);
            if (d1 < d2) {
                for (int x = i; x < i + bloc; x++) {
                    for (int y = j; y < j + bloc; y++) {
                        output.at<Vec3b>(x, y) = colors[0];
                    }
                }
            }
            else {
                for (int x = i; x < i + bloc; x++) {
                    for (int y = j; y < j + bloc; y++) {
                        output.at<Vec3b>(x, y) = colors[1];
                    }
                }
            }
        }
    }
    return output;
}

int main(int argc, char** argv)
{
    Mat img_input, img_seg, img_d_bgr, img_d_hsv, img_d_lab;
    VideoCapture* pCap = nullptr;
    const int width = 640;
    const int height = 480;
    const int size = 50;
    // Ouvre la camera
    pCap = new VideoCapture(0);
    if (!pCap->isOpened()) {
        cout << "Couldn't open image / camera ";
        return 1;
    }
    // Force une camera 640x480 (pas trop grande).
    pCap->set(CAP_PROP_FRAME_WIDTH, 640);
    pCap->set(CAP_PROP_FRAME_HEIGHT, 480);
    (*pCap) >> img_input;
    if (img_input.empty()) return 1; // probleme avec la camera
    Point pt1(width / 2 - size / 2, height / 2 - size / 2);
    Point pt2(width / 2 + size / 2, height / 2 + size / 2);
    Mat output = img_input;
    std::vector<Vec3b> colors = { Vec3b(255,0,0), Vec3b(255,255,0) };
    bool reco = false;
    namedWindow("input", 1);
    imshow("input", img_input);
    bool freeze = false;
    while (true)
    {
        char c = (char)waitKey(50); // attend 50ms -> 20 images/s
        if (pCap != nullptr && !freeze)
            (*pCap) >> img_input;     // récupère l'image de la caméra
        if (c == 27 || c == 'q')  // permet de quitter l'application
            break;
        if (c == 'f') // permet de geler l'image
            freeze = !freeze;
        if (c == 'v') {
            //calcule la distribution couleur dans la partie droite et gauche de l'écran
            //Calcule la distance entre les 2 distributions et l'affiche
            ColorDistribution cd_left, cd_right;
			cd_left = cd_left.getColorDistribution(img_input, Point(0, 0), Point(width / 2, height));
			cd_right = cd_right.getColorDistribution(img_input, Point(width / 2, 0), Point(width, height));
			float distance = cd_left.distance(cd_right);
			cout << "Distance: " << distance << endl;
        }
        if (c == 'b') {
            const int bbloc = 128;
            col_hists.clear();
            for (int i = 0; i <= height - bbloc; i += bbloc) {
                for (int j = 0; j <= width - bbloc; j += bbloc) {
                    ColorDistribution cd;
					cd = cd.getColorDistribution(img_input, Point(j, i), Point(j + bbloc, i + bbloc));
					col_hists.push_back(cd);
                }
            }
			int nb_hists_background = col_hists.size();
			cout << "Background histograms: " << nb_hists_background << endl;
        }
        if (c == 'a') {
            ColorDistribution cd;
            cd = cd.getColorDistribution(img_input, pt1, pt2);
			col_hists_object.push_back(cd);
			cout << "Object histograms: " << col_hists_object.size() << endl;
        }
        if (c == 'r') {
            reco = !reco;
        }
        if (reco) {
            Mat gray;
			cvtColor(img_input, gray, COLOR_BGR2GRAY);
			Mat reco = recoObject(img_input, col_hists, col_hists_object, colors, 8);
            cvtColor(gray, img_input, COLOR_GRAY2BGR);
            output = 0.5 * reco + 0.5 * img_input;
        }
        else {
			cv::rectangle(img_input, pt1, pt2, Scalar({ 255.0, 255.0, 255.0 }), 1);
        }
        //cv::rectangle(img_input, pt1, pt2, Scalar({ 255.0, 255.0, 255.0 }), 1);
        imshow("input", output); // affiche le flux video
    }
    return 0;
}