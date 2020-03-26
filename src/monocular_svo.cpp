#include "svo/monocular_svo.h"

namespace svo {

MonocularSVO::MonocularSVO() : initialized_(false), vo_(NULL), cam_(NULL) {}

MonocularSVO::~MonocularSVO()
{
//    delete vo_;
//    delete cam_;
}

bool MonocularSVO::initialize(const std::string &cam_model, const std::vector<double> &cam_params)
{
    if (cam_model == "Pinhole")
    {
        if (cam_params.size() != 10)
            return false;
        else
        {
            int img_width  = static_cast<int>(cam_params[0]);
            int img_height = static_cast<int>(cam_params[1]);
            double fx      = cam_params[2];
            double fy      = cam_params[3];
            double cx      = cam_params[4];
            double cy      = cam_params[5];
            double d0      = cam_params[6];
            double d1      = cam_params[7];
            double d2      = cam_params[8];
            double d3      = cam_params[9];
            cam_ = new vk::PinholeCamera(img_width, img_height, fx, fy, cx, cy,
                                         d0, d1, d2, d3);
        }
    }
    else if (cam_model == "ATAN")
    {
        if (cam_params.size() != 7)
            return false;
        else
        {
            int img_width  = static_cast<int>(cam_params[0]);
            int img_height = static_cast<int>(cam_params[1]);
            double fx      = cam_params[2];
            double fy      = cam_params[3];
            double cx      = cam_params[4];
            double cy      = cam_params[5];
            double d0      = cam_params[6];
            cam_ = new vk::ATANCamera(img_width, img_height, fx, fy, cx, cy, d0);
        }
    }
    else
        return false;

    vo_ = new FrameHandlerMono(cam_);
    vo_->start();

    initialized_ = true;
    return true;
}

void MonocularSVO::update(const cv::Mat &img, const double &t)
{
    vo_->addImage(img, t);
    if (vo_->stage() == FrameHandlerMono::STAGE_PAUSED)
        usleep(100000);
}

void MonocularSVO::getPose(Eigen::Vector3d &trans, Eigen::Matrix3d &Rot)
{
    SE3 T_frame_from_world = vo_->lastFrame()->T_f_w_; // .inverse() ?
    trans = T_frame_from_world.translation();
    Rot = T_frame_from_world.rotation_matrix();
}

} // end namespace svo
