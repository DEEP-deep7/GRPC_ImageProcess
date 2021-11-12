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

	void VideoRequest(std::string * nn);

	void Login();

	void NetViedo(std::string username);

private:
	void ShowImage(cv::Mat image);

	bool m_IsViedo = true;

	std::mutex* m_tex;

	std::string m_client;
	std::string* m_clientPtr;

	std::string m_username;

	std::unique_ptr<CVImageService::CVServer::Stub> m_stub;
};