#include "CVImageServer.h"


cv::Mat CVImageServer::CVImageProcess()
{
	Mat src, dest;
	src = imread("C:/Users/gl/Desktop/Temp/3.jpg");
	//namedWindow("测试opencv", WINDOW_AUTOSIZE);
	//imshow("测试opencv", src);

	dest.create(src.size(), src.type());
	//像素操作 滤波器
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (src.channels() == 3)  //通道值为3  可以对以下三个通道进行操作
			{
				int b = src.at<Vec3b>(i, j)[0];
				int g = src.at<Vec3b>(i, j)[1];
				int r = src.at<Vec3b>(i, j)[2];
				//dest.at<Vec3b>(i, j)[0] =  b; 
				//dest.at<Vec3b>(i, j)[1] =  g;
				//if (r < 204 && r > 202 && b < 38 && b > 36 && g < 35 && g > 33)
				if (r >= 200)
				{
					dest.at<Vec3b>(i, j)[2] = 255;
					dest.at<Vec3b>(i, j)[0] = 255;
					dest.at<Vec3b>(i, j)[1] = 255;
				}

			}
		}
	}
	std::cout << "colorb:" << int(dest.at<Vec3b>(5, 10)[0]) << std::endl;
	std::cout << "colorg:" << int(dest.at<Vec3b>(5, 10)[1]) << std::endl;
	std::cout << "colorr:" << int(dest.at<Vec3b>(5, 10)[2]) << std::endl;
	std::cout << "rows::" << int(dest.rows) << std::endl;
	std::cout << "size::" << dest.size() << std::endl;
	std::cout << "value:" << int(src.at<Vec3b>(1, 0)[0]) << "," << int(src.at<Vec3b>(1, 0)[1]) << "," << int(src.at<Vec3b>(1, 0)[2]) << std::endl;
	//对应接口
	//bitwise_not(src, dest);

	//namedWindow("测试opencv2", WINDOW_AUTOSIZE);
	//imshow("测试opencv2", dest);

	//waitKey(0);
	return src;
}

CVImageServer::CVImageServer()
{
}

::grpc::Status CVImageServer::CVMatImageStream(::grpc::ServerContext* context, 
	::grpc::ServerReaderWriter<::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* stream)
{
		std::cout << "start server" << std::endl;
		CVImageService::ImageMessage tempStream;// = dynamic_cast<CVImageService::ImageMessage*>(context);
		Mat src = CVImageProcess();
		CVImageService::ImageMessage* tempbuf = new CVImageService::ImageMessage();
	
		stream->Read(&tempStream);
	
		std::cout << "command:" << tempStream.command()<<","<< tempStream.encodebuff().size()<<std::endl;
		

		//编码的前必须的data格式，用一个uchar类型的vector
		std::vector<uchar> data_encode;
		//直接编码
		cv::imencode(".png", src, data_encode);
		std::cout << "size: " << data_encode.size() << std::endl;
		//放到string里面
		std::string str_encode(data_encode.begin(), data_encode.end());
		
		tempbuf->set_command("image");
		tempbuf->set_colum(55);
		tempbuf->set_row(55);
		tempbuf->set_encodebuff(str_encode);
	
		if (!stream->Write(*tempbuf))
		{
			std::cout << "write error";
		}
	return ::grpc::Status();
}

::grpc::Status CVImageServer::CVImageProcessFunction(::grpc::ServerContext* context, 
	::grpc::ServerReaderWriter<::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* stream)
{

	std::cout << "start server" << std::endl;
	CVImageService::ImageMessage tempStream;// = dynamic_cast<CVImageService::ImageMessage*>(context);
	
	stream->Read(&tempStream); //接收数据

	std::cout << "command:" << tempStream.command()<< std::endl;
	std::cout << "command:" << tempStream.command() << ","<< tempStream.encodebuff().size() << std::endl;
	//解码
	const std::string strbuf = tempStream.encodebuff();
	std::vector<uchar> data(tempStream.encodebuff().begin(), tempStream.encodebuff().end());
	cv::Mat tempmat = cv::imdecode(data, 1);
	if (tempmat.data != nullptr);
	{
		std::cout << "imdecode maybe error" << std::endl;
		//return ::grpc::Status::OK;
	}
	
	//图像处理
	cv::Mat out = CVImageProcess(tempmat);

	//编码+发送数据
	CVImageService::ImageMessage* tempbuf = new CVImageService::ImageMessage();
	//编码的前必须的data格式，用一个uchar类型的vector
	std::vector<uchar> data_encode;
	//直接编码
	cv::imencode(".png", out, data_encode);
	std::cout << "size: " << data_encode.size() << std::endl;
	//放到string里面
	std::string str_encode(data_encode.begin(), data_encode.end());

	tempbuf->set_command("image");
	tempbuf->set_colum(55);
	tempbuf->set_encodebuff(str_encode);

	if (!stream->Write(*tempbuf)) //发送数据
	{
		std::cout << "write error";
	}

	return ::grpc::Status::OK;
}

