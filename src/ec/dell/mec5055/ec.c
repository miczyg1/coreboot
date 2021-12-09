/* SPDX-License-Identifier: GPL-2.0-only */

#include <console/console.h>
#include <delay.h>
#include <device/device.h>
#include <device/pnp.h>
#include <pc80/keyboard.h>
#include <superio/conf_mode.h>

#include "mec5055.h"

static void mec5055_pnp_init(struct device *dev)
{
	if (!dev->enabled)
		return;

	switch (dev->path.pnp.device) {
	case MEC5055_KBC:
		pc_keyboard_init(NO_AUX_DEVICE);
		break;
	case MEC5055_LPC:
		pnp_enter_conf_mode(dev);
		pnp_set_logical_device(dev);
		/* Enable SERIRQ */
		pnp_write_config(dev, 0x24, pnp_read_config(dev, 0x24) | 0x04);
		pnp_exit_conf_mode(dev);
		break;
	}
}

static void mec5055_set_iobase(struct device *dev, u8 index, u16 iobase)
{
	u8 val;
	struct device *lpc_if;
	u8 iobase_reg = 0;

	lpc_if = dev_find_slot_pnp(dev->path.pnp.port, MEC5055_LPC);

	if (!lpc_if) {
		printk(BIOS_ERR, "ERROR: %s LPC interface LDN not present."
		       "Check the devicetree!\n", dev_path(dev));
		return;
	}

	switch (dev->path.pnp.device) {
	case MEC5055_LPC:
		iobase_reg = 0x60;
		break;
	case MEC5055_MAILBOX:
		iobase_reg = 0x64;
		break;
	case MEC5055_KBC:
		iobase_reg = 0x68;
		break;
	case MEC5055_ACPI_EC1:
		iobase_reg = 0x6c;
		break;
	case MEC5055_ACPI_EC2:
		iobase_reg = 0x70;
		break;
	case MEC5055_ACPI_EC3:
		iobase_reg = 0x74;
		break;
	case MEC5055_ACPI_EC4:
		iobase_reg = 0x78;
		break;
	case MEC5055_ACPI_EC5:
		iobase_reg = 0x7c;
		break;
	case MEC5055_UART1:
		iobase_reg = 0x80;
		break;
	case MEC5055_UART2:
		iobase_reg = 0x84;
		break;
	case MEC5055_LEGACY_FAST_KB:
		iobase_reg = 0x88;
		break;
	case MEC5055_EMBEDDED_FLASH:
		iobase_reg = 0x8c;
		break;
	case MEC5055_EMBEDDED_MEMORY:
		iobase_reg = 0x90;
		break;
	default:
		return;
	}

	pnp_set_logical_device(lpc_if);

	/* Flip the bytes in IO base, LSB goes first */
	pnp_write_config(lpc_if, iobase_reg + 2, iobase & 0xff);
	pnp_write_config(lpc_if, iobase_reg + 3, (iobase >> 8) & 0xff);

	/* Set valid bit */
	val = pnp_read_config(lpc_if, iobase_reg + 1);
	val |= 0x80;
	pnp_write_config(lpc_if, iobase_reg + 1, val);

	pnp_set_logical_device(dev);
}

static void mec5055_set_irq(struct device *dev, u8 index, u8 irq)
{
	u8 select_bit = 0;
	struct device *lpc_if;

	/* In case it is not the IRQ, write misc register directly */
	if (index >= PNP_IDX_MSC0) {
		pnp_write_config(dev, index, irq);
		return;
	}

	lpc_if = dev_find_slot_pnp(dev->path.pnp.port, MEC5055_LPC);

	if (!lpc_if) {
		printk(BIOS_ERR, "ERROR: %s LPC interface LDN not present."
		       "Check the devicetree!\n", dev_path(dev));
		return;
	}

	pnp_set_logical_device(lpc_if);

	/*
	 * Some LDNs can generate IRQs from two sources, i.e.
	 * - KBC may generate separate IRQ for mouse and keyboard,
	 * SELECT bit allows to distinguish IRQ source for single LDN.
	 * Use the standard IRQs for devices.
	 */
	switch (dev->path.pnp.device) {
	case MEC5055_KBC:
		if (index == 0x72)
			select_bit = 0x80;
		break;
	default:
		break;
	}

	/*
	 * IRQs are set in a little different manner. Each IRQ number has its
	 * own register which is programmed with LDN number which should use
	 * the IRQ. Ignore the index offset and choose register based on IRQ
	 * number counting from IRQ base.
	 */
	pnp_write_config(lpc_if, MEC5055_IRQ_BASE + irq, dev->path.pnp.device | select_bit);
	pnp_set_logical_device(dev);
}

