SVO
===

This code implements a semi-direct monocular visual odometry pipeline, as described in the video and paper below. Adapted for portability from ETH Zurich's ROS-enabled pipeline at https://github.com/uzh-rpg/rpg_svo. Python wrappers implemented [TODO].

Video: http://youtu.be/2YnIMfw6bJY

Paper: http://rpg.ifi.uzh.ch/docs/ICRA14_Forster.pdf

### Compiling

Install Boost and Eigen3:

```bash
sudo apt-get install libboost-all-dev libeigen3-dev
```

Install opencv (Ubuntu instructions at https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html)

Clone and build this repository:

```bash
git clone --recurse-submodules https://github.com/goromal/svo.git
mkdir build && cd build
cmake ..
make
```
