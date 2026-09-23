/* Effect message hook of the ov119 enemy (x3 with ov272/ov279). A "spawned" message (kind 5) picks
 * by byte 3: slots 0/1 spawn pair 2 (kind 0x15) at the packed position (bytes 5..) and, clearing
 * (slot 0) or raising (slot 1) bit 4 of +0x1ae, restart the +0x3a4 aura (func_ov119_020cf7b0 with
 * the slot); slot 2 spawns pair 1 (kind 5) at the packed position; slot 3 spawns pair 4 on the
 * +0xa0 pose and starts reaction 0x121 mode 6 there into +0x3b0; slot 4 anchors pair 3 on the pose
 * (looping). The base hook always runs. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Pair { int res; int handle; };

extern int func_ov107_020c08cc(int model, int res, int kind, int arg, int scale, void *pos);
extern int func_ov107_020c0794(int model, int res, int kind, int zero, void *t);
extern int func_ov107_020c09a0(int model, int res, int kind, void *at, int a, int b);
extern int func_ov107_020cb040(char *self, int id, int mode, int flag, void *pose);
extern int func_ov119_020cf7b0(char *self, int on);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov119_020cc3a8(char *self, u8 *msg, int arg)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
        case 1:
            (*(struct Pair **)(self + 0x3a8))[2].handle =
                func_ov107_020c08cc(*(int *)(self + 0x3c), (*(struct Pair **)(self + 0x3a8))[2].res, 0x15, 0, 0x1000, msg + 5);
            if (msg[3] == 0) {
                *(u16 *)(self + 0x1ae) &= ~0x10;
                *(int *)(self + 0x3a4) = func_ov119_020cf7b0(self, 0);
            } else {
                *(u16 *)(self + 0x1ae) |= 0x10;
                *(int *)(self + 0x3a4) = func_ov119_020cf7b0(self, 1);
            }
            break;
        case 2:
            (*(struct Pair **)(self + 0x3a8))[1].handle =
                func_ov107_020c08cc(*(int *)(self + 0x3c), (*(struct Pair **)(self + 0x3a8))[1].res, 5, 0, 0x1000, msg + 5);
            break;
        case 3:
            (*(struct Pair **)(self + 0x3a8))[4].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Pair **)(self + 0x3a8))[4].res, 5, 0, self + 0xa0);
            *(int *)(self + 0x3b0) = func_ov107_020cb040(self, 0x121, 6, 0, self + 0xa0);
            break;
        case 4:
            (*(struct Pair **)(self + 0x3a8))[3].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Pair **)(self + 0x3a8))[3].res, 5, self + 0xa0, 0, 1);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
