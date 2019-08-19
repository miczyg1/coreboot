/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 The ChromiumOS Authors.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef ELOG_H_
#define ELOG_H_

#include <stdint.h>

#define MAX_EVENT_SIZE                    0x7F

/* End of log */
#define ELOG_TYPE_EOL                     0xFF

struct event_header {
	uint8_t type;
	uint8_t length;
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} __packed;

/*
 * Standard SMBIOS event log types below 0x80
 */
#define ELOG_TYPE_UNDEFINED_EVENT         0x00
#define ELOG_TYPE_SINGLE_BIT_ECC_MEM_ERR  0x01
#define ELOG_TYPE_MULTI_BIT_ECC_MEM_ERR   0x02
#define ELOG_TYPE_MEM_PARITY_ERR          0x03
#define ELOG_TYPE_BUS_TIMEOUT             0x04
#define ELOG_TYPE_IO_CHECK                0x05
#define ELOG_TYPE_SW_NMI                  0x06
#define ELOG_TYPE_POST_MEM_RESIZE         0x07
#define ELOG_TYPE_POST_ERR                0x08
#define ELOG_TYPE_PCI_PERR                0x09
#define ELOG_TYPE_PCI_SERR                0x0A
#define ELOG_TYPE_CPU_FAIL                0x0B
#define ELOG_TYPE_EISA_TIMEOUT            0x0C
#define ELOG_TYPE_CORRECTABLE_MEMLOG_DIS  0x0D
#define ELOG_TYPE_LOG_DISABLED            0x0E
#define ELOG_TYPE_UNDEFINED_EVENT2        0x0F
#define ELOG_TYPE_SYS_LIMIT_EXCEED        0x10
#define ELOG_TYPE_ASYNC_HW_TIMER_EXPIRED  0x11
#define ELOG_TYPE_SYS_CONFIG_INFO         0x12
#define ELOG_TYPE_HDD_INFO                0x13
#define ELOG_TYPE_SYS_RECONFIG            0x14
#define ELOG_TYPE_CPU_ERROR               0x15
#define ELOG_TYPE_LOG_CLEAR               0x16
#define ELOG_TYPE_BOOT                    0x17

/*
 * Extended defined OEM event types start at 0x80
 */

/* OS/kernel events */
#define ELOG_TYPE_OS_EVENT                0x81

/* Last event from coreboot */
#define ELOG_TYPE_OS_BOOT                 0x90

/* Embedded controller event */
#define ELOG_TYPE_EC_EVENT                0x91
#define EC_EVENT_LID_CLOSED                  0x01
#define EC_EVENT_LID_OPEN                    0x02
#define EC_EVENT_POWER_BUTTON                0x03
#define EC_EVENT_AC_CONNECTED                0x04
#define EC_EVENT_AC_DISCONNECTED             0x05
#define EC_EVENT_BATTERY_LOW                 0x06
#define EC_EVENT_BATTERY_CRITICAL            0x07
#define EC_EVENT_BATTERY                     0x08
#define EC_EVENT_THERMAL_THRESHOLD           0x09
#define EC_EVENT_DEVICE_EVENT                0x0a
#define EC_EVENT_THERMAL                     0x0b
#define EC_EVENT_USB_CHARGER                 0x0c
#define EC_EVENT_KEY_PRESSED                 0x0d
#define EC_EVENT_INTERFACE_READY             0x0e
#define EC_EVENT_KEYBOARD_RECOVERY           0x0f
#define EC_EVENT_THERMAL_SHUTDOWN            0x10
#define EC_EVENT_BATTERY_SHUTDOWN            0x11
#define EC_EVENT_FAN_ERROR                   0x12
#define EC_EVENT_THROTTLE_STOP               0x13
#define EC_EVENT_HANG_DETECT                 0x14
#define EC_EVENT_HANG_REBOOT                 0x15
#define EC_EVENT_PD_MCU                      0x16
#define EC_EVENT_BATTERY_STATUS              0x17
#define EC_EVENT_PANIC                       0x18
#define EC_EVENT_KEYBOARD_FASTBOOT           0x19
#define EC_EVENT_RTC                         0x1a
#define EC_EVENT_MKBP                        0x1b
#define EC_EVENT_USB_MUX                     0x1c
#define EC_EVENT_MODE_CHANGE                 0x1d
#define EC_EVENT_KEYBOARD_RECOVERY_HWREINIT  0x1e
#define EC_EVENT_EXTENDED                    0x1f

