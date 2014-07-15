## googletest 配置

### 下载安装
<pre>
<code># 下载最新版本googletes, 当前是1.7.0
wget https://googletest.googlecode.com/file/gtest-1.6.0.zip
tar -vzxf gtest-1.7.0.zip

# 将googletest拷贝到/usr/local/gtest中
cd gtest-1.7.0
sudo mkdir /usr/local/gtest
cp include/gtest/ /usr/local/include/gtest/

# 将需要用到的主文件编译成中间文件
g++ -I ./include -I ./ -c ./src/gtest-all.cc

# 打包成库文件libgtest.a
ar -rv libgtest.a gtest-all.o</code>
</pre>

### 编译测试文件 
<pre>
<code># 以`tree/unit.test.tree.cc`为例来说明如何编译具体的测试文件
# 执行如下命令前，需要将libgtest.a拷贝到tree目录下，在测试文件中，需要包含gtest/gtest.h
g++ -g unit.test.tree.cc search.tree.cc libgtest.a -o unit.test.tree.out</code>
</pre>

