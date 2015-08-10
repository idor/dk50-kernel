#
# Makefile for the industrial I/O core.
#

obj-y += industrialio.o
industrialio-y := industrialio-core.o industrialio-event.o inkern.o
industrialio-y += industrialio-buffer.o
industrialio-y += industrialio-trigger.o
industrialio-$(CONFIG_IIO_BUFFER_CB) += buffer_cb.o

CFLAGS_industrialio-buffer.o += -DCONFIG_IIO_BUFFER -DCONFIG_IIO_TRIGGER -DCONFIG_IIO_KFIFO_BUF
CFLAGS_industrialio-trigger.o += -DCONFIG_IIO_BUFFER -DCONFIG_IIO_TRIGGER -DCONFIG_IIO_KFIFO_BUF

obj-$(CONFIG_IIO_TRIGGERED_BUFFER) += industrialio-triggered-buffer.o
obj-y += kfifo_buf.o

CFLAGS_kfifo_buf.o += -DCONFIG_IIO_KFIFO_BUF -DCONFIG_IIO_BUFFER -DCONFIG_IIO_TRIGGER

obj-y += accel/
obj-y += adc/
obj-y += amplifiers/
obj-y += common/
obj-y += dac/
obj-y += gyro/
obj-y += frequency/
obj-y += imu/
obj-y += light/
obj-y += magnetometer/
