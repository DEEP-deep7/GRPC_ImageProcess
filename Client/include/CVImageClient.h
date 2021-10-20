#include <grpcpp/grpcpp.h>
#include "../ImageStream.grpc.pb.h"
#include <opencv2/core/core.hpp>
#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

using grpc::Channel;

class CVImageClient
{
public:
	CVImageClient(std::shared_ptr<Channel> channel);

	void ImageProcess();

	void GetImageData();

private:
	void ShowImage(cv::Mat image);



	std::unique_ptr<CVImageService::CVServer::Stub> m_stub;
};