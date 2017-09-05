#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <aruco/aruco.h>
using namespace cv;
using namespace std;

int main(int argc, char **argv) {
        auto dict_names=aruco::Dictionary::getDicTypes();
        cerr<<"\t\tDictionaries: ";
        for(auto dict:dict_names)    cerr<<dict<<" ";cerr<<endl;
        int pixSize = 25;
        bool enclosingCorners=false;
        bool waterMark=true;
        //aruco::Dictionary dic=aruco::Dictionary::load(aruco::Dictionary::DICT_6X6_250);
        //aruco::Dictionary dic=aruco::Dictionary::load(aruco::Dictionary::ARUCO);
        aruco::Dictionary dic=aruco::Dictionary::loadPredefined(aruco::Dictionary::ARUCO);

        for (int i=0; i<16; i++) {
          cv::imwrite("img"+std::to_string(i)+".jpg", dic.getMarkerImage_id(i,pixSize,waterMark,enclosingCorners));
        }
}
