/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/io.h>
#include <console/console.h>
#include "mec5055.h"

static const u16 EC_CTRL = 0x910;
static const u16 EC_DATA = 0x911;

static void wait_ec(void)
{
	u8 v;
	do {
		outb(0, EC_CTRL);
		v = inb(EC_DATA);
	} while (v != 0);
}

static enum cb_err read_ec_regs(u8 start, u8 *sdata, u8 count)
{
	if (start >= 0x20 || start + count > 0x20) {
		printk(BIOS_ERR, "%s: Invalid start or count argument.\n", __func__);
		return CB_ERR_ARG;
	}

	while (count--) {
		outb(start + 0x10, EC_CTRL);
		*sdata = inb(EC_DATA);
		sdata++;
		start++;
	}

	return CB_SUCCESS;
}

static enum cb_err write_ec_regs(u8 start, const u8 *sdata, u8 count)
{
	if (start >= 0x20 || start + count > 0x20) {
		printk(BIOS_ERR, "%s: Invalid start or count argument.\n", __func__);
		return CB_ERR_ARG;
	}

	while (count--) {
		outb(start + 0x10, EC_CTRL);
		outb(*sdata, EC_DATA);
		sdata++;
		start++;
	}

	return CB_SUCCESS;
}

/*
 * Steps to communicate with the EC:
 * 1. send command:
 *   - write arguments to EC[2:]
 *   - send 0 to CTRL then cmd to DATA
 * 2. wait for EC
 * 3. receive result: result may starts at EC[0] or EC[1]
 */

/* send command to EC and wait, command at cmd[0], args in cmd[2:] */
static enum cb_err ec_send_command(const u8 *cmd, int argc)
{
	int result = CB_SUCCESS;

	if (argc > 0) {
		if (argc > 0x1e) {
			printk(BIOS_ERR, "%s: argc too big.\n", __func__);
			result = CB_ERR_ARG;
		} else {
			result = write_ec_regs(2, cmd + 2, argc);
		}
	}

	outb(0, EC_CTRL);
	outb(cmd[0], EC_DATA);
	wait_ec();
	return result;
}

/* receive result from EC[0:] */
enum cb_err mec5055_ec_command_0(u8 *buf, u8 cmd, int argc)
{
	buf[0] = cmd;
	enum cb_err res = ec_send_command(buf, argc);
	if (res != CB_SUCCESS) {
		printk(BIOS_ERR, "error: %s returns %d.\n", __func__, res);
		return res;
	}

	return read_ec_regs(0, buf, 0x10);
}

/* receive result from EC[1:] */
enum cb_err mec5055_ec_command_1(u8 cmd, const u8 *cmd_buf, int argc, u8 *res_buf, int res_size)
{
	if (argc >= 0x1e)
		argc = 0x1e;

	if (res_size >= 0x1f)
		res_size = 0x1f;

	enum cb_err res = write_ec_regs(2, cmd_buf, argc);
	if (res != CB_SUCCESS) {
		printk(BIOS_ERR, "error: %s returns %d.\n", __func__, res);
		return res;
	}

	outb(0, EC_CTRL);
	outb(cmd, EC_DATA);
	wait_ec();

	return read_ec_regs(1, res_buf, res_size);
}

void mec5055_early_init(void)
{
	u8 buf[32], c;

	mec5055_ec_command_0(buf, 0xc2, 0);
	mec5055_ec_command_1(0xab, NULL, 0, &c, 1);
}
