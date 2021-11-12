#include "..\include\CVImageClient.h"
#include <grpcpp/client_context.h>
#include <thread>
#include <mutex>


CVImageClient::CVImageClient(std::shared_ptr<Channel> channel)
{
	m_stub = CVImageService::CVServer::NewStub(channel);
    m_tex = new std::mutex;
    m_clientPtr = &m_client;
}

void CVImageClient::ShowImage(cv::Mat image)
{
    if (image.empty())
    {
        std::cout << "empty image" << std::endl;
        return;
    }
    std::cout << "CVHandle" << std::endl;
    cv::namedWindow("测试opencv", cv::WINDOW_AUTOSIZE);
    cv::imshow("测试opencv", image);
    cv::waitKey(0);

}


void CVImageClient::GetImageData()
{
    std::string command;
    std::cout << "intput command" << std::endl;
    std::cin >> command;
    std::cout << "command is:" << command << std::endl;
    grpc::ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<CVImageService::ImageMessage, CVImageService::ImageMessage> > stream(
        m_stub->CVMatImageStream(&context));  

    std::thread writer([stream, command]() {
        std::cout << "Client setPkg" << std::endl;
        CVImageService::ImageMessage commandPkg;
        commandPkg.set_command(command);
        commandPkg.set_colum(0);
        commandPkg.set_row(0);
        //commandPkg.set_state(0);
        //commandPkg.set_imagestream(1, "asdfasdf");//为什么这么写会导致客户端崩溃
        std::cout << "Client Write" << std::endl;
        stream->Write(commandPkg);
        stream->WritesDone();
        std::cout << "write over" << std::endl;
        });

    CVImageService::ImageMessage imagedata;
    if (!stream->Read(&imagedata))
    {
        std::cout << "接收失败"<<std::endl;
    }
    cv::Mat tempmat;
    const std::string strbuf = imagedata.encodebuff();
    std::vector<uchar> data(strbuf.begin(), strbuf.end());

    tempmat = cv::imdecode(data, 1);
    std::cout << "command:" << imagedata.command()<<std::endl;
    if (tempmat.empty());
    {
        std::cout << "imdecode maybe error" << std::endl;
    }

    ShowImage(tempmat);
}

void CVImageClient::VideoRequest(std::string* nn)
{
    //要开启一个线程来监听返回消息，也可以用io多路复用
    std::cout << "开始监听回复消息" << std::endl;
    grpc::ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<CVImageService::RequestVideoMessage, CVImageService::ReplyVideoMessage>> stream(
        m_stub->CVVideoRequest(&context));
    
    CVImageService::ReplyVideoMessage reply;
    stream->Read(&reply);
    if (reply.command().compare("VideoRequest") == 0)
    {
        /*CVImageService::RequestVideoMessage request;
        request.set_command("argue");
        std::cout << "client:" << nn <<std::endl;
        request.add_userdata(m_username);
        request.add_userdata(*nn);
        stream->Write(request);
        m_IsViedo = false;*/
        std::cout << "接收图像" << std::endl;
    }
    else
    {
        std::cout << "error command:" << reply.command();
        return;
    }
    
    //接收图像
    grpc::ClientContext context2;
    std::shared_ptr<grpc::ClientReaderWriter<CVImageService::RequestVideoMessage, CVImageService::ReplyVideoMessage>> stream2(
        m_stub->CVVideo(&context2));
    
    CVImageService::ReplyVideoMessage reply2;
    cv::Mat tempmat;
    //std::string strbuf;
    std::vector<uchar> data;
    while (stream2->Read(&reply2))
    {
        if (reply2.command().compare("video") == 0)
        {
            data.resize(reply2.videobuff().size());
            std::copy(reply2.videobuff().begin(), reply2.videobuff().end(), data.begin());
            
            

            tempmat = cv::imdecode(data, 1);
            if (tempmat.empty());
            {
                std::cout << "imdecode maybe error" << std::endl;
                //return;
            }
            ShowImage(tempmat);
        }
        std::cout << "recive image" << std::endl;
    }
    
}

