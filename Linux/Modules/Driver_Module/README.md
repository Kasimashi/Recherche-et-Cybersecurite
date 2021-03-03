# Install kernel headers:

```

sudo apt update
sudo apt upgrade
sudo apt-get install raspberrypi-kernel-headers

```

# Command to test on device
```

insmod gpio_ctrl_driver.ko blink_period_ms=1000
rmmod insmod gpio_ctrl_driver
dmesg
modinfo gpio_ctrl_driver.ko
sudo cat /dev/gpio_ctrl_driver
echo 1200 | sudo tee /dev/gpio_ctrl_driver
modinfo gpio_ctrl_driver.ko

```
