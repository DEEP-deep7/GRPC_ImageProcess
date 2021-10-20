#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "../ImageStream.grpc.pb.h"
//#include <ImageStream.pb.h>
//pb.hͷ�ļ�������ַ�������Unicode�ľ��棬��Ҫ��ͷ�ļ�תΪGB2312���棬������뱨��

using namespace cv;
using grpc::ServerContext;
//using grpc::ServerReaderWriter;
using grpc::Status;
using CVImageService::CVServer;
//using grpc::Channel;
//using namespace namespace_uploadpic;
//class CVImageService::CVServer::Service;

class CVImageServer final : public CVServer::Service
{
public:

	

	CVImageServer();

	::grpc::Status CVMatImageStream(::grpc::ServerContext* context,
		::grpc::ServerReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* stream);

	::grpc::Status CVImageProcessFunction(::grpc::ServerContext* context, 
		::grpc::ServerReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* stream);


private:
	cv::Mat CVImageProcess();

	cv::Mat CVImageProcess(cv::Mat Image);
};