/* Power */
#define ELOG_TYPE_POWER_FAIL              0x92
#define ELOG_TYPE_SUS_POWER_FAIL          0x93
#define ELOG_TYPE_PWROK_FAIL              0x94
#define ELOG_TYPE_SYS_PWROK_FAIL          0x95
#define ELOG_TYPE_POWER_ON                0x96
#define ELOG_TYPE_POWER_BUTTON            0x97
#define ELOG_TYPE_POWER_BUTTON_OVERRIDE   0x98

/* Reset */
#define ELOG_TYPE_RESET_BUTTON            0x99
#define ELOG_TYPE_SYSTEM_RESET            0x9a
#define ELOG_TYPE_RTC_RESET               0x9b
#define ELOG_TYPE_TCO_RESET               0x9c

/* Sleep/Wake */
#define ELOG_TYPE_ACPI_ENTER              0x9d
/*
 * Deep Sx wake variant is provided below - 0xad
 * Sleep/"wake pending" event log provided below - 0xb1 - 0x01/0x02
 */

#define ELOG_TYPE_ACPI_WAKE               0x9e
#define ELOG_TYPE_WAKE_SOURCE             0x9f
#define  ELOG_WAKE_SOURCE_PCIE             0x00
#define  ELOG_WAKE_SOURCE_PME              0x01
#define  ELOG_WAKE_SOURCE_PME_INTERNAL     0x02
#define  ELOG_WAKE_SOURCE_RTC              0x03
#define  ELOG_WAKE_SOURCE_GPIO             0x04
#define  ELOG_WAKE_SOURCE_SMBUS            0x05
#define  ELOG_WAKE_SOURCE_PWRBTN           0x06
#define  ELOG_WAKE_SOURCE_PME_HDA          0x07
#define  ELOG_WAKE_SOURCE_PME_GBE          0x08
#define  ELOG_WAKE_SOURCE_PME_EMMC         0x09
#define  ELOG_WAKE_SOURCE_PME_SDCARD       0x0a
#define  ELOG_WAKE_SOURCE_PME_PCIE1        0x0b
#define  ELOG_WAKE_SOURCE_PME_PCIE2        0x0c
#define  ELOG_WAKE_SOURCE_PME_PCIE3        0x0d
#define  ELOG_WAKE_SOURCE_PME_PCIE4        0x0e
#define  ELOG_WAKE_SOURCE_PME_PCIE5        0x0f
#define  ELOG_WAKE_SOURCE_PME_PCIE6        0x10
#define  ELOG_WAKE_SOURCE_PME_PCIE7        0x11
#define  ELOG_WAKE_SOURCE_PME_PCIE8        0x12
#define  ELOG_WAKE_SOURCE_PME_PCIE9        0x13
#define  ELOG_WAKE_SOURCE_PME_PCIE10       0x14
#define  ELOG_WAKE_SOURCE_PME_PCIE11       0x15
#define  ELOG_WAKE_SOURCE_PME_PCIE12       0x16
#define  ELOG_WAKE_SOURCE_PME_SATA         0x17
#define  ELOG_WAKE_SOURCE_PME_CSE          0x18
#define  ELOG_WAKE_SOURCE_PME_CSE2         0x19
#define  ELOG_WAKE_SOURCE_PME_CSE3         0x1a
#define  ELOG_WAKE_SOURCE_PME_XHCI         0x1b
#define  ELOG_WAKE_SOURCE_PME_XDCI         0x1c
#define  ELOG_WAKE_SOURCE_PME_XHCI_USB_2   0x1d
#define  ELOG_WAKE_SOURCE_PME_XHCI_USB_3   0x1e
#define  ELOG_WAKE_SOURCE_PME_WIFI         0x1f

