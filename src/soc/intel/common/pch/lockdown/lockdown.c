/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootstate.h>
#include <intelblocks/cfg.h>
#include <intelblocks/fast_spi.h>
#include <intelblocks/lpc_lib.h>
#include <intelblocks/pcr.h>
#include <intelblocks/systemagent.h>
#include <intelpch/lockdown.h>
#include <intelblocks/gpmr.h>
#include <soc/pci_devs.h>
#include <soc/pcr_ids.h>
#include <soc/soc_chip.h>

/*
 * This function will get lockdown config specific to soc.
 *
 * Return values:
 *  0 = CHIPSET_LOCKDOWN_COREBOOT = Use coreboot to lockdown IPs
 *  1 = CHIPSET_LOCKDOWN_FSP = use FSP's lockdown functionality to lockdown IPs
 */
int get_lockdown_config(void)
{
	const struct soc_intel_common_config *common_config;
	common_config = chip_get_common_soc_structure();

	return common_config->chipset_lockdown;
}

static void gpmr_lockdown_cfg(void)
{
	if (!CONFIG(SOC_INTEL_COMMON_BLOCK_GPMR))
		return;

	/*
	 * GCS reg
	 *
	 * When set, prevents GCS.BBS from being changed
	 * GCS.BBS: (Boot BIOS Strap) This field determines the destination
	 * of accesses to the BIOS memory range.
	 *	Bits Description
	 *	"0b": SPI
	 *	"1b": LPC/eSPI
	 */
	gpmr_or32(GPMR_GCS, GPMR_GCS_BILD);

	/*
	 * Set Secure Register Lock (SRL) bit in DMI control register to lock
	 * DMI configuration and bypass when IOC instead of DMI
	 */
	if (!CONFIG(SOC_INTEL_COMMON_BLOCK_IOC))
		gpmr_or32(GPMR_DMICTL, GPMR_DMICTL_SRLOCK);
}

static void sa_lockdown_config(int chipset_lockdown)
{
	if (!CONFIG(SOC_INTEL_COMMON_BLOCK_SA))
		return;

	if (chipset_lockdown == CHIPSET_LOCKDOWN_COREBOOT)
		sa_lock_pam();
}

/*
 * platform_lockdown_config has 2 major part.
 * 1. Common SoC lockdown configuration.
 * 2. SoC specific lockdown configuration as per Silicon
 * guideline.
 */
static void platform_lockdown_config(void *unused)
{
	int chipset_lockdown;
	chipset_lockdown = get_lockdown_config();

	if (!CONFIG(SOC_INTEL_COMMON_SPI_LOCKDOWN_SMM)) {
		/* SPI lock down configuration */
		fast_spi_lockdown_cfg(chipset_lockdown);

		/* LPC/eSPI lock down configuration */
		lpc_lockdown_config(chipset_lockdown);
	}

	/* GPMR lock down configuration */
	gpmr_lockdown_cfg();

	/* SA lock down configuration */
	sa_lockdown_config(chipset_lockdown);

	/* SoC lock down configuration */
	soc_lockdown_config(chipset_lockdown);
}

BOOT_STATE_INIT_ENTRY(BS_DEV_RESOURCES, BS_ON_EXIT, platform_lockdown_config,
				NULL);
