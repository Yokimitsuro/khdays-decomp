/* Runs one step of the script scheduler (func_02032f5c) and reports whether it is idle (not in
 * state 1, func_020335a4). */
#pragma thumb on
extern void func_02032f5c(void);
extern int func_020335a4(void);

enum { SCHED_BUSY = 0, SCHED_IDLE = 1 };

int func_02022448(void)
{
    func_02032f5c();
    return func_020335a4() != 0 ? SCHED_BUSY : SCHED_IDLE;
}
