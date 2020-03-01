/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 * Copyright (C) 2014 Vladimir Serbinenko
 * Copyright (C) 2019-2020 3mdeb Embedded Systems Consulting
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <timestamp.h>
#include <arch/acpi.h>
#include <arch/beep.h>
#include <arch/byteorder.h>
#include <arch/cpu.h>
#include <arch/io.h>
#include <device/pci_def.h>
#include <device/pci_ops.h>
#include <device/pnp_def.h>
#include <device/pnp_ops.h>
#include <cpu/x86/lapic.h>
#include <console/console.h>
#include <northbridge/intel/sandybridge/sandybridge.h>
#include <northbridge/intel/sandybridge/raminit_native.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <southbridge/intel/common/gpio.h>
#include <cpu/x86/msr.h>
#include <superio/smsc/sch5545/sch5545.h>
#include <superio/smsc/sch5545/sch5545_emi.h>

#include "sch5545_ec.h"

void pch_enable_lpc(void)
{
	pci_write_config16(PCI_DEV(0, 0x1f, 0), 0x82, 0x3c01);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0x84, 0x007c0a01);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0x88, 0x007c0901);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0x8c, 0x003c07e1);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0x90, 0x001c0901);
}

void mainboard_rcba_config(void)
{	
}

const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 6, 0 },
	{ 1, 6, 0 },
	{ 1, 1, 1 },
	{ 1, 1, 1 },
	{ 1, 1, 2 },
	{ 1, 1, 2 },
	{ 1, 6, 3 },
	{ 1, 6, 3 },
	{ 1, 6, 4 },
	{ 1, 6, 4 },
	{ 1, 6, 5 },
	{ 1, 1, 5 },
	{ 1, 1, 6 },
	{ 1, 6, 6 },
};

static void sch5545_enter_conf_state(pnp_devfn_t dev)
{
	unsigned port = dev >> 8;
	outb(0x55, port);
}

static void sch5545_exit_conf_state(pnp_devfn_t dev)
{
	unsigned port = dev >> 8;
	outb(0xaa, port);
}

void mainboard_early_init(int s3resume)
{
	pnp_devfn_t dev;
	uint8_t val;
	uint16_t ec_fw_version;

	dev = PNP_DEV(0x2e, SCH5545_LDN_LPC_IF);

	sch5545_enter_conf_state(dev);
	pnp_set_logical_device(dev);

	for (val = 0x40; val < 0x84; val++)
		printk(BIOS_DEBUG, "SIO %02x: %02x\n", val,
					pnp_read_config(dev, val));

	dev = PNP_DEV(0x2e, SCH5545_LDN_UART1);
	printk(BIOS_DEBUG, "SIO %02x: %02x\n", 0x30,
					pnp_read_config(dev, 0x30));
					
	printk(BIOS_DEBUG, "Dev_dis %02x: %02x\n", val,
					inb(SCH5545_RUNTIME_REG_BASE + SCH5545_RR_DEV_DISABLE));
	sch5545_exit_conf_state(dev);

	sch5545_emi_init(0x2e);
	if (sch5545_emi_get_int_mask_high())
		printk(BIOS_INFO, "EC interrupt mask MSB is not 0\n");

	sch5545_emi_disable_interrupts();
	sch5545_ec_fan_spin_up();

	ec_fw_version = sch5545_get_ec_fw_version();

	if (ec_fw_version == 0x0000) {
		printk(BIOS_INFO, "SCH5545 EC is not functional, probably due"
				  " to power failure\n");
		printk(BIOS_INFO, "Uploading EC firmware to SCH5545\n");

		sch5545_update_ec_firmware();
		ec_fw_version = sch5545_get_ec_fw_version();

		if (ec_fw_version != 0x0318) {
			printk(BIOS_ERR, "EC firmware update failed!\n");
			printk(BIOS_ERR, "The fans will keep running at"
					 " maximum speed\n");
		} else {
			printk(BIOS_INFO, "EC firmware update success\n");
		}
	}

	sch5545_ec_finalize();

	printk(BIOS_DEBUG, "EC init complete.\n");

	dev = PNP_DEV(0x2e, SCH5545_LDN_LPC_IF);

	sch5545_enter_conf_state(dev);
	pnp_set_logical_device(dev);

	for (val = 0x40; val < 0x84; val++)
		printk(BIOS_DEBUG, "SIO %02x: %02x\n", val,
					pnp_read_config(dev, val));

	dev = PNP_DEV(0x2e, SCH5545_LDN_UART1);
	printk(BIOS_DEBUG, "SIO %02x: %02x\n", 0x30,
					pnp_read_config(dev, 0x30));
					
	printk(BIOS_DEBUG, "Dev_dis %02x: %02x\n", val,
					inb(SCH5545_RUNTIME_REG_BASE + SCH5545_RR_DEV_DISABLE));
	sch5545_exit_conf_state(dev);

	sch5545_enable_uart(0x2e, 0);
	
	dev = PNP_DEV(0x2e, SCH5545_LDN_LPC_IF);

	sch5545_enter_conf_state(dev);
	pnp_set_logical_device(dev);

	for (val = 0x40; val < 0x84; val++)
		printk(BIOS_DEBUG, "SIO %02x: %02x\n", val,
					pnp_read_config(dev, val));

	dev = PNP_DEV(0x2e, SCH5545_LDN_UART1);
	printk(BIOS_DEBUG, "SIO %02x: %02x\n", 0x30,
					pnp_read_config(dev, 0x30));
					
	printk(BIOS_DEBUG, "Dev_dis %02x: %02x\n", val,
					inb(SCH5545_RUNTIME_REG_BASE + SCH5545_RR_DEV_DISABLE));
	sch5545_exit_conf_state(dev);
}



