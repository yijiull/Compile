# Compile
***

```
git clone https://github.com/yijiull/Compile.git  
cd Compile/build
cmake ..
make
```

## 实验一提取token
>实验一的测试数据在/Compile/build/test中，experiment1_test1_in.txt和experiment1_test2_in.txt
```
./main -token {file}   //file换成测试数据的文件名，注意路径
```

## 实验二生成中间代码
>实验二的测试数据在/Compile/build/test中，experiment2_test1_in.txt和experiment2_test2_in.txt
```
./main  {file}   //file换成测试数据的文件名，注意路径
```
> 另外附加的数据在/Compile/build/test/bug中，取消相应的注释就会报错


## 接口

在main.h中：
- void setSourceCode(std::string fileName);   //设置待编译的源文件fileName
- void getAllToken();  //实验一提取所有的token，输出到{fileName}.token中  
- void generateResult();  //实验二生成中间代码，输出到{fileName}.code中，另外符号表输出到{fileName}.symbal，语法树输出到{fileName}.tree  
- std::string getContent(std::string fileName); //从fileName文件中提取所有字符
- 所有的报错信息都输出到{fileName}.log中

可参考test.cpp。
