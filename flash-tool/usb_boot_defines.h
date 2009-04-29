/*
 * "Ingenic flash tool" - flash the Ingenic CPU via USB
 *
 * (C) Copyright 2009
 * Author: Marek Lindner <lindner_marek@yahoo.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA
 */

#ifndef __JZ4740_USBDEFINES__H_
#define __JZ4740_USBDEFINES__H_

/* #define dprintf(x...) printf(x) */
#define SDRAM_SIZE ( 16 * 1024 * 1024 )
#define CODE_SIZE  ( 4 * 1024 * 1024 )
/* #define START_ADDR ( 0x80000000 + SDRAM_SIZE - CODE_SIZE ) */

#define MAX_COMMAND_LENGTH 100
#define COMMAND_NUM 31
#define NAND_MAX_BLK_NUM  10000000	/* ((Hand.nand_pn / Hand.nand_ppb) + 1) */
#define NAND_MAX_PAGE_NUM 1073740824	/*Hand.nand_pn */
#define NAND_SECTION_NUM 23
#define MAX_TRANSFER_SIZE 0x100000
#define MAX_LOAD_SIZE 0x3000
#define NAND_MAX_BYTE_NUM (Hand.nand_pn * Hand.nand_ps)
#define	IOCTL_INBUF_SIZE	512
#define	IOCTL_OUTBUF_SIZE	512
#define MAX_DEV_NUM 16 

enum CPUTYPE {
	JZ4740,
	JZ4750,
};

enum USB_Boot_State {
	DISCONNECT,
	CONNECT,
	BOOT,
	UNBOOT
};

enum OPTION {
	OOB_ECC,
	OOB_NO_ECC,
	NO_OOB,
};

enum NOR_OPS_TYPE {
	NOR_INIT = 0,
	NOR_QUERY,
	NOR_WRITE,
	NOR_ERASE_CHIP,
	NOR_ERASE_SECTOR
};

enum NOR_FLASH_TYPE
{
	NOR_AM29 = 0,
	NOR_SST28,
	NOR_SST39x16,
	NOR_SST39x8
};

enum NAND_OPS_TYPE {
	NAND_QUERY = 0,
	NAND_INIT,
	NAND_MARK_BAD,
	NAND_READ_OOB,
	NAND_READ_RAW,
	NAND_ERASE,
	NAND_READ,
	NAND_PROGRAM,
	NAND_READ_TO_RAM
};

enum SDRAM_OPS_TYPE {
	SDRAM_LOAD,
};

enum DATA_STRUCTURE_OB {
	DS_flash_info ,
	DS_hand
};

struct fw_args_t {
	/* CPU ID */
	unsigned int  cpu_id;

	/* PLL args */
	unsigned char ext_clk;
	unsigned char cpu_speed;
	unsigned char phm_div;
	unsigned char use_uart;
	unsigned int  boudrate;

	/* SDRAM args */
	unsigned char bus_width;
	unsigned char bank_num;
	unsigned char row_addr;
	unsigned char col_addr;
	unsigned char is_mobile;
	unsigned char is_busshare;

	/* debug args */
	unsigned char debug_ops;
	unsigned char pin_num;
	unsigned int  start;
	unsigned int  size;

	/* for align */
	/* unsigned char align1; */
	/* unsigned char align2; */
} __attribute__((packed));

struct  hand_t {

	/* nand flash info */
	int pt;             	/* cpu type */
	int nand_bw;		/* bus width */
	int nand_rc;		/* row cycle */
	int nand_ps;		/* page size */
	int nand_ppb;		/* page number per block */
	int nand_force_erase;
	int nand_pn;		/* page number in total */
	int nand_os;		/* oob size */
	int nand_eccpos;
	int nand_bbpage;
	int nand_bbpos;
	int nand_plane;
	int nand_bchbit;
	int nand_wppin;
	int nand_bpc;		/* block number per chip */

	struct fw_args_t fw_args;
} __attribute__((packed));

struct nand_in_t {
	unsigned char dev;
	unsigned char max_chip;
	unsigned char *buf;
	unsigned char *cs_map;
	unsigned int start;
	unsigned int length;
	unsigned int option;

	int (* check) (unsigned char *,unsigned char *,unsigned int);
};

struct nand_out_t {
	unsigned char *status;
};

struct sdram_in_t {
	unsigned char dev;
	unsigned char *buf;
	unsigned int start;
	unsigned int length;
	unsigned int option;
};

#endif	/* __JZ4740_USBDEFINES__H_ */