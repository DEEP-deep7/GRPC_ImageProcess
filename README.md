# GRPC_ImageProcess

本案例使用grpc实现了客户端发送图片，服务端处理并返回图片的功能。

## 依赖：

[cmake](https://www.baidu.com/link?url=dHrT2QG73Ijl7lXi2pxoZifXPy6FOju5jtPQ5phD-CO&wd=&eqid=dfe39b890006bdc200000004617013b9)

[Opencv](https://opencv.org/)

[grpc](https://github.com/grpc/grpc)

[protobuf](https://github.com/protocolbuffers/protobuf)：建议在源码编译grpc的时候可以选择编译生成protobuf，这样就可以不用额外拉取protobuf代码编译。

## build

windows vs2015以上

```cmake
mkdir ../build
cd ../build
cmake ../GRPC_ImageProcess -G "Visual Studio 14 2015" -D Protobuf_DIR="..." -D OpenCV_DIR="..." -D gRPC_DIR="..."
cmake --build .
```