::grpc::Status CVImageServer::CVLogin(::grpc::ServerContext* context,
	::grpc::ServerReaderWriter<::CVImageService::ReplyVideoMessage, ::CVImageService::RequestVideoMessage>* stream)
{
	std::cout << "CVLogin" << std::endl;

	::CVImageService::RequestVideoMessage request;
	stream->Read(&request);

	if (request.command().empty())
	{
		std::cout << "no command" << std::endl;
	}

	std::cout << "user name:" << request.userdata(0) <<"，command:" << request.command() << std::endl;
	if (request.command().compare("Login") == 0)
	{
		std::string username = request.userdata(0);

		if (m_UserMap.find(username) == m_UserMap.end())
		{
			m_UserMap.insert(std::pair<std::string,
				::grpc::ServerReaderWriter<::CVImageService::ReplyVideoMessage,
				::CVImageService::RequestVideoMessage>*>(username, stream));
		}

		::CVImageService::ReplyVideoMessage reply;
		reply.set_command("Login");
		reply.add_userdata("secuess");  //不要使用set_userdata(int,cont char*)这样的接口，会崩溃
		int i = 1;
		for (auto it = m_UserMap.begin(); it != m_UserMap.end(); it++)
		{
			if (it->first.compare(username)!= 0) //不展示自己的username
			{
				reply.add_userdata(it->first);
			}
		}
		stream->Write(reply);
	}

	return ::grpc::Status();
}


::grpc::Status CVImageServer::CVVideo(::grpc::ServerContext* context,
	::grpc::ServerReaderWriter<::CVImageService::ReplyVideoMessage, ::CVImageService::RequestVideoMessage>* stream)
{
	//std::cout << "CVLogin" << std::endl;

	::CVImageService::RequestVideoMessage request;
	stream->Read(&request);

	if (request.command().compare("Video") != 0)
	{
		std::string username = request.userdata(0);
		
		auto Userstream = m_UserMap.at(username);
		if (Userstream == nullptr)
		{
			std::cout << "find error stream" << std::endl;
			return ::grpc::Status::OK;
		}

		::CVImageService::ReplyVideoMessage reply;
		reply.set_command("Video");
		reply.set_userdata(0,"secuess");
		reply.set_videobuff(request.videobuff());
		Userstream->Write(reply);
	}

	return ::grpc::Status::OK;
}

cv::Mat CVImageServer::CVImageProcess(cv::Mat Image)
{
	cv::Mat dest;
	dest.create(Image.size(), Image.type());
	//像素操作 滤波器
	for (int i = 0; i < Image.rows; i++)
	{
		for (int j = 0; j < Image.cols; j++)
		{
			if (Image.channels() == 3)  //通道值为3  可以对以下三个通道进行操作
			{
				int b = Image.at<Vec3b>(i, j)[0];
				int g = Image.at<Vec3b>(i, j)[1];
				int r = Image.at<Vec3b>(i, j)[2];
				//dest.at<Vec3b>(i, j)[0] =  b; 
				//dest.at<Vec3b>(i, j)[1] =  g;
				//if (r < 204 && r > 202 && b < 38 && b > 36 && g < 35 && g > 33)
				if (r >= 200)
				{
					dest.at<Vec3b>(i, j)[2] = 255;
					dest.at<Vec3b>(i, j)[0] = 255;
					dest.at<Vec3b>(i, j)[1] = 255;
				}

			}
		}
	}
	return dest;
}


