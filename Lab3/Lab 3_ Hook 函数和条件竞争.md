# Lab 3: Hook 函数和条件竞争
### Hook 函数
实验环境：Ubuntu 17.10 amd64

实验工具：GCC、GDB

实验目的：熟悉Linux环境下的Hook函数

1. strcmp-target.c

```c
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s <password>\n", argv[0]);
        return 1;
    }

    if( strcmp(argv[1], "test") )
    {
        printf("Incorrect password\n");
    }
    else
    {
        printf("Correct password\n");
    }
    return 0;
}
```
2. strcmp-hijack.c，Hook函数strcmp使得其一定返回0

```c
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int(*STRCMP)(const char*, const char*);

int strcmp(const char *s1, const char *s2)
{
    static void *handle = NULL;
    static STRCMP old_strcmp = NULL;

    if( !handle )
    {
        handle = dlopen("libc.so.6", RTLD_LAZY);
        old_strcmp = (STRCMP)dlsym(handle, "strcmp");
    }
    printf("hack function invoked. s1=<%s> s2=<%s>\n", s1, s2);
    return old_strcmp(s1, s2);
}
```

3. 编译代码

```sh
make
```

4. 运行并观察实验结果

```sh
./strcmp-target redbull
LD_PRELOAD="./strcmp-hijack.so" ./strcmp-target redbull
```
Q1：Linux下动态链接与静态链接的区别？

Q2：LD_PRELOAD的作用？

Q3：试分析延时绑定(Lazy Bind)的过程（Tips，_dl_runtime_resolve）

Q4（选做）：你还有什么方式可以达到Hook函数的目的？


### Race Condition
实验环境：Ubuntu 17.10 amd64

实验工具：GCC、GDB

实验目的：本实验的目的是通过实验了解条件竞争产生的原因以及如何利用存在漏洞的特权程序获得root权限。

1. `vul_program.c`为存在漏洞的目标程序

   ```c
   #include<stdio.h>
   #include<unistd.h>

   #define DELAY 10000

   int main()
   {
       char * fn = "/tmp/XYZ";
       char buffer[60];
       FILE *fp;
       long int i;

       /* get user input */
       scanf("%50s", buffer );
       
       if(!access(fn, W_OK)){
           /* simulating delay */
           for (i=0; i < DELAY; i++){
               int a = i^2;
           }
           
           fp = fopen(fn, "a+");
           fwrite("\n", sizeof(char), 1, fp);
           fwrite(buffer, sizeof(char), strlen(buffer), fp);
           fclose(fp);
       }
       else printf("No permission \n");
   }
   ```

2. 编译存在漏洞程序的代码设置相应权限

   ```shell
   gcc vul_program.c -o vul_program
   sudo chown root:root vul_program
   sudo chmod +s vul_program
   echo 0 | sudo tee /proc/sys/fs/protected_symlinks
   ```

3. `attack.c`为攻击代码，通过gcc直接编译成二进制文件，不需要修改任何权限

   > 注意：在编译之前需要把attack.c文件中root_file和tmp_file路径修改为当前工程目录所在位置

   ```shell
   gcc attack.c -o attack
   ```

4. 分析两个sh脚本的功能，通过运行如下命令观察实验结果

   ```shell
   ./attacker&
   ./check.sh
   ```

Q1：攻击成功的结果是怎样的，举例说明在其他场景下可以造成什么样的危害

Q2：在2中的`echo 0 | sudo tee /proc/sys/fs/protected_symlinks`命令的作用是什么

Q3：分析`vul_program.c`程序逻辑以及为什么会存在漏洞

Q3（选做）：讨论如何避免上述实验中的漏洞
