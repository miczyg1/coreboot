#include <string.h>
#include <arch/io.h>
#include <console/console.h>
#include <superio/smsc/sch5545/sch5545.h>
#include <superio/smsc/sch5545/sch5545_emi.h>

#include "sch5545_ec.h"

static uint8_t global_data[0x47];
static uint8_t buff_len;

static uint8_t send_mbox_msg_with_int(uint8_t mbox_message)
{
	uint8_t int_sts, int_cond;

	sch5545_emi_h2ec_mbox_write(mbox_message);

	do {
		int_sts = sch5545_emi_get_int_src_low();
		int_cond = int_sts & 0x71;
	} while (int_cond == 0);

	sch5545_emi_set_int_src_low(int_cond);

	if ((int_sts & 1) == 0)
		return 0;

	if (sch5545_emi_ec2h_mbox_read() == mbox_message)
		return 1;

	return 0;
}

static uint8_t ec_read_write_reg(uint8_t ldn, uint16_t reg, uint8_t *value,
				 uint8_t rw_bit)
{
	uint8_t int_mask_bckup, ret = 0;
	rw_bit &= 1;

	int_mask_bckup = sch5545_emi_get_int_mask_low();
	sch5545_emi_set_int_mask_low(0);

	sch5545_emi_ec_write16(0x8000, (ldn << 1) | 0x100 | rw_bit);
	if (rw_bit)
		sch5545_emi_ec_write32(0x8004, (reg << 16) | *value);
	else
		sch5545_emi_ec_write32(0x8004, reg << 16);

	ret = send_mbox_msg_with_int(1);
	if (ret && !rw_bit)
		*value = sch5545_emi_ec_read8(0x8004);
	else if (ret != 1 && rw_bit)
		printk(BIOS_WARNING, "EC mailbox returned unexpected value"
		       " when writing %02x to %04x\n", *value, reg);
	else if (ret != 1 && !rw_bit)
		printk(BIOS_WARNING, "EC mailbox returned unexpected value"
		       " when reading %04x \n", reg);

	sch5545_emi_set_int_mask_low(int_mask_bckup);

	return ret;
}

static void ec_send_sequence(uint8_t *buffer, uint8_t count)
{
	unsigned int i;
	uint16_t reg;
	uint8_t val;

	for(i = 0; i < count; i++) {
		reg = buffer[i*3] | (buffer[i*3 + 1] << 8);
		val = buffer[i*3 + 2];
		ec_read_write_reg(EC_HWM_LDN, reg, &val, WRITE_OP);
	}
}

static void ec_prepare_4_bytes(uint8_t *g_buffer, uint8_t *l_buffer)
{
	l_buffer[6] |= 0xc0;
	l_buffer[6] &= 0xf7;
	l_buffer[6] &= 0xf8;
	l_buffer[6] |= (g_buffer[6] & 7);
	l_buffer[6] &= 0xcf;
	l_buffer[6] |= ((g_buffer[6] >> 4) & 3) << 4;
	l_buffer[7] &= 0x80;
	l_buffer[7] |= 0x01;
	l_buffer[7] &= 0x7f;
	l_buffer[8] &= 0xe0;
	l_buffer[8] |= g_buffer[8] & 0x1f;
	l_buffer[8] &= 0xdf;
	l_buffer[8] &= 0xbf;
	l_buffer[8] &= 0x7f;
}

static void ec_prepare_and_send_12_type1(uint8_t *g_buffer, uint8_t *l_buffer)
{
	ec_prepare_4_bytes(g_buffer, l_buffer);
	l_buffer[9]  = g_buffer[9];
	l_buffer[10] = 0x05;

	ec_send_sequence(l_buffer, 12);
}

