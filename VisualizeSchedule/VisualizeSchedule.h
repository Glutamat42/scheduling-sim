//
// Created by markus on 19.05.21.
//

#ifndef SCHEDULING_SIM_VISUALIZESCHEDULE_H
#define SCHEDULING_SIM_VISUALIZESCHEDULE_H

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "constants.h"
#include "MapField.h"
#include "Colors.h"


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

    VisualizeSchedule() : VisualizeSchedule(cv::Point2i(0,0)) {}

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
