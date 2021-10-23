protoc -I. --grpc_out=. --plugin=protoc-gen-grpc="C:\Program Files (x86)\grpc\bin\grpc_cpp_plugin.exe" ImageStream.proto
protoc --cpp_out=./ ImageStream.proto
::copy .\*.h ..\Server\include
::copy .\*.cc ..\Server\src
::copy .\*.h ..\Client\include
::copy .\*.cc ..\Client\src
pause
