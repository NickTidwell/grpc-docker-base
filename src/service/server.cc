#include <string>

#include <grpc++/grpc++.h>
#include "test_message.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using test_message::TestMessageService;
using test_message::TestMessageRequest;
using test_message::TestMessageResponse;



class TestServiceImplementation final : public TestMessageService::Service {
    Status sendRequest(
        ServerContext* context, 
        const TestMessageRequest* request, 
        TestMessageResponse* reply
    ) override {
        int a = request->a();
        int b = request->b();

        reply->set_result(a * b);

        return Status::OK;
    } 
};

void Run() {
    std::string address("grpc-service:5000");
    TestServiceImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}


int main(int argc, char** argv) {
    Run();

    return 0;
}