static void ec_prepare_and_send_12_type2(uint8_t *g_buffer, uint8_t *l_buffer)
{
	ec_prepare_4_bytes(g_buffer, l_buffer);
	l_buffer[9] &= 0xc0;
	l_buffer[9] &= 0x3f;
	l_buffer[10] = g_buffer[10];
	l_buffer[11] = 0x05;

	ec_send_sequence(l_buffer, 12);
}

static void ec_prepare_and_send_13(uint8_t *g_buffer, uint8_t *l_buffer)
{
	ec_prepare_4_bytes(g_buffer, l_buffer);
	l_buffer[9]  = 0x05;
	l_buffer[10] = 0x00;
	l_buffer[11] = 0x01;
	l_buffer[12] = 0x01;

	ec_send_sequence(l_buffer, 13);
}

static void ec_prepare_and_send_14(uint8_t *g_buffer, uint8_t *l_buffer)
{
	ec_prepare_4_bytes(g_buffer, l_buffer);
	l_buffer[9]  = 0x01;
	l_buffer[10] = 0x00;
	l_buffer[11] = 0x00;
	ec_read_write_reg(EC_HWM_LDN, 0x059e, &l_buffer[12], READ_OP);
	l_buffer[13] = 0x00;

	ec_send_sequence(l_buffer, 14);
}

static void ec_prepare_and_send_16_or_11(uint8_t *g_buffer, uint8_t *l_buffer)
{
	ec_prepare_4_bytes(g_buffer, l_buffer);

	if (g_buffer[12] == 0 || g_buffer[12] == 1 || g_buffer[12] == 0xff) {
		l_buffer[9]  = 0x04;
		l_buffer[10] = 0x00;
		l_buffer[11] = 0x01;
		l_buffer[12] = 0xf1;
		l_buffer[13] = 0xf0;
		l_buffer[14] = 0xff;
		l_buffer[15] = 0x00;
		ec_send_sequence(l_buffer, 16);
		return;
	}

	l_buffer[9]  = 0x04;
	l_buffer[10] = 0x05;

	ec_send_sequence(l_buffer, 11);
}


static void ec_prepare_and_send_17(uint8_t *g_buffer, uint8_t *l_buffer)
{
	ec_prepare_4_bytes(g_buffer, l_buffer);
	l_buffer[9] &= 0xc0;
	l_buffer[9] &= 0x3f;
	l_buffer[10] = 0x03;
	l_buffer[11] = 0x00;
	l_buffer[12] = 0x01;
	l_buffer[13] = 0xf1;
	l_buffer[14] = 0xf0;
	l_buffer[15] = 0xf0;
	l_buffer[16] = 0x00;

	ec_send_sequence(l_buffer, 17);
}

static void ec_prepare_and_send_20(uint8_t *g_buffer, uint8_t *l_buffer)
{
	ec_prepare_4_bytes(g_buffer, l_buffer);
	l_buffer[9] &= 0xc0;
	l_buffer[9] &= 0x3f;
	l_buffer[10] = 0x04;
	l_buffer[11] = 0x00;
	l_buffer[12] = 0x09;
	l_buffer[13] = 0x00;
	l_buffer[14] = 0x00;
	l_buffer[15] = 0x00;
	l_buffer[16] = 0x00;
	l_buffer[17] = 0x00;
	l_buffer[18] = 0x00;
	l_buffer[19] = 0x00;

	ec_send_sequence(l_buffer, 20);
}

static void ec_prepare_data(uint8_t *g_buffer, uint8_t *l_buffer)
{
	if (g_buffer[0] != 0x0f)
		return;

	if ((g_buffer[7] & 0x7f) != 0) {
		ec_prepare_and_send_12_type1(g_buffer, l_buffer);
		return;
	}

	if ((g_buffer[8] >> 7) == 1) {
		if (g_buffer[9] > 0xf) {
			printk(BIOS_WARNING, "%s: Unsupported type %x\n",
				__func__, g_buffer[9]);
			return;
		}

		switch (g_buffer[9]) {
		case 1:
		case 2:
			ec_prepare_and_send_14(g_buffer, l_buffer);
			break;
		case 4:
			ec_prepare_and_send_16_or_11(g_buffer, l_buffer);
			break;
		case 5:
			ec_prepare_and_send_13(g_buffer, l_buffer);
			break;
		default:
			ec_prepare_and_send_12_type1(g_buffer, l_buffer);
			break;
		}
	}
}

