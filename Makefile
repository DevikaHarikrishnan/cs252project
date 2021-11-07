obj-m += simple.o
obj-m += hello.o
obj-m += readjiffies.o
obj-m += timeelapsed.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean