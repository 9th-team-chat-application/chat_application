# chat_application

## 代码文件结构
1. 每一个分支仅仅允许有以下文件结构。实现文件统一放在src目录下，头文件统一放在include目录下。
2. 在include目录下必须有head.h头文件，在里面include所有需要的库文件，不允许include自己创建的头文件。
3. 在编写过程中，慎用extern关键字，严格注意thread的生命周期。
```
.
├── build
├── CMakeLists.txt
├── include
├── README.md
└── src
```

## cmake说明
第一次使用前需要安装
```
sudo apt update
sudo apt install cmake make
```
cmake具体使用：
```
cd build
cmake ..
make
./chat_application
```
如果出现错误，无论是编译还是运行，只要出现错误，必须将build目录下的所有文件删除。
更改完错误再次编译运行。
如果出现链接库等的错误找王占坤处理。
