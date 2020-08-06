#include <opencv2/opencv.hpp>

#include <iostream>

using namespace cv;

const int sliderMax = 100;
int sliderVal = 0;
const std::string windowName = "Saturated Image";
Mat sourceImage,saturatedImage,hsvImage;;

void onTrack(int desaturationScale, void*); 

int main()
{
    sourceImage = imread("girl.jpg", IMREAD_COLOR);	
	if (sourceImage.empty()) {
		std::cout << "Error while reading input image" << std::endl;
		return -1;
	}
	namedWindow(windowName, WINDOW_AUTOSIZE);
	createTrackbar("Saturation", windowName, &sliderVal, sliderMax, onTrack);
	onTrack(0, 0);	
	imshow("Original Image", sourceImage);

	if (waitKey(0) >= 0) {
		destroyAllWindows();
		std::cout << "Terminating" << std::endl;
	}
	return 0;
}
void onTrack(int scale, void*){

	float saturationScale = (float) scale / 100;

	cvtColor(sourceImage, hsvImage, COLOR_BGR2HSV);

	hsvImage.convertTo(hsvImage, CV_32F); // Needed for multiplication

	std::vector<Mat> channels(3);
	split(hsvImage, channels);

	//Desaturation
	channels[1] = channels[1] * saturationScale;

	min(channels[1], 255, channels[1]);
	max(channels[1], 0, channels[1]);

	merge(channels, hsvImage);
	hsvImage.convertTo(hsvImage, CV_8UC3);

	cvtColor(hsvImage, saturatedImage, COLOR_HSV2BGR);
	imshow("Saturated Image", saturatedImage);

}