void CVImageClient::Login()
{
    std::cout << "输入用户名" << std::endl;
    
    std::cin >> m_username;
    grpc::ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<CVImageService::RequestVideoMessage, CVImageService::ReplyVideoMessage>> stream(
        m_stub->CVLogin(&context));

    CVImageService::RequestVideoMessage request;
    request.add_userdata(m_username);
    request.set_command("Login");
    //request.set_userdata(0, "Login");
    stream->Write(request);

    CVImageService::ReplyVideoMessage reply;
    stream->Read(&reply);
    if (reply.userdata(0).compare("secuess") != 0)
    {
        std::cout << "登录失败" << std::endl;
        return;
    }
    
    std::cout << "登录成功，用户列表如下：" << std::endl;
    for (int i = 1; i < reply.userdata_size(); i++)
    {
        std::cout << reply.userdata(i) << std::endl;
    }


    std::thread t(&CVImageClient::VideoRequest,this , m_clientPtr);
    //t.detach();

    grpc::ClientContext context2;
    std::shared_ptr<grpc::ClientReaderWriter<CVImageService::RequestVideoMessage, CVImageService::ReplyVideoMessage>> stream2(
        m_stub->CVVideoRequest(&context2));
    std::cout << "输入用户名进行呼叫" << std::endl;
    
    std::cin >> m_client;
    
    CVImageService::RequestVideoMessage request2;
    request2.set_command("VideoRequest");
    request2.add_userdata(m_username);
    request2.add_userdata(m_client);
    std::cout << "m_client:" << m_client <<std::endl;
    stream2->Write(request2);

    CVImageService::ReplyVideoMessage reply2;
    stream2->Read(&reply2);

    /*if (reply2.command().compare("argue") != 0)
    {
        std::cout << "用户拒绝:" << reply2.command() << std::endl;
        return;
    }*/

    //发送图像
    NetViedo(m_username);
    
    t.join();
    

}

void CVImageClient::NetViedo(std::string username)
{
    
    std::cout << "发送图像" << std::endl;
    grpc::ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<CVImageService::RequestVideoMessage, CVImageService::ReplyVideoMessage>> stream(
        m_stub->CVVideo(&context));

    //发送图像
    cv::Mat frame;
    cv::VideoCapture capture(0);
    std::vector<uchar> data_encode;
    std::string str_encode;
    CVImageService::RequestVideoMessage request;
    
    if (capture.isOpened()) { //摄像头读取文件开关
        while (true) {
            Sleep(1000);
            capture >> frame;
            if (!frame.empty()) {
               //传输图像 
               cv::imencode(".png", frame, data_encode);
               str_encode.append(data_encode.begin(), data_encode.end());
               request.add_userdata(username);
               request.set_command("Video");
               request.set_videobuff(str_encode);
               stream->Write(request);

               std::cout << "send" << std::endl;
               request.Clear();
               str_encode.clear();
               data_encode.clear();
            }
            else {
                printf("error");
                break;
            }

            int c = cv::waitKey(50);
            if ((char)c == 27) {
                break;
            }
        }

    }



}

void CVImageClient::ImageProcess()
{
    std::string command;
    std::cout << "intput command" << std::endl;
    std::cin >> command;
    std::cout << "command is:" << command << std::endl;
    grpc::ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<CVImageService::ImageMessage, CVImageService::ImageMessage> > stream(
        m_stub->CVImageProcessFunction(&context));

    cv::Mat src= cv::imread("C:/Users/gl/Desktop/Temp/3.jpg"); //设置图像路径
    std::vector<uchar> data_encode;
    //直接编码
    if (!cv::imencode(".png", src, data_encode))
    {
        std::cout << "client imencode error" << std::endl;
        return;
    }
    std::string str_encode(data_encode.begin(), data_encode.end());
    std::cout << "encode size:" << data_encode.size() << ","<< str_encode.size()<<std::endl;
    //设置发送消息
    //std::thread writer([stream, command, str_encode]() {
        std::cout << "Client setPkg" << std::endl;
        CVImageService::ImageMessage* commandPkg = new CVImageService::ImageMessage;
        commandPkg->set_command(command);
        commandPkg->set_colum(0);
        commandPkg->set_row(0);
        commandPkg->set_encodebuff(str_encode);
        std::cout << "Client Write" << std::endl;
        if (!stream->Write(*commandPkg))
        {
            std::cout << "client write error" << std::endl;
            return;
        }
        stream->WritesDone();
        
        
        std::cout << "write over" << std::endl;
        commandPkg->Clear();
        if (commandPkg)
        {
            delete commandPkg;
        }
    //});


    CVImageService::ImageMessage imagedata;
    if (!stream->Read(&imagedata))
    {
        std::cout << "接收失败" << std::endl;
        //return;
    }
    cv::Mat tempmat;
    std::string strbuf = imagedata.encodebuff();
    std::vector<uchar> data(strbuf.begin(), strbuf.end());

    tempmat = cv::imdecode(data, 1);
    std::cout << "command:" << imagedata.command() << std::endl;
    if (tempmat.empty());
    {
        std::cout << "imdecode maybe error" << std::endl;
        //return;
    }

    ShowImage(tempmat);

}

