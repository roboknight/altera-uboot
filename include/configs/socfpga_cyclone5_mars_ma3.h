/*
 * Copyright (C) 2014 Marek Vasut <marex@denx.de>
 * Copyright (C) 2015 Antmicro Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIG_SOCFPGA_CYCLONE5_MARS_MA3_H__
#define __CONFIG_SOCFPGA_CYCLONE5_MARS_MA3_H__

#include <asm/arch/socfpga_base_addrs.h>
#include <configs/socfpga_cyclone5_mercury_sa1.h>

#define CONFIG_PREBOOT

/* Set PHY_ADDR to use Micrel KSZ PHY only. */
#define CONFIG_PHY_ADDR 3

#ifdef CONFIG_EXTRA_ENV_SETTINGS
#undef CONFIG_EXTRA_ENV_SETTINGS
#endif
#define CONFIG_EXTRA_ENV_SETTINGS \
	"envfile=uEnv.txt\0" \
	"loadbootenv_addr=0x2000000\0" \
	"loadbootenv=load mmc 0 ${loadbootenv_addr} ${envfile}\0" \
	"importbootenv=echo Importing environment from SD ...; " \
	"env import -t ${loadbootenv_addr} $filesize\0" \
	"sd_uenvtxt_exists=test -e mmc 0 ${envfile}\0" \
	"preboot=mmc rescan; if env run sd_uenvtxt_exists; " \
		"then if env run loadbootenv; "\
			"then env run importbootenv; " \
			"fi; " \
		"fi;\0" \
	"altera_mux_sd_memory=if test \"${sd_target}\" = emmc; " \
		"then echo \"Switching SD interface to eMMC\"; " \
			"run altera_enable_emmc; " \
		"else echo \"Switching SD interface to MMC\";" \
			"run altera_enable_mmc; " \
		"fi;\0" \
	"altera_enable_mmc=gpio set 53; mmc rescan;\0" \
	"altera_enable_emmc=gpio clear 53; mmc rescan;\0" \
	"loadaddr=0x200000\0"                       \
	"ipaddr=192.168.1.113\0"                    \
	"serverip=192.168.1.188\0"                  \
	"serverpath=/srv/nfs/rootfs\0"               \
	"netmask=255.255.255.0\0"                   \
						\
	"preloader_image=preloader-mkpimage.bin\0"  \
	"bitstream_image=fpga.rbf.img\0"	    \
	"kernel_image=uImage\0"                     \
	"rootfs_image=rootfs.jffs2\0"               \
	"uramdisk_image=uramdisk\0"                 \
	"devicetree_image=devicetree.dtb\0"         \
	"bootscript_image=uboot.scr\0"              \
	"uboot_image=u-boot.img\0"		    \
						\
	"preloader_loadaddr=0x2B00000\0"	\
	"bitstream_loadaddr=0x3600000\0"	\
	"uboot_loadaddr=0x2C00000\0"		\
	"kernel_loadaddr=0x3000000\0"               \
	"devicetree_loadaddr=0x2A00000\0"           \
	"rootfs_loadaddr=0x4000000\0"               \
	"ramdisk_loadaddr=0x4000000\0"               \
	"bootscript_loadaddr=0x1000000\0"           \
	"initrd_high=0x10000000\0" \
						\
	"preloader_size="   __stringify(QSPI_PRELOADER_SIZE) "\0"\
	"rootfs_size="     __stringify(QSPI_ROOTFS_SIZE) "\0"\
	"ramdisk_size="     __stringify(QSPI_RAMDISK_SIZE) "\0"\
	"kernel_size="     __stringify(QSPI_LINUX_SIZE)  "\0"\
	"devicetree_size=" __stringify(QSPI_DTB_SIZE)    "\0"\
	"bootscript_size=" __stringify(QSPI_BOOTSCRIPT_SIZE)   "\0"\
	"bitstream_size="   __stringify(QSPI_BITSTREAM_SIZE)    "\0"\
								\
	"qspi_kernel_offset="     __stringify(QSPI_LINUX_OFFSET) "\0"\
	"qspi_rootfs_offset="     __stringify(QSPI_ROOTFS_OFFSET)"\0"\
	"qspi_ramdisk_offset="     __stringify(QSPI_ROOTFS_OFFSET)"\0"\
	"qspi_devicetree_offset=" __stringify(QSPI_DTB_OFFSET)   "\0"\
	"qspi_bootscript_offset=" __stringify(QSPI_BOOTSCRIPT_OFFSET)  "\0"\
	"qspi_preloader_offset="  __stringify(QSPI_PRELOADER_OFFSET)   "\0"\
	"qspi_uboot_offset="      __stringify(QSPI_UBOOT_OFFSET)       "\0"\
	"qspi_uboot_erase_offset="  __stringify(QSPI_UBOOT_ERASE_ADDR)   "\0"\
	"qspi_uboot_erase_size="  __stringify(QSPI_UBOOT_ERASE_SIZE)   "\0"\
	"qspi_bitstream_offset="  __stringify(QSPI_BITSTREAM_OFFSET)   "\0"\
						 \
	"mmcargs=setenv bootargs console=ttyS0,115200 root=/dev/mmcblk0p3 rw rootwait\0"\
	"usbargs=setenv bootargs console=ttyS0,115200 root=/dev/sda2 rw rootwait\0"\
	"qspiargs=setenv bootargs console=ttyS0,115200 root=/dev/mtdblock1 rootfstype=jffs2 rw rootwait\0"\
	"nfsargs=setenv bootargs console=ttyS0,115200 root=/dev/nfs nfsroot=${serverip}:${serverpath},v3 rw rootwait ip=dhcp\0"\
	"qspiargs=setenv bootargs console=ttyS0,115200 root=/dev/mtdblock1 rootfstype=jffs2 rw rootwait\0"\
	"qspiramdiskargs=setenv bootargs console=ttyS0,115200 earlyprintk rw root=/dev/ram\0"\
	"def_args=console=ttyS0,115200 rw earlyprintk\0"\
	"ramdisk_args=setenv bootargs ${def_args} root=/dev/ram\0"\
	"qspiboot=echo Bootinq on QSPI Flash ...; " \
		"bridge enable && "	                \
		"sf probe && "                          \
		"sf read ${bootscript_loadaddr} ${qspi_bootscript_offset} ${bootscript_size} && "\
		"source ${bootscript_loadaddr}\0"       \
                                                \
	"mmcboot=echo Booting on SD Card ...; "      \
		"bridge enable && "                     \
		"mmc rescan && "                        \
		"load mmc 0 ${bootscript_loadaddr} ${bootscript_image} && "\
		"source ${bootscript_loadaddr}\0"       \
                                                \
	"usbboot=echo Booting on USB ...; "     \
		"bridge enable && "		\
		"usb start && "			\
		"load usb 0 ${bootscript_loadaddr} ${bootscript_image} && " \
		"source ${bootscript_loadaddr} \0"\
                                                \
    "netboot=echo Booting from TFTP/NFS ...; "  \
		"bridge enable && "             \
        "tftpboot ${bootscript_loadaddr} ${bootscript_image} && "\
        "source ${bootscript_loadaddr}\0"       \
                                                \
	"modeboot=setexpr.l bootsel *0xFFD08014 \\\\& 0x7;" \
		"if test ${bootsel} -eq 4 || test ${bootsel} -eq 5;"\
		"then;echo Booting from MMC ...;"\
		"run mmcboot;"\
		"fi;"\
		"if test ${bootsel} -eq 6 || test ${bootsel} -eq 7;"\
		"then;echo Booting from QSPI ...;"\
		"run qspiboot;"\
		"fi\0"

#endif	/* __CONFIG_SOCFPGA_CYCLONE5_MARS_MA3_H__ */