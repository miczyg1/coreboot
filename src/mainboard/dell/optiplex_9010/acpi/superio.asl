/*
 * This file is part of the coreboot project.
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
/*
#undef SUPERIO_DEV
#undef SUPERIO_PNP_BASE
#define SUPERIO_DEV		SIO1
#define SUPERIO_PNP_BASE	0x2e

#define SUPERIO_SHOW_UARTA
#define SUPERIO_SHOW_KBC

#include <superio/smsc/sch5545/acpi/superio.asl>
*/
Scope (\_GPE)
{
	Method (_L08, 0, NotSerialized)
	{
		/*\_SB.PCI0.LPCB.SIO1.SIOH ()*/
		Notify (\_SB.PWRB, 0x02)
	}

	Method (_L0D, 0, NotSerialized)
	{
		Notify (\_SB.PCI0.EHC1, 0x02)
		Notify (\_SB.PCI0.EHC2, 0x02)
		Notify (\_SB.PCI0.GLAN, 0x02)
	}

	Method (_L09, 0, NotSerialized)
	{
		Notify (\_SB.PCI0.RP01, 0x02)
		Notify (\_SB.PCI0.RP02, 0x02)
		Notify (\_SB.PCI0.RP03, 0x02)
		Notify (\_SB.PCI0.RP04, 0x02)
		Notify (\_SB.PCI0.RP05, 0x02)
		Notify (\_SB.PCI0.RP06, 0x02)
		Notify (\_SB.PCI0.RP07, 0x02)
		Notify (\_SB.PCI0.RP08, 0x02)
		Notify (\_SB.PCI0.PEGP, 0x02)
	}
}
