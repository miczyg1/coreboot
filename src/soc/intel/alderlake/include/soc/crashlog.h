/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _SOC_COMMON_BLOCK_CRASHLOG_LIB_H_
#define _SOC_COMMON_BLOCK_CRASHLIB_LIB_H_

#include <types.h>


/* DVSEC capability Registers */
#define TEL_DVSEC_OFFSET			0x100
#define TEL_DVSEC_PCIE_CAP_ID			0x0
#define TEL_DVSEC_NEXT_CAP			0x2
#define TEL_DVSEV_ID				0x8
#define TEL_DVSEV_DISCOVERY_TABLE_OFFSET	0xC
#define TELEMETRY_EXTENDED_CAP_ID		0x23
#define CRASHLOG_DVSEC_ID			0x04
#define TEL_DVSEC_TBIR_BAR0			0
#define TEL_DVSEC_TBIR_BAR1			1

/* CPU CrashLog MMIO Registers */
#define CRASHLOG_MAILBOX_INTF_ADDRESS		0x6038
#define CRASHLOG_POINTER_SIZE_FIELD_OFFSET	0x04

#endif /* _SOC_COMMON_BLOCK_CRASHLOG_LIB_H_ */