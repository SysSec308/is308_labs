# is308_labs

## 准备环境

我们建议使用[Vmware](https://www.vmware.com/ch.html) or [VirtualBox](https://www.virtualbox.org/)，它可以运行在Windows、Linux或OSX系统上，用来运行我们的实验环境。

### 1. Linux环境所需工具

建议使用Ubuntu 17.10的镜像（或其他16.04之后版本），[ubuntu-17.10.1-desktop-amd64.iso](http://ftp.sjtu.edu.cn/ubuntu-cd/17.10.1/ubuntu-17.10.1-desktop-amd64.iso)

1. 编译器gcc
2. 调试工具gdb
3. [PEDA](https://github.com/longld/peda)（可选） - Python Exploit Development Assistance for GDB
> 相关资料：http://ropshell.com/peda/
4. [pwntools](https://github.com/Gallopsled/pwntools) - CTF framework and exploit development library

```sh
sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y install binutils nasm
sudo apt-get -y install gcc-multilib g++-multilib
sudo apt-get -y install libc6-dev-i386
sudo apt-get -y install git
sudo apt-get -y install libc6-dbg libc6-dbg:i386
sudo apt-get -y install nmap
sudo apt-get -y install python-pip libssl-dev
sudo apt-get -y install gdb
sudo pip install --upgrade pip
sudo pip install --upgrade capstone
sudo pip install --upgrade pwntools
sudo pip install ropgadget
git clone https://github.com/scwuaptx/peda.git ~/peda 
cp ~/peda/.inpurc ~/
git clone https://github.com/scwuaptx/Pwngdb.git
cp ~/Pwngdb/.gdbinit ~/
git clone https://github.com/JonathanSalwan/ROPgadget
```

### 2. Windows环境所需工具

建议使用Windows 7 32位以及上
1. 编程环境VS2010或以上
2. 调试工具[OllyDBG](http://www.ollydbg.de/odbg201.zip)
3. [IDA Pro](https://www.hex-rays.com/products/ida/support/download_freeware.shtml) - a static analysis tool
    * Shift + F12 – 查看字符串
    * X – 查看字符串引用

参考资料：