static void mec5055_set_drq(struct device *dev, u8 index, u8 drq)
{
	struct device *lpc_if;

	if (drq == 4) {
		printk(BIOS_ERR, "ERROR: %s %02x: Trying to set reserved DMA channel 4!\n",
		       dev_path(dev), index);
		printk(BIOS_ERR, "This configuration is untested. Trying to continue.\n");
	}

	/* DMA channel is programmed via LPC LDN */
	lpc_if = dev_find_slot_pnp(dev->path.pnp.port, MEC5055_LPC);

	if (!lpc_if) {
		printk(BIOS_ERR, "ERROR: %s LPC interface LDN not present."
		       "Check the devicetree!\n", dev_path(dev));
		return;
	}

	pnp_set_logical_device(lpc_if);

	/*
	 * There are 8 configurable DMA channels. DRQs are set in a little
	 * different manner. Each DMA channel has its own 16-bit register which
	 * is programmed with LDN number (in higher byte) which should use the
	 * IRQ. Ignore the index offset and choose register based on IRQ number
	 * counting from IRQ base. Set valid bit (bit 7) additionally.
	 */
	pnp_write_config(dev, MEC5055_DRQ_BASE + (drq * 2) + 1, dev->path.pnp.device | 0x80);

	pnp_set_logical_device(dev);
}

static void mec5055_set_resource(struct device *dev, struct resource *resource)
{
	if (!(resource->flags & IORESOURCE_ASSIGNED)) {
		/*
		 * The PNP_MSC super IO registers have the IRQ flag set. If no
		 * value is assigned in the devicetree, the corresponding
		 * PNP_MSC register doesn't get written, which should be printed
		 * as warning and not as error.
		 */
		if (resource->flags & IORESOURCE_IRQ &&
		    (resource->index != PNP_IDX_IRQ0) &&
		    (resource->index != PNP_IDX_IRQ1))
			printk(BIOS_WARNING, "WARNING: %s %02lx %s size: "
			       "0x%010llx not assigned\n", dev_path(dev),
			       resource->index, resource_type(resource),
			       resource->size);
		else
			printk(BIOS_ERR, "ERROR: %s %02lx %s size: 0x%010llx "
			       "not assigned\n", dev_path(dev), resource->index,
			       resource_type(resource), resource->size);
		return;
	}

	/* Now store the resource. */
	if (resource->flags & IORESOURCE_IO) {
		mec5055_set_iobase(dev, resource->index, resource->base);
	} else if (resource->flags & IORESOURCE_DRQ) {
		mec5055_set_drq(dev, resource->index, resource->base);
	} else if (resource->flags & IORESOURCE_IRQ) {
		mec5055_set_irq(dev, resource->index, resource->base);
	} else {
		printk(BIOS_ERR, "ERROR: %s %02lx unknown resource type\n",
		       dev_path(dev), resource->index);
		return;
	}
	resource->flags |= IORESOURCE_STORED;

	report_resource_stored(dev, resource, "");
}

static void mec5055_set_resources(struct device *dev)
{
	struct resource *res;

	pnp_enter_conf_mode(dev);

	/* Select the logical device (LDN). */
	pnp_set_logical_device(dev);

	for (res = dev->resource_list; res; res = res->next)
		mec5055_set_resource(dev, res);

	pnp_exit_conf_mode(dev);
}

static struct device_operations ec_pnp_ops = {
	.read_resources   = pnp_read_resources,
	.set_resources    = pnp_set_resources,
	.enable_resources = pnp_enable_resources,
	.enable           = pnp_alt_enable,
	.init             = mec5055_pnp_init,
	.ops_pnp_mode     = &pnp_conf_mode_55_aa,
};

static struct pnp_info pnp_dev_info[] = {
	{ NULL, MEC5055_LPC,		 PNP_IO0, 0x0ffe },
	{ NULL, MEC5055_MAILBOX,	 PNP_IO0, 0x0ff8 },
	{ NULL, MEC5055_KBC,		 PNP_IO0 | PNP_IRQ0 | PNP_IRQ1, 0x0fff },
	{ NULL, MEC5055_ACPI_EC1,	 PNP_IO0, 0x0ffc },
	{ NULL, MEC5055_ACPI_EC2,	 PNP_IO0, 0x0ff8 },
	{ NULL, MEC5055_ACPI_EC3,	 PNP_IO0, 0x0ff8 },
	{ NULL, MEC5055_ACPI_EC4,	 PNP_IO0, 0x0ff0 },
	{ NULL, MEC5055_ACPI_EC5,	 PNP_IO0, 0xfffe },
	{ NULL, MEC5055_UART1,		 PNP_IO0 | PNP_IRQ0 | PNP_IDX_MSC0, 0x07ff, 0x07ff },
	{ NULL, MEC5055_UART2,		 PNP_IO0 | PNP_IRQ0 | PNP_IDX_MSC0, 0x07ff, 0x07ff, 0xfff0 },
	{ NULL, MEC5055_LEGACY_FAST_KB,	 PNP_IO0, 0x0fff, },
	{ NULL, MEC5055_EMBEDDED_FLASH,	 PNP_IO0, 0x0ffc },
	{ NULL, MEC5055_EMBEDDED_MEMORY, PNP_IO0, 0x0ff0, },
};

static void enable_dev(struct device *dev)
{
	if (dev->path.type == DEVICE_PATH_PNP) {
		pnp_enable_devices(dev, &ec_pnp_ops, ARRAY_SIZE(pnp_dev_info), pnp_dev_info);
	}
	else {
		printk(BIOS_ERR, "EC: Unknown device type. Check your devicetree!\n");
	}
}

struct chip_operations ec_clevo_it5570e_ops = {
	CHIP_NAME("Dell MEC5055 EC")
	.enable_dev = enable_dev,
};