#include <string>

#include <grpc++/grpc++.h>
#include "test_message.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using test_message::TestMessageService;
using test_message::TestMessageRequest;
using test_message::TestMessageResponse;


class TestClient {
    public:
        TestClient(std::shared_ptr<Channel> channel) : stub_(TestMessageService::NewStub(channel)) {}

    int sendRequest(int a, int b) {
        TestMessageRequest request;

        request.set_a(a);
        request.set_b(b);

        TestMessageResponse reply;

        ClientContext context;

        Status status = stub_->sendRequest(&context, request, &reply);

        if(status.ok()){
            return reply.result();
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return -1;
        }
    }

    private:
        std::unique_ptr<TestMessageService::Stub> stub_;
};

void Run() {
    std::string address("grpc-service:5000");
    TestClient client(
        grpc::CreateChannel(
            address, 
            grpc::InsecureChannelCredentials()
        )
    );

    int response;


    int request_num = 1;
    for(request_num; request_num < 10; request_num++)
    {
        int a = rand() % 100 +1;
        int b = rand() % 100 +1;

        response = client.sendRequest(a, b);
        std::cout << "Answer received: " << a << " * " << b << " = " << response << std::endl;
    }

}

int main(int argc, char* argv[]){
    Run();

    return 0;
}