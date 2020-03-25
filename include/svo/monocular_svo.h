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
    friend ostream& operator <<(ostream& os, const MonocularSVO& msvo);
    ~MonocularSVO();
private:
    bool initialized_;
    FrameHandlerMono* vo_;
    vk::AbstractCamera* cam_;
};

std::ostream& operator<< (std::ostream& os, const MonocularSVO& msvo)
{
    if (msvo.initialized_)
        os << "Initialized ";
    else
        os << "Uninitialized ";
    os << "monocular SVO solver with image (w=" << msvo.cam_->width() << ", h=" << msvo.cam_->height() << ")";
}

} // end namespace svo
