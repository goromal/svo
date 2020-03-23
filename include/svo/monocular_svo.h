#pragma once
#include <svo/frame_handler_mono.h>
#include <svo/map.h>
#include <svo/config.h>
#include <vikit/abstract_camera.h>
#include <boost/thread.hpp>
#include <Eigen/Core>
#include <vikit/pinhole_camera.h>
#include <vikit/atan_camera.h>
#include <svo/frame.h>

namespace svo {

class MonocularSVO
{
public:
    MonocularSVO();
    bool initialize(const std::string &cam_model, const std::vector<double> &cam_params);
    void update(const cv::Mat &img, const double &t);
    void getPose(Eigen::Vector3d &trans, Eigen::Matrix3d &Rot);
    ~MonocularSVO();
private:
    bool initialized_;
    FrameHandlerMono* vo_;
    vk::AbstractCamera* cam_;
};

} // end namespace svo
