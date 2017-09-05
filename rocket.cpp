#include <iostream>
#include <unistd.h>
#include <aruco/aruco.h>
#include <aruco/cvdrawingutils.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core.hpp" 
#include "opencv2/imgproc.hpp"
#include <stdlib.h>
using namespace cv;
using namespace aruco;

int main(int argc,char **argv)
{




    VideoCapture cap(1);
    //if(!cap.isOpened())
//        return -1;

    int inners[4] = {2, 3, 1, 0};
    int crop_size = 512;
    cv::Point2f target_corners[] = { cv::Point2f(0,0), cv::Point2f(crop_size,0), cv::Point2f(0,crop_size), cv::Point2f(crop_size,crop_size) };

    Mat frame;
    namedWindow("win",1);
    Mat roi;
    namedWindow("roi",1);
    MarkerDetector MDetector;
    string prefix = "/run/user/1000/gvfs/afp-volume\\:host\\=sarsas-Mac-Pro.local\\,user\\=sarsa\\,volume\\=";
    string rocket_path = prefix+ "coets/Coet_";
    string satellite_path = prefix+"satelits/Satelit_";
    string temp_path =  prefix+"Public/";
    //string temp_path =  "./";
    int rocket_count = 1;
    int satellite_count = 1;

    bool is_empty = false;

    while (true)
    {
        cap >> frame;
        vector<Marker> Markers;
        MDetector.detect(frame,Markers);

        vector<int> rocket_inds = {0,1,2,3};
        vector<int> satellite_inds = {4,5,6,7};
        vector<int> empty_inds = {8};

        vector<int> frame_inds(Markers.size());
        for (unsigned int i=0;i<Markers.size();i++) {
          frame_inds[i] = Markers[i].id;
        }

        std::string roi_content = "";
        if (frame_inds == rocket_inds) roi_content = "rocket";
        else if (frame_inds == satellite_inds) roi_content = "satellite";
        else if (frame_inds == satellite_inds) roi_content = "satellite";
        else if (frame_inds == empty_inds) roi_content = "empty";

        if (roi_content != "" && roi_content != "empty") {

          cv::Point2f roi_corners[4];
          for (unsigned int i=0;i<4;i++) {
            roi_corners[i] = Markers[i][inners[i]];
          }
          
          cv::Mat M = cv::getPerspectiveTransform(roi_corners, target_corners);
          cv::warpPerspective(frame, roi, M, {crop_size, crop_size});
          cv::imshow("roi",roi);

          if (is_empty == true) {
	    is_empty = false;
            string temp_file = temp_path+"img.jpg" ;
            cv::imwrite("./img.jpg", roi);
            system(("cp ./img.jpg "+temp_file).c_str());
            if (roi_content == "rocket") {
              std::string file_name = rocket_path+std::to_string(rocket_count)+".jpg";
              std::string command = "cp "+temp_file+ " "+file_name+"\n";
              system(command.c_str());
              cout << command.c_str() << "\n";
              rocket_count += 1;
            }
            else {
              std::string file_name = satellite_path+std::to_string(satellite_count)+".jpg";
              std::string command = "cp "+temp_file+" "+file_name+"\n";
              system(command.c_str());
              cout << command.c_str() << "\n";
              satellite_count += 1;
            }
	  }

	}

        if (roi_content == "empty") {
	  is_empty = true;
	}

        cout << roi_content << "\n";
        cv::imshow("win",frame);
        cv::waitKey(30);
    }

}