struct elog_event_data_wake {
	uint8_t source;
	uint32_t instance;
} __packed;

/* Chrome OS related events */
#define ELOG_TYPE_CROS_DEVELOPER_MODE     0xa0
#define ELOG_TYPE_CROS_RECOVERY_MODE      0xa1
#define  ELOG_CROS_RECOVERY_MODE_BUTTON    0x02

/* Management Engine Events */
#define ELOG_TYPE_MANAGEMENT_ENGINE       0xa2
#define ELOG_TYPE_MANAGEMENT_ENGINE_EXT   0xa4
struct elog_event_data_me_extended {
	uint8_t current_working_state;
	uint8_t operation_state;
	uint8_t operation_mode;
	uint8_t error_code;
	uint8_t progress_code;
	uint8_t current_pmevent;
	uint8_t current_state;
} __packed;

/* Last post code from previous boot */
#define ELOG_TYPE_LAST_POST_CODE          0xa3
#define ELOG_TYPE_POST_EXTRA              0xa6

/* EC Shutdown Reason */
#define ELOG_TYPE_EC_SHUTDOWN             0xa5

/* ARM/generic versions of sleep/wake - These came from another firmware
 * apparently, but not all the firmware sources were updated so that the
 * elog namespace was coherent. */
#define ELOG_TYPE_SLEEP                   0xa7
#define ELOG_TYPE_WAKE                    0xa8
#define ELOG_TYPE_FW_WAKE                 0xa9

/* Memory Cache Update */
#define ELOG_TYPE_MEM_CACHE_UPDATE        0xaa
#define  ELOG_MEM_CACHE_UPDATE_SLOT_NORMAL    0
#define  ELOG_MEM_CACHE_UPDATE_SLOT_RECOVERY  1
#define  ELOG_MEM_CACHE_UPDATE_SLOT_VARIABLE  2
#define  ELOG_MEM_CACHE_UPDATE_STATUS_SUCCESS 0
#define  ELOG_MEM_CACHE_UPDATE_STATUS_FAIL    1
struct elog_event_mem_cache_update {
	uint8_t slot;
	uint8_t status;
} __packed;

/* CPU Thermal Trip */
#define ELOG_TYPE_THERM_TRIP              0xab

/* Cr50 */
#define ELOG_TYPE_CR50_UPDATE             0xac

/* Deep Sx wake variant */
#define ELOG_TYPE_ACPI_DEEP_WAKE          0xad

/* EC Device Event */
#define ELOG_TYPE_EC_DEVICE_EVENT         0xae
#define ELOG_EC_DEVICE_EVENT_TRACKPAD       0x01
#define ELOG_EC_DEVICE_EVENT_DSP            0x02
#define ELOG_EC_DEVICE_EVENT_WIFI           0x03
#define ELOG_EC_DEVICE_EVENT_CASE_OPEN      0x04
#define ELOG_EC_DEVICE_EVENT_CASE_CLOSE     0x05

/* S0ix sleep/wake */
#define ELOG_TYPE_S0IX_ENTER              0xaf
#define ELOG_TYPE_S0IX_EXIT               0xb0

/* Extended events */
#define ELOG_TYPE_EXTENDED_EVENT          0xb1
#define  ELOG_SLEEP_PENDING_PM1_WAKE       0x01
#define  ELOG_SLEEP_PENDING_GPE0_WAKE      0x02

/* Cr50 reset to enable TPM */
#define ELOG_TYPE_CR50_NEED_RESET         0xb2

