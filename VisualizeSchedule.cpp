//
// Created by markus on 19.05.21.
//

#include "VisualizeSchedule.h"

unsigned int FIELD_WIDTH = 26;
unsigned int FIELD_HEIGHT = 26;
unsigned int BORDER_WIDTH = 4;
unsigned int TABLE_BORDER_WIDTH = 3;


VisualizeSchedule::VisualizeSchedule(cv::Point2i size) {
    this->matrix.resize(size.x, std::vector<MapField>(size.y, MapField()));
    this->matrixBounds = size;
}

void VisualizeSchedule::setBGColor(cv::Point2i pos, cv::Scalar color) {
    this->matrix[pos.x][pos.y].color_bg = color;
}

void VisualizeSchedule::setLeftBorderColor(cv::Point2i pos, cv::Scalar color) {
    this->matrix[pos.x][pos.y].setColorLeft(color);
}

void VisualizeSchedule::setCross(cv::Point2i pos, bool newState) {
    this->matrix[pos.x][pos.y].cross = newState;
}

void VisualizeSchedule::show() {
    // size of table
    int fieldTotalWidth = (FIELD_WIDTH + 2 * BORDER_WIDTH + TABLE_BORDER_WIDTH);
    int fieldTotalHeight = (FIELD_HEIGHT + 2 * BORDER_WIDTH + TABLE_BORDER_WIDTH);
    int tableWidth = (fieldTotalWidth * this->matrixBounds.x) + TABLE_BORDER_WIDTH;
    int tableHeight = (fieldTotalHeight * this->matrixBounds.y) + TABLE_BORDER_WIDTH;

    // adjust size for labels
    int totalWidth = tableWidth;
    int totalHeight = tableHeight + BORDER_WIDTH + 23;  // "BORDER_WIDTH + x" for numbers row
    const int primLabelWidth = 2*FIELD_WIDTH;
    const int secLabelWidth = 2*FIELD_WIDTH;
    if (!this->primaryLabels.empty()) {
        totalWidth += primLabelWidth;
    }
    if (!this->secondaryLabels.empty()) {
        totalWidth += secLabelWidth;
    }

    // create blank image
    cv::Mat image = cv::Mat::zeros(totalHeight, totalWidth, CV_8UC3);


    // borders of last row and column
    cv::rectangle(image, cv::Point2i(0, tableHeight - TABLE_BORDER_WIDTH), cv::Point2i (tableWidth, tableHeight), Colors::gray, TABLE_BORDER_WIDTH);
    cv::rectangle(image, cv::Point2i(tableWidth - TABLE_BORDER_WIDTH, 0), cv::Point2i (tableWidth, tableHeight), Colors::gray, TABLE_BORDER_WIDTH);
    for (int x = 0; x < this->matrixBounds.x; ++x) {
        int x_offset = x * fieldTotalWidth;
        cv::rectangle(image, cv::Point2i(x_offset, 0), cv::Point2i (x_offset + TABLE_BORDER_WIDTH, tableHeight), Colors::gray, cv::FILLED); // vertical table lines

        for (int y = 0; y < this->matrixBounds.y; ++y) {
            int y_offset = y * fieldTotalHeight;
            cv::rectangle(image, cv::Point2i(x_offset, y_offset), cv::Point2i (x_offset + fieldTotalWidth, y_offset + TABLE_BORDER_WIDTH), Colors::gray, cv::FILLED); // horizontal table lines

            cv::Mat currentTile = this->matrix[x][y].draw();
            currentTile.copyTo(image(cv::Rect(x_offset + TABLE_BORDER_WIDTH, y_offset + TABLE_BORDER_WIDTH,currentTile.cols, currentTile.rows)));
        }
    }

    // labels
    int x_offset = tableWidth;
    if (!this->primaryLabels.empty()) {
        for (int y = 0; y < this->primaryLabels.size(); ++y) {
            cv::putText(image, this->primaryLabels[y], cv::Point2i(x_offset + BORDER_WIDTH*2, fieldTotalHeight * y + fieldTotalHeight - BORDER_WIDTH*2), cv::FONT_HERSHEY_SIMPLEX, 0.65, Colors::white, 2);
        }

        x_offset += primLabelWidth;  // adjust x_offset in case of more label columns (sec labels) will be added
    }
    if (!this->secondaryLabels.empty()) {
        for (int y = 0; y < this->secondaryLabels.size(); ++y) {
            cv::putText(image, this->secondaryLabels[y], cv::Point2i(x_offset + BORDER_WIDTH*2, fieldTotalHeight * y + fieldTotalHeight - BORDER_WIDTH*2), cv::FONT_HERSHEY_SIMPLEX, 0.5, Colors::white, 1);
        }
    }

    // numbers
    for (int x = 0; x < this->matrixBounds.x; ++x) {
        cv::putText(image, std::to_string(x), cv::Point2i(x*fieldTotalWidth+BORDER_WIDTH, totalHeight-BORDER_WIDTH), cv::FONT_HERSHEY_SIMPLEX, 0.65, Colors::white, 2);
    }


    cv::imshow(this->windowTitle, image);
    cv::waitKey();
}

void VisualizeSchedule::setPrimaryLabels(std::vector<std::string> labels) {
    this->primaryLabels = labels;
}

void VisualizeSchedule::setSecondaryLabels(std::vector<std::string> labels) {
    this->secondaryLabels = labels;
}

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


const cv::Scalar Colors::black = cv::Scalar (0,0,0);
const cv::Scalar Colors::gray = cv::Scalar (200,200,200);
const cv::Scalar Colors::red = cv::Scalar (0,0,255);
const cv::Scalar Colors::green = cv::Scalar (20,200,20);
const cv::Scalar Colors::white = cv::Scalar (255,255,255);