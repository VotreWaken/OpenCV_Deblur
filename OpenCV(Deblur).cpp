// 2018-03-11
// Debluring
// added Edgetaper
// 2018-03-12
// added Deconvwnr
// 2018-03-13
// added DeblurFilter class
// 2018-03-14
// added H and h output
// added time elapsed output
// 2018-03-15
// realised G output
// 2018-03-17
// realised any image size processing
// 2018-04-16
// corrected class


#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "DeblurFilter.hpp"




int main(int argc, char* argv[])
{
	int sigma1 = 53;
	int snr = 5200;
	std::string str_Inpath = "D:\\cprojects\\OpenCV(Deblur)\OpenCV(Deblur)\\www\\images";
	std::string str_Outpath = "D:\cprojects\OpenCV(Deblur)\OpenCV(Deblur)\\output\\";
	std::string strInFileName = "original.jpg";

	if (argc == 3)
	{
		str_Inpath = "";
		str_Outpath = "";
		strInFileName = argv[1];
		sigma1 = atoi(argv[2]);

		std::cout << str_Inpath << '\n';
		std::cout << str_Outpath << '\n';
		std::cout << strInFileName << '\n';
		std::cout << sigma1 << '\n';
	}

	if (argc == 4)
	{
		str_Inpath = "";
		str_Outpath = "";
		strInFileName = argv[1];
		sigma1 = atoi(argv[2]);
		snr = atoi(argv[3]);

		std::cout << str_Inpath << '\n';
		std::cout << str_Outpath << '\n';
		std::cout << strInFileName << '\n';
		std::cout << sigma1 << '\n';
		std::cout << snr << '\n';
	}

	cv::Mat imgIn;
	imgIn = cv::imread(strInFileName, cv::IMREAD_UNCHANGED);
	if (imgIn.empty()) //check whether the image is loaded or not
	{
		std::cout << "ERROR : Image cannot be loaded..!!" << '\n';
		return -1;
	}

	cv::Mat imgOut;
	DeblurFilter filter;
	double t0, t1;
	t0 = (double)cv::getTickCount();
	filter.Process(imgIn, imgOut, sigma1, snr);
	t1 = ((double)cv::getTickCount() - t0) / cv::getTickFrequency();
	std::cout << "Total elapsed  CPU time (ms)= " << 1000 * t1 << '\n';
	std::cout << '\n';

	imgOut.convertTo(imgOut, CV_8U);
	normalize(imgOut, imgOut, 0, 255, cv::NORM_MINMAX);

	std::string strOutFileName = strInFileName;
	char  buf[100];
	sprintf_s(buf, "_R = %d_snr = %d", sigma1, snr);
	strOutFileName.insert(strOutFileName.size() - 4, buf);
	imwrite( strOutFileName, imgOut);
	return 0;
}