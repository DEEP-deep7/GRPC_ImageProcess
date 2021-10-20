protoc -I. --grpc_out=. --plugin=protoc-gen-grpc="F://GRPCCpp//build//Release//grpc_cpp_plugin.exe" ImageStream.proto
protoc --cpp_out=./ ImageStream.proto
::copy .\*.h ..\Server\include
::copy .\*.cc ..\Server\src
::copy .\*.h ..\Client\include
::copy .\*.cc ..\Client\src
pause
