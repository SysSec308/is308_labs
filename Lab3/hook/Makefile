strcmp-target: strcmp-target.c strcmp-hijack.so
	gcc -o strcmp-target strcmp-target.c

strcmp-hijack.so: strcmp-hijack.c
	gcc -fPIC -shared -o strcmp-hijack.so strcmp-hijack.c -ldl
