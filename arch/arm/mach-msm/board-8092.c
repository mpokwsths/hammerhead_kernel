/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/of_fdt.h>
#include <linux/of_irq.h>
#include <asm/hardware/gic.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>
#include <mach/socinfo.h>
#include <mach/board.h>
#include <mach/msm_memtypes.h>
#include <mach/qpnp-int.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/irqdomain.h>
#include <mach/clk-provider.h>

#include "board-dt.h"
#include "clock.h"
#include "platsmp.h"

#define MPQ8092_MAC_FUSE_PHYS     0xfc4bc0e0
#define MPQ8092_MAC_FUSE_SIZE     0x10

static const char mac_addr_prop_name[] = "mac-address";

static void __init mpq8092_dt_reserve(void)
{
	of_scan_flat_dt(dt_scan_for_memory_reserve, NULL);
}

static void __init mpq8092_map_io(void)
{
	msm_map_mpq8092_io();
}

static struct of_dev_auxdata mpq8092_auxdata_lookup[] __initdata = {
	OF_DEV_AUXDATA("qcom,msm-lsuart-v14", 0xF991F000, \
			"msm_serial_hsl.0", NULL),
	OF_DEV_AUXDATA("qcom,msm-sdcc", 0xF9824000, \
			"msm_sdcc.1", NULL),
	OF_DEV_AUXDATA("qcom,msm-sdcc", 0xF98A4000, \
			"msm_sdcc.2", NULL),
	{}
};

static void __init mpq8092_init(void)
{
	struct of_dev_auxdata *adata = mpq8092_auxdata_lookup;

	if (socinfo_init() < 0)
		pr_err("%s: socinfo_init() failed\n", __func__);

	mpq8092_init_gpiomux();
	msm_clock_init(&mpq8092_clock_init_data);
	board_dt_populate(adata);
}

static const char *mpq8092_dt_match[] __initconst = {
	"qcom,mpq8092-sim",
	NULL
};

DT_MACHINE_START(MSM8092_DT,
		"Qualcomm Technologies, Inc. MSM 8092 (Flattened Device Tree)")
	.map_io			= mpq8092_map_io,
	.init_machine		= mpq8092_init,
	.dt_compat		= mpq8092_dt_match,
	.reserve		= mpq8092_dt_reserve,
	.smp			= &msm8974_smp_ops,
MACHINE_END
