/*
 * Copyright (C) STMicroelectronics 2009
 * Copyright (C) ST-Ericsson SA 2010
 *
 * License Terms: GNU General Public License v2
 *	Based on ARM realview platform
 *
 * Author: Sundar Iyer <sundar.iyer@stericsson.com>
 *
 */
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/smp.h>

#include <asm/smp_plat.h>

<<<<<<< HEAD
extern volatile int pen_release;

static inline void platform_do_lowpower(unsigned int cpu)
=======
#include <mach/setup.h>

/*
 * platform-specific code to shutdown a CPU
 *
 * Called with IRQs disabled
 */
void __ref ux500_cpu_die(unsigned int cpu)
>>>>>>> 28e8e29... ARM: consolidate pen_release instead of having per platform definitions
{
<<<<<<< HEAD
	flush_cache_all();

	/* we put the platform to just WFI */
=======
	/* directly enter low power state, skipping secure registers */
>>>>>>> bca7a5a... ARM: cpu hotplug: remove majority of cache flushing from platforms
	for (;;) {
		__asm__ __volatile__("dsb\n\t" "wfi\n\t"
				: : : "memory");
		if (pen_release == cpu_logical_map(cpu)) {
			/*
			 * OK, proper wakeup, we're done
			 */
			break;
		}
	}
}

int platform_cpu_kill(unsigned int cpu)
{
	return 1;
}

/*
 * platform-specific code to shutdown a CPU
 *
 * Called with IRQs disabled
 */
void platform_cpu_die(unsigned int cpu)
{
	/* directly enter low power state, skipping secure registers */
	platform_do_lowpower(cpu);
}

int platform_cpu_disable(unsigned int cpu)
{
	/*
	 * we don't allow CPU 0 to be shutdown (it is still too special
	 * e.g. clock tick interrupts)
	 */
	return cpu == 0 ? -EPERM : 0;
}
