#ifndef __INCLUDE_LINUX_OOM_H
#define __INCLUDE_LINUX_OOM_H

/*
 * /proc/<pid>/oom_adj is deprecated, see
 * Documentation/feature-removal-schedule.txt.
 *
 * /proc/<pid>/oom_adj set to -17 protects from the oom-killer
 */
#define OOM_DISABLE (-17)
/* inclusive */
#define OOM_ADJUST_MIN (-16)
#define OOM_ADJUST_MAX 15

/*
 * /proc/<pid>/oom_score_adj set to OOM_SCORE_ADJ_MIN disables oom killing for
 * pid.
 */
#define OOM_SCORE_ADJ_MIN	(-1000)
#define OOM_SCORE_ADJ_MAX	1000

#ifdef __KERNEL__

#include <linux/sched.h>
#include <linux/types.h>
#include <linux/nodemask.h>

struct zonelist;
struct notifier_block;
struct mem_cgroup;
struct task_struct;

/*
 * Types of limitations to the nodes from which allocations may occur
 */
enum oom_constraint {
	CONSTRAINT_NONE,
	CONSTRAINT_CPUSET,
	CONSTRAINT_MEMORY_POLICY,
	CONSTRAINT_MEMCG,
};

extern void compare_swap_oom_score_adj(int old_val, int new_val);
extern int test_set_oom_score_adj(int new_val);

extern struct mutex oom_lock;

extern void mark_oom_victim(struct task_struct *tsk);

extern void unmark_oom_victim(void);

extern int oom_kills_count(void);
extern void note_oom_kill(void);

extern unsigned int oom_badness(struct task_struct *p, struct mem_cgroup *memcg,
			const nodemask_t *nodemask, unsigned long totalpages);

extern bool out_of_memory(struct zonelist *zonelist, gfp_t gfp_mask,
		int order, nodemask_t *mask, bool force_kill);
extern int register_oom_notifier(struct notifier_block *nb);
extern int unregister_oom_notifier(struct notifier_block *nb);

extern bool oom_killer_disabled;
extern bool oom_killer_disable(void);
extern void oom_killer_enable(void);

extern struct task_struct *find_lock_task_mm(struct task_struct *p);

extern void dump_tasks(const struct mem_cgroup *memcg,
		const nodemask_t *nodemask);

/* sysctls */
extern int sysctl_oom_dump_tasks;
extern int sysctl_oom_kill_allocating_task;
extern int sysctl_panic_on_oom;
#endif /* __KERNEL__*/
#endif /* _INCLUDE_LINUX_OOM_H */