struct elog_event_extended_event {
	uint8_t event_type;
	uint32_t event_complement;
} __packed;

#define ELOG_EVENT_TO_NAME_TABLE \
	{ ELOG_TYPE_UNDEFINED_EVENT,		"UNDEFINED EVENT" },\
	{ ELOG_TYPE_SINGLE_BIT_ECC_MEM_ERR,	"Single-Bit ECC memory error" },\
	{ ELOG_TYPE_MULTI_BIT_ECC_MEM_ERR,	"Multi-Bit ECC memory error" },\
	{ ELOG_TYPE_MEM_PARITY_ERR,		"Memory parity error" },\
	{ ELOG_TYPE_BUS_TIMEOUT,		"Bus time-out" },\
	{ ELOG_TYPE_IO_CHECK,			"IO channel check" },\
	{ ELOG_TYPE_SW_NMI,			"Software NMI" }, \
	{ ELOG_TYPE_POST_MEM_RESIZE,		"Post memory resize" },\
	{ ELOG_TYPE_POST_ERR,			"Post error" },\
	{ ELOG_TYPE_PCI_PERR,			"PCI parity error" },\
	{ ELOG_TYPE_PCI_SERR,			"PCI system error" },\
	{ ELOG_TYPE_CPU_FAIL,			"CPU failure" },\
	{ ELOG_TYPE_EISA_TIMEOUT,		"EISA FailSafe Timer time-out" },\
	{ ELOG_TYPE_CORRECTABLE_MEMLOG_DIS, "Correctable memory log disable" },\
	{ ELOG_TYPE_LOG_DISABLED,		"Event log disabled for type" },\
	{ ELOG_TYPE_UNDEFINED_EVENT2,		"UNDEFINED EVENT 2" },\
	{ ELOG_TYPE_SYS_LIMIT_EXCEED,		"System limit exceeded" },\
	{ ELOG_TYPE_ASYNC_HW_TIMER_EXPIRED,	"Asynchronous hardware timer expired and issued a system reset" },\
	{ ELOG_TYPE_SYS_CONFIG_INFO,		"System configuration information" },\
	{ ELOG_TYPE_HDD_INFO,			"Hard-disk information" },\
	{ ELOG_TYPE_SYS_RECONFIG,		"System reconfigured" },\
	{ ELOG_TYPE_CPU_ERROR,			"Uncorrectable CPU-complex error" },\
	{ ELOG_TYPE_LOG_CLEAR,			"Log Area reset/cleared" },\
	{ ELOG_TYPE_BOOT,			"System boot" },\
	{ ELOG_TYPE_OS_EVENT,			"Operating system event" },\
	{ ELOG_TYPE_OS_BOOT,			"Boot operating system" },\
	{ ELOG_TYPE_POWER_FAIL,			"Power failure" },\
	{ ELOG_TYPE_SUS_POWER_FAIL,		"Suspend power failure" },\
	{ ELOG_TYPE_PWROK_FAIL,			"Power OK failure" },\
	{ ELOG_TYPE_SYS_PWROK_FAIL,		"System power OK failure" },\
	{ ELOG_TYPE_POWER_ON,			"Power on" },\
	{ ELOG_TYPE_POWER_BUTTON,		"Power button pressed" },\
	{ ELOG_TYPE_POWER_BUTTON_OVERRIDE,	"Power button override" },\
	{ ELOG_TYPE_RESET_BUTTON,		"Reset button pressed" },\
	{ ELOG_TYPE_SYSTEM_RESET,		"System reset" },\
	{ ELOG_TYPE_RTC_RESET,			"Real Time Clock reset" },\
	{ ELOG_TYPE_TCO_RESET,			"TCO timer reset" },\
	{ ELOG_TYPE_ACPI_ENTER,			"Entered ACPI state" },\
	{ ELOG_TYPE_ACPI_WAKE,			"ACPI wake event" }, \
	{ ELOG_TYPE_WAKE_SOURCE,		"ACPI wake source" }, \
	{ ELOG_TYPE_CROS_DEVELOPER_MODE,	"Entered ChromeOS developer mode" },\
	{ ELOG_TYPE_CROS_RECOVERY_MODE,		"Entered ChromeOS recovery mode" },\
	{ ELOG_TYPE_MANAGEMENT_ENGINE,		"Intel Management Engine event" },\
	{ ELOG_TYPE_MANAGEMENT_ENGINE_EXT,	"Intel Management Engine extended event" },\
	{ ELOG_TYPE_LAST_POST_CODE,		"Post code from last boot" },\
	{ ELOG_TYPE_POST_EXTRA,			"Post code extra" },\
	{ ELOG_TYPE_EC_SHUTDOWN,		"Embedded Controller shutdown" },\
	{ ELOG_TYPE_SLEEP,			"Entered sleep mode", },\
	{ ELOG_TYPE_WAKE,			"Wake event" },\
	{ ELOG_TYPE_FW_WAKE,			"Firmware wake event" },\
	{ ELOG_TYPE_MEM_CACHE_UPDATE,		"MRC cache update" },\
	{ ELOG_TYPE_THERM_TRIP,			"Thermal trip occured" },\
	{ ELOG_TYPE_CR50_UPDATE,		"CR50 TPM update event" },\
	{ ELOG_TYPE_ACPI_DEEP_WAKE,		"ACPI deep wake event" },\
	{ ELOG_TYPE_EC_DEVICE_EVENT,		"Embedded controller device event" },\
	{ ELOG_TYPE_S0IX_ENTER,			"Entered S0ix state" },\
	{ ELOG_TYPE_S0IX_EXIT,			"Exited from S0ix state" },\
	{ ELOG_TYPE_EXTENDED_EVENT,		"Extended event" },\
	{ ELOG_TYPE_CR50_NEED_RESET,		"CR50 TPM configuration needs reset" }

