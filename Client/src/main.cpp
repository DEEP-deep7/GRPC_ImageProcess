#include"../include/CVImageClient.h"


int main()
{
	CVImageClient client(grpc::CreateChannel("localhost:50052",
		grpc::InsecureChannelCredentials()));
	std::cout << "start handle image stream" << std::endl;
	
	int modle;
	
	
	while (true)
	{
		std::cout << "ѡ��ģʽ��1Ϊͼ������ԣ�2ΪԶ��ͼ����demo��3Ϊ��¼+������Ƶ" << std::endl;
		std::cout << "������Ƶ���ܱ����ȵ�¼" << std::endl;
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