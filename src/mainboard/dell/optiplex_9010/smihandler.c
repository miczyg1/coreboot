/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 * Copyright (C) 2014 Vladimir Serbinenko
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

#include <arch/io.h>
#include <console/console.h>
#include <cpu/x86/smm.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <southbridge/intel/common/pmutil.h>
#include <southbridge/intel/common/pmbase.h>

#include "sch5545_ec.h"

static void dump_pmbase(void)
{

	printk(BIOS_SPEW, "PM1_STS: %04x\n"
			  "PM1_EN: %04x\n"
			  "PM1_CNT: %08x\n"
			  "PM1_TMR: %08x\n"
			  "GPE0_STS: %08x\n"
			  "GPE0_EN: %08x\n"
			  "SMI_EN: %08x\n"
			  "SMI_STS: %08x\n"
			  "ALT_GP_SMI_EN: %04x\n"
			  "ALT_GP_SMI_STS: %04x\n"
			  "GPE_CNTL: %02x\n",
			  read_pmbase16(PM1_STS), read_pmbase16(PM1_EN),
			  read_pmbase32(PM1_CNT), read_pmbase32(PM1_TMR),
			  read_pmbase32(GPE0_STS), read_pmbase32(GPE0_EN),
			  read_pmbase32(SMI_EN), read_pmbase32(SMI_STS),
			  read_pmbase16(ALT_GP_SMI_EN),
			  read_pmbase16(ALT_GP_SMI_STS), read_pmbase8(GPE_CNTL)
		);
}


void mainboard_smi_gpi(u32 gpi_sts)
{
	printk(BIOS_SPEW, "%s: gpi_sts: %08x\n", __func__, gpi_sts);
	dump_pmbase();
	/* intrusion switch connected to INTRUDER# on CPU/PCH */
}

int mainboard_smi_apmc(u8 data)
{
	switch (data) {
	case APM_CNT_ACPI_ENABLE:
		printk(BIOS_SPEW, "%s: APM CNT EN: %02x\n", __func__, data);
		dump_pmbase();
		break;
	case APM_CNT_ACPI_DISABLE:
		printk(BIOS_SPEW, "%s: APM CNT DIS: %02x\n", __func__, data);
		dump_pmbase();
		break;
	default:
		break;
	}
	return 0;
}

void mainboard_smi_sleep(u8 slp_typ)
{
	printk(BIOS_SPEW, "%s: SMI sleep: %02x\n", __func__, slp_typ);
	dump_pmbase();
	if (slp_typ == 3) {

	}
}

void mainboard_smi_serirq(void)
{
//	sch5545_ec_handle_serirq_smi();
}

