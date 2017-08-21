#pragma once
/*************************************************************************
> File Name: output_pose.cpp
> Author: Guo Hengkai
> Description:
> Created Time: Sun 06 Nov 2016 10:47:29 AM CST
************************************************************************/
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "boost/algorithm/string.hpp"
#include "google/protobuf/text_format.h"

#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/net.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/format.hpp"
#include "caffe/util/io.hpp"

#include <opencv2\opencv.hpp>

using caffe::Blob;
using caffe::Caffe;
using caffe::Datum;
using caffe::Net;
using std::string;
using std::vector;

#define SQR(x) ((x)*(x))


class HandPoseEstimator {
public:
	HandPoseEstimator();
	~HandPoseEstimator();

	int gpu;		//Optional; run in GPU mode on given device ID. -1 for CPU.
	string model;	// "The model definition protocol buffer text file.");
	string weights;	// "The weights to initialize model.");
	string phase;	// "Network phase (train or test).");
	string output_blob;	// "Blob name for output.")
	double fx;
	double fy;
	double ux;
	double uy;
	int lower;
	int upper;
	vector<int> cube_length;
	int height, width;

	boost::shared_ptr<Net<float> > test_net;

	int init_model();
	vector<float> predict(const cv::Mat& cv_img);
	void Mat2Blob(const cv::Mat &mat,
		boost::shared_ptr<Blob<float> > blob);

	void get_center(const cv::Mat& cv_img, vector<float>& center, int lower, int upper);

	cv::Mat crop_image(const cv::Mat& cv_img,
		const vector<float>& center, const vector<int>& cube_length,
		float fx, float fy, int height, int width);
};
