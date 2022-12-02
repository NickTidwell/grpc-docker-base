FROM grpc/cxx
WORKDIR /usr/src/app/
COPY Makefile /usr/src/app/
ADD test_message.proto /usr/src/app/
ADD ./client_dir /usr/src/app/

RUN make client
