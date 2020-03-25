/*
 * This file is part of the coreboot project.
 *
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

#define READ_OP					0
#define WRITE_OP				1

#define EC_HWM_LDN				1
#define EC_GPIO_LDN				2
#define   EC_GPIO_PP			(0 << 0)
#define   EC_GPIO_OD			(1 << 0)
#define   EC_GPIO_FUNC0				(0 << 4)
#define   EC_GPIO_FUNC1				(1 << 4)
#define   EC_GPIO_FUNC2				(2 << 4)
#define   EC_GPIO_FUNC3				(3 << 4)

uint16_t sch5545_get_ec_fw_version(void);
void sch5545_update_ec_firmware(uint16_t ec_version);
void sch5545_ec_early_init(void);
void sch5545_ec_hwm_early_init(void);
void sch5545_ec_hwm_init(void *unused);
void sch5545_ec_enable_smi(void *unused);
void sch5545_ec_init_late(void);
void sch5545_ec_final(void *unused);
void sch5545_ec_handle_serirq_smi(void);
int ec_write_32_bulk_with_int(uint16_t addr, uint32_t *data, uint32_t size,
			      uint8_t mbox_msg);

/*
 * GUIDS:
 * SMSC5544DXE			900E6DC5-B1D5-4A51-B4012309D3A6E797
 * DxeEmiProtocol1		3B63BCF5-4B92-4CF6-8E529C2B16882026
 * DxeEmiProtocol2		378012DD-AD6E-4618-8036AF72F44BD3DC
 * SmmEventDxeGuid		E492B063-E846-4810-A96801BC24339774
 * DxeSwSmiGuid			8a32a694-b440-42fd-b917-23cf4cdeb54a
 * DxeEmiProtocolNotify		59daebc7-6b3e-4f48-b827-1b19e07dc905
 * DxeHwmDriver1		29630EB9-54E5-4A6D-9C9E5D41F6779572
 * DxeHwmDriver2		DC193D57-30DF-499B-8ABAF10264C01B11
 * ECInitGuid			417acee0-6fa9-4a82-99d7-f9b1dd271e48
 * DxeVariableGuid1		71db7b7e-4165-48fa-ac9d-f9af4cefc534
 * DxeVariableGuid2		af976ecd-3ca1-4d3f-850e-bddc83420744
 * DxeECIODriver		a48e3fdc-f716-4f88-a236-cef8403358aa
 * SmmSioEmiGuid2		9ddf7bf2-ae76-41ea-b5b2-adfb53f774f1
 * SmmSioEmiGuid1		59daebc7-6b3e-4f48-b827-1b19e07dc905
 * SmmSioEmiHandleProtocol	a28d678a-57b9-4184-8920-955aa966a24e
 * DxeHWM1NNotifyGUid		c0c1d5e0-dd40-46bf-90e5-19c3f2b62656
 * DxeHWM2NNotifyGUid		3f1d5ffd-f6ae-4116-a512-370d7bac6d6c
 */