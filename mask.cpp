#include <iostream>
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core.hpp" 
#include "opencv2/imgproc.hpp"
using namespace cv;

int main(int argc,char **argv)
{
  Mat img = imread("cat.jpg");
  std::vector<Mat> channels(3);
  cv::split(img, channels);

//  Mat mask = cv::zeros(b_channel.shape, channels[0].type());
  Mat mask(channels[0].size(), channels[0].type(), 55);
//  cv::circle(mask, cv::Point(mask.rows/2, mask.cols/2), 200, cv::Scalar(255), -1, 8, 0);

  channels.push_back(mask);

  Mat result;
  cv::merge(channels, result);

  std::cout << img.channels() << "\n";
  std::cout << result.channels() << "\n";

  cv::imshow("img", img);
  cv::imshow("res", result);
  imwrite("circle_cat.jpg", result);
  cv::waitKey(0);
}