static void ec_prepare_data2(uint8_t *g_buffer, uint8_t *l_buffer)
{
	if ((g_buffer[7] & 0x7f) != 1)
		return;

	if ((g_buffer[9] & 0x3f) != 0) {
		ec_prepare_and_send_12_type2(g_buffer, l_buffer);
		return;
	}

	if ((g_buffer[8] >> 7) == 1) {
		if(g_buffer[10] > 5) {
			printk(BIOS_WARNING, "%s: Unsupported type %x\n",
				__func__, g_buffer[10]);
			return;
		}
		switch (g_buffer[10]) {
		case 4:
			ec_prepare_and_send_20(g_buffer, l_buffer);
			break;
		case 3:
		case 5:
			ec_prepare_and_send_17(g_buffer, l_buffer);
			break;
		default:
			ec_prepare_and_send_12_type2(g_buffer, l_buffer);
			break;
		}
	}
}

static uint8_t send_mbox_msg_simple(uint8_t mbox_message)
{
	uint8_t int_sts;

	sch5545_emi_h2ec_mbox_write(mbox_message);

	do {
		int_sts = sch5545_emi_get_int_src_low();
		if ((int_sts & 70) != 0)
			return 0;
	} while ((int_sts & 1) == 0);

	if (sch5545_emi_ec2h_mbox_read() == mbox_message)
		return 1;

	return 0;
}

static int sch5545_multiple_read(uint32_t *buf, uint8_t *bytes_read)
{
	uint8_t to_read, i;

	uint32_t status = sch5545_emi_ec_read32(0x8080);
	to_read = (status >> 24) & 0xff;

	if ((status & 0xff) != 0x0c) {
		printk(BIOS_WARNING, "Wrong LDN detected (%x), expected 0xc\n",
			status & 0xff);
		return -1;
	}

	if (*bytes_read >= to_read) {
		for (i = 0; i <= to_read/4; i++) {
			*(buf + i) = sch5545_emi_ec_read32(0x8084 + i*4);
			printk(BIOS_WARNING, "%s: read value %08x\n", __func__,
				*(buf + i));
		}
	} else {
		printk(BIOS_WARNING, "More bytes to read (%x) than"
			" expected (%x)\n", to_read, *bytes_read);
		return -1;
	}

	*bytes_read = to_read;

	if (send_mbox_msg_simple(0x05))
		return 0;

	printk(BIOS_WARNING, "%s: Mailbox returned unexpected value\n",
		__func__);
	return -1;

}

void sch5545_ec_handle_serirq_smi(void)
{
	uint8_t local_data[0x47] = { 0 };
	uint8_t val;

	sch5545_emi_init(0x2e);

	val = sch5545_emi_get_int_src_low();
	if (val != 0x08) {
		printk(BIOS_INFO, "EC INT SRC should be 0x08, is %02x\n", val);
		return;
	}

	val = 0x47;
	sch5545_multiple_read((uint32_t *)&global_data[3], &val);
	buff_len = val + 3;
	global_data[0] = 0x0f;
	global_data[1] = buff_len;
	ec_read_write_reg(EC_HWM_LDN, 0x059f, &val, READ_OP);
	global_data[2] = val;

	if ((global_data[7] & 0x7f) == 0)
		ec_prepare_data(global_data, local_data);
	else if ((global_data[7] & 0x7f) == 1)
		ec_prepare_data2(global_data, local_data);

	outb(1, SCH5545_RUNTIME_REG_BASE + SCH5545_RR_SMI_STS);
}
