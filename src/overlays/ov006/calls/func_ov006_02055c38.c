/* func_ov006_02055c38 -- title: switch the 3D title model to pose `pose`.
 * Only acts when the pose actually changes (OBJ+0x94f0 caches the current one): restarts the
 * two tweens at OBJ+0x9574 and OBJ+0x9590 over 300 frames -- one ramping to 0x10000, the other
 * running mode 2 down from 0xa000. Returns 0 if the title object is gone. */
extern void func_02035fb0(int *tween, int a, int b, int target, int frames);
extern void func_02035ffc(int tween);
extern int *data_ov006_02056664;

int func_ov006_02055c38(int pose) {
    int *obj = data_ov006_02056664;
    if (obj == 0) {
        return 0;
    }
    if (*(int *)((char *)obj + 0x94f0) != pose) {
        func_02035fb0((int *)((char *)obj + 0x9574), 0, 0, 0x10000, 300);
        func_02035ffc((int)((char *)data_ov006_02056664 + 0x9574));
        func_02035fb0((int *)((char *)data_ov006_02056664 + 0x9590), 2, 0xa000, 0, 300);
        func_02035ffc((int)((char *)data_ov006_02056664 + 0x9590));
        *(int *)((char *)data_ov006_02056664 + 0x94f0) = pose;
    }
    return 1;
}
