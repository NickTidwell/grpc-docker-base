FROM grpc/cxx
WORKDIR /usr/src/app/

COPY Makefile /usr/src/app/
ADD test_message.proto /usr/src/app/
ADD ./service /usr/src/app/

RUN make server
