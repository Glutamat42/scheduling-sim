//
// Created by markus on 21.05.21.
//

#ifndef SCHEDULING_SIM_MAPFIELD_H
#define SCHEDULING_SIM_MAPFIELD_H

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "constants.h"
#include "Colors.h"


class MapField {
private:
    bool color_left_enabled = false;
    cv::Scalar color_left = CV_RGB(255, 255, 255);

public:
    cv::Scalar color_bg = CV_RGB(255, 255, 255);
    bool cross = false;

    void setColorLeft(cv::Scalar color);

    cv::Mat draw();
};


#endif //SCHEDULING_SIM_MAPFIELD_H