#define EC_EVENT_TO_NAME_TABLE \
	{ EC_EVENT_LID_CLOSED,			"Lid closed" },\
	{ EC_EVENT_LID_OPEN,			"Lid open" },\
	{ EC_EVENT_POWER_BUTTON,		"Power button pressed" },\
	{ EC_EVENT_AC_CONNECTED,		"AC power supply connected" },\
	{ EC_EVENT_AC_DISCONNECTED,		"AC power supply disconnected" },\
	{ EC_EVENT_BATTERY_LOW,			"Battery low" },\
	{ EC_EVENT_BATTERY_CRITICAL,		"Battery critical" },\
	{ EC_EVENT_BATTERY,			"Battery event" },\
	{ EC_EVENT_THERMAL_THRESHOLD,		"Thermal threshold reached" },\
	{ EC_EVENT_DEVICE_EVENT,		"Device event" },\
	{ EC_EVENT_THERMAL,			"Thermal event" },\
	{ EC_EVENT_USB_CHARGER,			"USB charger" },\
	{ EC_EVENT_KEY_PRESSED,			"Key pressed" },\
	{ EC_EVENT_INTERFACE_READY,		"Interface ready" },\
	{ EC_EVENT_KEYBOARD_RECOVERY,		"Keyboard recovery" },\
	{ EC_EVENT_THERMAL_SHUTDOWN,		"Thermal shutdown" },\
	{ EC_EVENT_BATTERY_SHUTDOWN,		"Battery shutdown" },\
	{ EC_EVENT_FAN_ERROR,			"Fan error" },\
	{ EC_EVENT_THROTTLE_STOP,		"Throttling stopeed" },\
	{ EC_EVENT_HANG_DETECT,			"Hang detected" },\
	{ EC_EVENT_HANG_REBOOT,			"Reboot hang" },\
	{ EC_EVENT_PD_MCU,			"PD processor" },\
	{ EC_EVENT_BATTERY_STATUS,		"Battery status" },\
	{ EC_EVENT_PANIC,			"Panic" },\
	{ EC_EVENT_KEYBOARD_FASTBOOT,		"Keyboard fastboot" },\
	{ EC_EVENT_RTC,				"Real Time Clock" },\
	{ EC_EVENT_MKBP,			"Matrix Keyboard Protocol" },\
	{ EC_EVENT_USB_MUX,			"USB multiplexer" },\
	{ EC_EVENT_MODE_CHANGE,			"Mode change" },\
	{ EC_EVENT_KEYBOARD_RECOVERY_HWREINIT,	"Keyboard recovery hardware reinitialization" },\
	{ EC_EVENT_EXTENDED,			"Extended event" }

