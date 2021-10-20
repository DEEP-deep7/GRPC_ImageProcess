#include"../include/CVImageClient.h"


int main()
{
	CVImageClient client(grpc::CreateChannel("localhost:50052",
		grpc::InsecureChannelCredentials()));
	std::cout << "start handle image stream" << std::endl;
	

	int modle;
	
	
	while (true)
	{
		std::cout << "选择模式：1为图像传输测试，2为远端图像处理demo" << std::endl;
		std::cin >> modle;

		switch (modle)
		{
		case 1:
			client.GetImageData();
			break;
		case 2:
			client.ImageProcess();
			break;
		default:
			std::cout << "error modle";
			break;
		}
	}


	return 0;
}