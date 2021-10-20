#include "CVImageServer.h"


cv::Mat CVImageServer::CVImageProcess()
{
	Mat src, dest;
	src = imread("C:/Users/gl/Desktop/Temp/photo.png");
	//namedWindow("����opencv", WINDOW_AUTOSIZE);
	//imshow("����opencv", src);

	dest.create(src.size(), src.type());
	//���ز��� �˲���
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (src.channels() == 3)  //ͨ��ֵΪ3  ���Զ���������ͨ�����в���
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
	//��Ӧ�ӿ�
	//bitwise_not(src, dest);

	//namedWindow("����opencv2", WINDOW_AUTOSIZE);
	//imshow("����opencv2", dest);

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
		

		//�����ǰ�����data��ʽ����һ��uchar���͵�vector
		std::vector<uchar> data_encode;
		//ֱ�ӱ���
		cv::imencode(".png", src, data_encode);
		std::cout << "size: " << data_encode.size() << std::endl;
		//�ŵ�string����
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
	
	stream->Read(&tempStream); //��������

	std::cout << "command:" << tempStream.command()<< std::endl;
	std::cout << "command:" << tempStream.command() << ","<< tempStream.encodebuff().size() << std::endl;
	//����
	const std::string strbuf = tempStream.encodebuff();
	std::vector<uchar> data(tempStream.encodebuff().begin(), tempStream.encodebuff().end());
	cv::Mat tempmat = cv::imdecode(data, 1);
	if (tempmat.data != nullptr);
	{
		std::cout << "imdecode maybe error" << std::endl;
		//return ::grpc::Status::OK;
	}
	
	//ͼ����
	cv::Mat out = CVImageProcess(tempmat);

	//����+��������
	CVImageService::ImageMessage* tempbuf = new CVImageService::ImageMessage();
	//�����ǰ�����data��ʽ����һ��uchar���͵�vector
	std::vector<uchar> data_encode;
	//ֱ�ӱ���
	cv::imencode(".png", out, data_encode);
	std::cout << "size: " << data_encode.size() << std::endl;
	//�ŵ�string����
	std::string str_encode(data_encode.begin(), data_encode.end());

	tempbuf->set_command("image");
	tempbuf->set_colum(55);
	tempbuf->set_encodebuff(str_encode);

	if (!stream->Write(*tempbuf)) //��������
	{
		std::cout << "write error";
	}

	return ::grpc::Status::OK;
}

cv::Mat CVImageServer::CVImageProcess(cv::Mat Image)
{
	cv::Mat dest;
	dest.create(Image.size(), Image.type());
	//���ز��� �˲���
	for (int i = 0; i < Image.rows; i++)
	{
		for (int j = 0; j < Image.cols; j++)
		{
			if (Image.channels() == 3)  //ͨ��ֵΪ3  ���Զ���������ͨ�����в���
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