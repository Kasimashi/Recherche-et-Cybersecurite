# Linux-Kernel-Basic-Template
Implementation of a new module in Linux Kernel Template

Installation of the module :
```
sudo insmod linux-module.ko //load the module
sudo rmmod linux-module //unload the module


sudo mknod linux-module c 508 0
cat /dev/linux-module
```

## In order to see Kernel log


type :

```
dmesg
```

or 

```
tail -f /var/log/kern.log
```
