//
// Created by markus on 21.05.21.
//

#include "MapField.h"

cv::Mat MapField::draw() {
    int imageWidth = (FIELD_WIDTH + 2 * BORDER_WIDTH + 1);
    int imageHeight = (FIELD_HEIGHT + 2 * BORDER_WIDTH + 1);
    cv::Mat img = cv::Mat::zeros(imageHeight, imageWidth, CV_8UC3);

    // bg
    cv::rectangle(img,cv::Point2i (0,0),cv::Point2i (imageWidth,imageHeight),this->color_bg,cv::FILLED);

    // left border
    if(this->color_left_enabled) {
        cv::rectangle(img, cv::Point2i(0, 0), cv::Point2i(BORDER_WIDTH, imageHeight), this->color_left, cv::FILLED);
    }

    // cross
    if (this->cross) {
        cv::line(img, cv::Point2i(BORDER_WIDTH + 3, BORDER_WIDTH + 3), cv::Point2i(BORDER_WIDTH + FIELD_WIDTH - 3, BORDER_WIDTH + FIELD_HEIGHT - 3),
                 cv::Scalar(0, 0, 0), 2);
        cv::line(img, cv::Point2i(BORDER_WIDTH + FIELD_WIDTH - 3, BORDER_WIDTH + 3), cv::Point2i(BORDER_WIDTH + 3, BORDER_WIDTH + FIELD_HEIGHT - 3),
                 cv::Scalar(0, 0, 0), 2);
    }

    return img;
}

void MapField::setColorLeft(cv::Scalar color) {
    this->color_left_enabled = true;
    this->color_left = color;
}
