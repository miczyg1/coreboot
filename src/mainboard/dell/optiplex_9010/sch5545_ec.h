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

uint16_t sch5545_get_ec_fw_version(void);
void sch5545_update_ec_firmware(void);
void sch5545_ec_fan_spin_up(void);
void sch5545_ec_finalize(void);
int ec_write_read_reg_int_disabled(uint16_t ldn, uint16_t reg, uint8_t *value,
				   uint8_t expected);
int ec_write_read_reg_ldn_without_int(uint16_t ldn, uint16_t reg, uint8_t val);
int ec_write_32_bulk_with_int(uint16_t addr, uint32_t *data, uint32_t size);
