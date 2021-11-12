#include"../include/CVImageClient.h"


int main()
{
	CVImageClient client(grpc::CreateChannel("localhost:50052",
		grpc::InsecureChannelCredentials()));
	std::cout << "start handle image stream" << std::endl;
	
	int modle;
	
	
	while (true)
	{
		std::cout << "选择模式：1为图像传输测试，2为远端图像处理demo，3为登录+网络视频" << std::endl;
		std::cout << "网络视频功能必须先登录" << std::endl;
		std::cin >> modle;

		switch (modle)
		{
		case 1:
			client.GetImageData();
			break;
		case 2:
			client.ImageProcess();
			break;
		case 3:
			client.Login();
			break;
		default:
			std::cout << "error modle";
			break;
		}
	}


	return 0;
}