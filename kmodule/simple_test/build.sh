#2018年08月17日15:14:13
#njl
#编译GPU 程序的脚本 直接运行就可以了
#经过验证这个程序是可以实现编译完成后把编译出来的二进制拷贝到板子上的
#前提是板子与主机通过以太网连接在同一个局域网中，并且板子的ip是192.168.1.2
export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-
export LINUX_S32V234_DIR=/home/hp/toolschain/gcc-linaro-aarch64-linux-gnu-4.9-2014.07_linux/bin
#export PATH=$PATH:/home/njl/S32V/gcc-linaro/bin
make clean
make -j4 

#scp Car3D.elf root@192.168.1.2:/opt/viv_samples/vdk

#scp $(pwd)/../src/*.frag root@192.168.1.2:/opt/viv_samples/vdk

#scp $(pwd)/../src/*.vert root@192.168.1.2:/opt/viv_samples/vdk

#scp -r $(pwd)/../src/Data root@192.168.1.2:/opt/viv_samples/vdk

