#include "ColorDistribution.h"
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/utility.hpp>
using namespace cv;

void ColorDistribution::reset() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			for (int k = 0; k < 8; k++)
				data[i][j][k] = 0;
	nb = 0;
}

void ColorDistribution::add(Vec3b color) {
	int i = color[0] / 32;
	int j = color[1] / 32;
	int k = color[2] / 32;
	data[i][j][k]++;
	nb++;
}

void ColorDistribution::finished() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			for (int k = 0; k < 8; k++)
				data[i][j][k] /= nb;
}

ColorDistribution ColorDistribution::getColorDistribution(Mat input, Point p1, Point p2) {
	ColorDistribution cd;
	cd.reset();
	for (int i = p1.y; i < p2.y; i++)
		for (int j = p1.x; j < p2.x; j++)
			cd.add(input.at<Vec3b>(i, j));
	cd.finished();
	return cd;
}

float ColorDistribution::distance(const ColorDistribution& other) const {
	float dist = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 8; k++) {
				float denom = data[i][j][k] + other.data[i][j][k];
				if (denom != 0) {
					dist += (data[i][j][k] - other.data[i][j][k]) * (data[i][j][k] - other.data[i][j][k]) / denom;
				}
			}
		}
	}
	return dist;
}