/* SPDX-License-Identifier: GPL-2.0-only */

#include <intelblocks/cfg.h>
#include <intelblocks/fast_spi.h>
#include <intelpch/lockdown.h>

void fast_spi_lockdown_cfg(int chipset_lockdown)
{
	if (!CONFIG(SOC_INTEL_COMMON_BLOCK_FAST_SPI))
		return;

	/* Set FAST_SPI opcode menu */
	fast_spi_set_opcode_menu();

	/* Discrete Lock Flash PR registers */
	fast_spi_pr_dlock();

	/* Check if SPI transaction is pending */
	fast_spi_cycle_in_progress();

	/* Clear any outstanding status bits like AEL, FCERR, FDONE, SAF etc. */
	fast_spi_clear_outstanding_status();

	/* Lock FAST_SPIBAR */
	fast_spi_lock_bar();

	/* Set Vendor Component Lock (VCL) */
	fast_spi_vscc0_lock();

	/* Set BIOS Interface Lock, BIOS Lock */
	if (chipset_lockdown == CHIPSET_LOCKDOWN_COREBOOT) {
		/* BIOS Interface Lock */
		fast_spi_set_bios_interface_lock_down();

		/* Only allow writes in SMM */
		if (CONFIG(BOOTMEDIA_SMM_BWP)) {
			fast_spi_set_eiss();
			fast_spi_enable_wp();
		}

		/* BIOS Lock */
		fast_spi_set_lock_enable();

		/* EXT BIOS Lock */
		fast_spi_set_ext_bios_lock_enable();
	}
}