void mainboard_config_superio(void)
{
	// return;

	// pnp_devfn_t dev;
	// uint8_t val;

	sch5545_early_init(0x2e);
	sch5545_emi_disable_interrupts();
	sch5545_enable_uart(0x2e, 0);

	// dev = PNP_DEV(0x2e, SCH5545_LDN_LPC_IF);

	// sch5545_enter_conf_state(dev);
	// pnp_set_logical_device(dev);

	// /* Setup other registers as in official firmware.
	//  * We do it here, because this SIO breaks our device model.
	//  * Some settings guessed from dumps and SCH5627 datasheet.
	//  */

	// /* IRQ1 to KBC */
	// pnp_write_config(dev, SCH5545_IRQ_BASE + 1, SCH5545_IRQ_KBD); 

	// /* IRQ2 (nSMI) to Embedded Memory Interface (EC) 
	//  * and select second interrupt signal
	//  */
	// pnp_write_config(dev, SCH5545_IRQ_BASE + 2,
	// 		 SCH5545_IRQ_EMI_IRQ_SOURCE);

	// /* IRQ12 to KBC and select second interrupt signal for mouse */
	// pnp_write_config(dev, SCH5545_IRQ_BASE + 12, SCH5545_IRQ_MOUSE);

	// /* Set up BAR for EMI to 0x0a40.	
	//  * Flipped due to different register layout on SMSC SuperIO
	//  */
	// pnp_set_iobase(dev, SCH5545_BAR_EM_IF + 2, 0x400a);
	// val = pnp_read_config(dev, SCH5545_BAR_EM_IF + 1);
	// val |= 0x80; /* set valid */
	// pnp_write_config(dev, SCH5545_BAR_EM_IF + 1, val);

	// /* Set up BAR for KBC, default is 0x60, so just set it as valid */
	// val = pnp_read_config(dev, SCH5545_BAR_KBC + 1);
	// val |= 0x80; /* set valid */
	// pnp_write_config(dev, SCH5545_BAR_KBC + 1, val);

	// /* enable KBC */
	// dev = PNP_DEV(0x2e, SCH5545_LDN_KBC);
	// pnp_set_logical_device(dev);
	// pnp_set_enable(dev, 1);

	// /* set LED color to green and on */
	// val = SCH5545_LED_COLOR_GREEN | SCH5545_LED_BLINK_ON |
	//       SCH5545_LED_CODE_FETCH;
	// outb(val, SCH5545_RUNTIME_REG_BASE + SCH5545_RR_LED);

	// sch5545_exit_conf_state(dev);
}

void mainboard_get_spd(spd_raw_data *spd, bool id_only)
{
	read_spd(&spd[0], 0x50, id_only);
	read_spd(&spd[1], 0x51, id_only);
	read_spd(&spd[2], 0x52, id_only);
	read_spd(&spd[3], 0x53, id_only);
}