#define WAKE_EVENT_TO_NAME_TABLE \
	{ ELOG_WAKE_SOURCE_PCIE,		"PCI Express" },\
	{ ELOG_WAKE_SOURCE_PME,			"PME" },\
	{ ELOG_WAKE_SOURCE_PME_INTERNAL,	"Internal PME" },\
	{ ELOG_WAKE_SOURCE_RTC,			"Real Time Clock" },\
	{ ELOG_WAKE_SOURCE_GPIO,		"GPIO" },\
	{ ELOG_WAKE_SOURCE_SMBUS,		"SMBus" },\
	{ ELOG_WAKE_SOURCE_PWRBTN,		"Power Button" },\
	{ ELOG_WAKE_SOURCE_PME_HDA,		"HD Audio PME" },\
	{ ELOG_WAKE_SOURCE_PME_GBE,		"Gigabit Ethernet PME" },\
	{ ELOG_WAKE_SOURCE_PME_EMMC,		"Embedded MMC PME" },\
	{ ELOG_WAKE_SOURCE_PME_SDCARD,		"SD card PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE1,		"PCI Express 1 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE2,		"PCI Express 2 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE3,		"PCI Express 3 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE4,		"PCI Express 4 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE5,		"PCI Express 5 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE6,		"PCI Express 6 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE7,		"PCI Express 7 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE8,		"PCI Express 8 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE9,		"PCI Express 9 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE10,		"PCI Express 10 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE11,		"PCI Express 11 PME" },\
	{ ELOG_WAKE_SOURCE_PME_PCIE12,		"PCI Express 12 PME" },\
	{ ELOG_WAKE_SOURCE_PME_SATA,		"SATA PME" },\
	{ ELOG_WAKE_SOURCE_PME_CSE,		"CSE PME" },\
	{ ELOG_WAKE_SOURCE_PME_CSE2,		"CSE 2 PME" },\
	{ ELOG_WAKE_SOURCE_PME_CSE3,		"CSE 3 PME" },\
	{ ELOG_WAKE_SOURCE_PME_XHCI,		"xHCI PME" },\
	{ ELOG_WAKE_SOURCE_PME_XDCI,		"xDCI PME" },\
	{ ELOG_WAKE_SOURCE_PME_XHCI_USB_2,	"xHCI USB2 PME" },\
	{ ELOG_WAKE_SOURCE_PME_XHCI_USB_3,	"xHCI USB2 PME" },\
	{ ELOG_WAKE_SOURCE_PME_WIFI,		"WiFi PME" }

#define EC_DEVICE_TO_NAME_TABLE \
	{ ELOG_EC_DEVICE_EVENT_TRACKPAD,	"Trackpad" },\
	{ ELOG_EC_DEVICE_EVENT_DSP,		"DSP" },\
	{ ELOG_EC_DEVICE_EVENT_WIFI,		"WiFi" },\
	{ ELOG_EC_DEVICE_EVENT_CASE_OPEN,	"Intrusion detection - case opened" },\
	{ ELOG_EC_DEVICE_EVENT_CASE_CLOSE,	"Intrusion detection - case closed" }

#endif /* ELOG_H_ */
