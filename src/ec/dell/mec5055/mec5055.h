/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _EC_DELL_MEC5055_H_
#define _EC_DELL_MEC5055_H_

#include <types.h>

#define MEC5055_LPC 		0xc
#define MEC5055_MAILBOX 	0x0
#define MEC5055_KBC 		0x1
#define MEC5055_ACPI_EC1	0x2
#define MEC5055_ACPI_EC2	0x3
#define MEC5055_ACPI_EC3	0x4
#define MEC5055_ACPI_EC4	0x5
#define MEC5055_ACPI_EC5	0x6
#define MEC5055_UART1		0x7
#define MEC5055_UART2		0x8
#define MEC5055_LEGACY_FAST_KB  0x9
#define MEC5055_EMBEDDED_FLASH	0xe
#define MEC5055_EMBEDDED_MEMORY	0x10

#define MEC5055_IRQ_BASE	0x40
#define MEC5055_DRQ_BASE	0x50

enum cb_err mec5055_ec_command_0(u8 *buf, u8 cmd, int argc);
enum cb_err mec5055_ec_command_1(u8 cmd, const u8 *cmd_buf, int argc, u8 *res_buf, int res_sz);
void mec5055_early_init(void);

#endif
