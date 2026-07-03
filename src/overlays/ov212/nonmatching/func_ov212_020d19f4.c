/*
 * func_ov212_020d19f4 — per-frame linear fade of a child list (menu/effect element).
 *
 * state = param_1[1]; timer = state[2]. While 0 < timer <= 0x1800, advance the
 * timer by *(*param_1 + 0x2c) and scale every child's field [+4] by the ramp
 * (0x1800 - timer)/0x1800 (children: count at (*state)[0x8c], base (*state)[0x90],
 * stride 0x38). Once timer passes 0x1800 the child field is forced to 0.
 *
 * NON-MATCHING: equivalent semantics, but a register-coloring tie blocks a
 * byte-exact match. The original materializes the loop counter i=0 into the
 * register just freed by param_1 (r0), scheduling the delta load through r2 to
 * keep r0 live; mwcc spends r0 as the delta scratch and colors i/off/child into
 * r4/r5/r6 instead of r0/r6/r5. Same class as the documented scheduler/coloring
 * ties (no source form flips which dead reg the counter reuses). Also affects the
 * 3 byte-identical siblings func_ov210_*, func_ov212_020d1b18-class (160B x4).
 */
void func_ov212_020d19f4(int *param_1)
{
    int *state = (int *)param_1[1];
    int timer = state[2];
    if (timer == 0)
        return;
    if (timer > 0x1800)
        return;
    state[2] = timer + *(int *)(*param_1 + 0x2c);
    if (0 < *(int *)(*state + 0x8c)) {
        int i = 0;
        int off = 0;
        do {
            int child = *(int *)(*state + 0x90) + off;
            int v;
            if (state[2] > 0x1800)
                v = 0;
            else
                v = *(int *)(child + 4) * (0x1800 - state[2]) / 0x1800;
            *(int *)(child + 4) = v;
            i = i + 1;
            off = off + 0x38;
        } while (i < *(int *)(*state + 0x8c));
    }
}
