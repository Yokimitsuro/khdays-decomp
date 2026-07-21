/* Format a centisecond timer into minutes/seconds/centiseconds bytes, clamped to 59:59:99:
 * param_1/1000 = seconds, /60 of that = minutes, /10 = centiseconds.
 *
 * NON-MATCHING (equivalent), size-exact. The magic divisions all reproduce (0xcccccccd>>35 for
 * /10, 0x10624dd3>>38 for /1000, 0x51eb851f>>37 for /100, 0x88888889>>37 for /60 computed twice),
 * and the clamp is `<= 0x3b`. Residue is purely the register allocation of the umull temporaries:
 * the ROM colours the two initial high-word products r4/lr and threads r6/r12/r5 through the mods,
 * while mwcc 139 picks ip/r5/... for the same values, diverging from the first ldr and propagating
 * through every instruction. No source reordering lands on the ROM's colouring. */
void func_ov008_02074258(unsigned int param_1, unsigned char *pMin, unsigned char *pSec, unsigned char *pCs) {
    unsigned int cs = param_1 / 10;
    unsigned int sec = param_1 / 1000;
    unsigned int min = sec / 60;
    *pCs = cs % 100;
    *pSec = sec % 60;
    *pMin = min;
    if ((min & 0xff) <= 0x3b) {
        return;
    }
    *pMin = 0x3b;
    *pSec = 0x3b;
    *pCs = 0x63;
}
