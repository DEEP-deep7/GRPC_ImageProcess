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
cmake --build . --config Release
```

也可以使用cmake gui生成vs工程，然后编译。



### 注意事项

* 编译grpc时需要管理员权限
* 使用命令行生成grpc代码之后使用vs编译，如果有编译报错并且有c4819的警告，则需要将生成的代码文件转码另存为GB2312字符集



### 其它说明

* GRPC接口拓展简单，需要在proto文件中定义消息体和服务，然后再运行Proto目录下的proto.bat生成代码，在运行bat之前，要修改一下命令行中插件的路径。

  `protoc -I. --grpc_out=. --plugin=protoc-gen-grpc="grpc_cpp_plugin.exe路径"ImageStream.proto `

  `protoc --cpp_out=./ ImageStream.proto`

* 这个小案例主要使用了grpc的双向流来传输图像

* 目前已经实现了远程处理图像的功能，还有一个网络视频的功能正在开发，可以在源码中看到。

  