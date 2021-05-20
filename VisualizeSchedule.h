//
// Created by markus on 19.05.21.
//

#ifndef SCHEDULING_SIM_VISUALIZESCHEDULE_H
#define SCHEDULING_SIM_VISUALIZESCHEDULE_H

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

struct Colors {
    static const cv::Scalar black;
    static const cv::Scalar gray;
    static const cv::Scalar red;
    static const cv::Scalar green;
    static const cv::Scalar white;
};


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

class VisualizeSchedule {
private:
    std::vector<std::vector<MapField>> matrix;
    cv::Point2i matrixBounds;
    std::vector<std::string> primaryLabels;
    std::vector<std::string> secondaryLabels;
public:
    std::string windowTitle = "Schedule";

    /**
     * @param size shape of elements (columns/steps, processes)
     */
    explicit VisualizeSchedule(cv::Point2i size);

    /** set background color of cell pos
     *
     */
    void setBGColor(cv::Point2i pos, cv::Scalar color);

    void setLeftBorderColor(cv::Point2i pos, cv::Scalar color);

    /** cross-marker in cell
     */
    void setCross(cv::Point2i pos, bool newState);

    void setPrimaryLabels(std::vector<std::string> labels);

    void setSecondaryLabels(std::vector<std::string> labels);

    /** add or remove columns from/to current object
     *
     * @param n number of new columns; negative to remove columns
     */
    void resizeColumns(int n=1);

    cv::Point2i getMatrixBounds();

    /** render */
    void show();
};


#endif //SCHEDULING_SIM_VISUALIZESCHEDULE_H
