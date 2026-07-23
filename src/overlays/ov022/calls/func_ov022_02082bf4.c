/* func_ov022_02082bf4 -- battle-scene poll: decide whether to advance to the 02082c54 step.
 * Two paths, chosen by bit 2 of the scene's flags halfword:
 *  - set: ask func_02021054 about the sub-object at +0x2c and then run the "any player"
 *    (-1) input check; on success run the transition hook.
 *  - clear: close the current panel and run the input check for either the local player
 *    (func_01fffe14) or any player, depending on bit 2 of data_0204c240.
 * Returns the next step function, or 0 to stay.
 *
 * data_0204c240 is read as a BYTE (ldrb). The `arg = -1` arm is written second so it stays
 * out of line: the ROM reuses the `movs r0,#4` mask register and reaches -1 with
 * `subs r0,r0,#5`, which only happens when that arm is the branch target. */
extern int func_02021054(int arg0);
extern int func_ov002_0206b5a0(int arg0);
extern void func_ov002_02071b10(void);
extern void func_ov022_02083c08(int arg0);
extern int func_01fffe14(void);
extern int data_ov022_020b2e60;
extern void func_ov022_02082c54(void);
extern unsigned char data_0204c240;

int func_ov022_02082bf4(void) {
    int ret = 0;
    if ((*(unsigned short *)*(int *)&data_ov022_020b2e60 & 4) != 0) {
        if (func_02021054(*(int *)(*(int *)&data_ov022_020b2e60 + 0x2c)) != 0 &&
            func_ov002_0206b5a0(-1) != 0) {
            ret = (int)func_ov022_02082c54;
            func_ov002_02071b10();
        }
    } else {
        int arg;
        func_ov022_02083c08(0);
        if ((data_0204c240 & 4) != 0) {
            arg = func_01fffe14();
        } else {
            arg = -1;
        }
        if (func_ov002_0206b5a0(arg) != 0) {
            ret = (int)func_ov022_02082c54;
        }
    }
    return ret;
}
