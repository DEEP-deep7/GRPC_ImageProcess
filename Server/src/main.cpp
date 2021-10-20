#include <grpc++/server_builder.h>
//#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include "CVImageServer.h"


int main()
{
    std::string server_address("0.0.0.0:50052");
    grpc::ServerBuilder builder;
    CVImageServer service;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}