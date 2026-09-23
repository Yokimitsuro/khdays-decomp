/* Move dispatcher of the ov254 actor: +0x4dc is set and, while moving (+0x60 bit 0), the ground
 * under the +8 track is probed (020ccfd4); on solid ground (3) its height goes to +0x4d4. A pending
 * move (+0x1c7) becomes current: bits 1-3 and 7 of the +0x60 high byte and bits 0-1 of +0x1ae
 * clear (bit 3 back on with a rider, +0x78), the +0x468 shell is recalled (020d419c) unless in
 * move 7, the five +0x3e0 shapes lose bit 0 and gain bit 1, +0x3e0 / +0x3e4 regain bit 0 (+0x3e0
 * keeps bit 1 only with a rider), the +0x460 / +0x464 helpers stop and the move's handler takes
 * slot 1. While moving: in moves 2 and 4 with a rider above the floor less 7.7 the +0x3f0 shape
 * gains bit 0 and loses bit 1; in move 0xa without a rider bit 3 of the +0x60 high byte follows
 * the solid ground. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct Hw60 { u16 lo : 8; u16 hi : 8; };
typedef struct { unsigned f : 8; } B8;
struct Shapes3e0 { char pad[0x3e0]; int shape[5]; };

extern int func_ov254_020ccfd4(int *self, Vec3 pos, int *outY);
extern void func_ov254_020d419c(int shell);
extern void func_ov254_020d4d34(int helper);
extern void func_ov254_020d532c(int helper);
extern void func_0203c634(int *node, int slot, void (*cb)(void));
extern void func_ov254_020ce488(void);
extern void func_ov254_020ce5d0(void);
extern void func_ov254_020ce668(void);
extern void func_ov254_020cef2c(void);
extern void func_ov254_020d05c4(void);
extern void func_ov254_020d0a5c(void);
extern void func_ov254_020d0c28(void);
extern void func_ov254_020d109c(void);
extern void func_ov254_020d1104(void);
extern void func_ov254_020d1698(void);
extern void func_ov254_020d184c(void);

void func_ov254_020cdccc(int *node)
{
    int *state = (int *)node[1];
    int ground = -1;
    int moving;
    int y;
    int i;

    moving = ((struct Hw60 *)(*state + 0x60))->lo & 1;
    *(int *)(*state + 0x4dc) = 1;
    if (moving) {
        y = 0;
        ground = func_ov254_020ccfd4(state, *(Vec3 *)state[2], &y);
        if (ground != -1 && ground != 1 && ground == 3) {
            *(int *)(*state + 0x4d4) = y;
            *(int *)(*state + 0x4dc) = 1;
        }
    }
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        ((struct Hw60 *)(*state + 0x60))->hi &= ~0x8e;
        *(u16 *)(*state + 0x100 + 0xae) &= ~3;
        if (state[0x1e] != 0) {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 8) << 0x18) >> 0x10);
        }
        if (*(int *)(*(int *)(*state + 0x468) + 0x388) != 0 && *(signed char *)(*state + 0x100 + 0xc6) != 7) {
            func_ov254_020d419c(*(int *)(*state + 0x468));
        }
        for (i = 0; i < 5; i++) {
            ((B8 *)(((struct Shapes3e0 *)*state)->shape[i] + 8))->f &= ~1;
            ((B8 *)(((struct Shapes3e0 *)*state)->shape[i] + 8))->f |= 2;
        }
        ((B8 *)(*(int *)(*state + 0x3e0) + 8))->f |= 1;
        ((B8 *)(*(int *)(*state + 0x3e4) + 8))->f |= 1;
        if (state[0x1e] == 0) {
            ((B8 *)(*(int *)(*state + 0x3e0) + 8))->f &= ~2;
        }
        func_ov254_020d4d34(*(int *)(*state + 0x460));
        func_ov254_020d532c(*(int *)(*state + 0x464));
        switch (*(signed char *)(*state + 0x100 + 0xc6)) {
        case 0:
            func_0203c634(node, 1, func_ov254_020ce488);
            break;
        case 2:
            func_0203c634(node, 1, func_ov254_020ce5d0);
            break;
        case 4:
            func_0203c634(node, 1, func_ov254_020ce668);
            break;
        case 5:
            func_0203c634(node, 1, func_ov254_020cef2c);
            break;
        case 6:
            func_0203c634(node, 1, func_ov254_020d05c4);
            break;
        case 7:
            func_0203c634(node, 1, func_ov254_020d0a5c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov254_020d0c28);
            break;
        case 9:
            func_0203c634(node, 1, func_ov254_020d109c);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov254_020d1104);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov254_020d1698);
            break;
        case 3:
            func_0203c634(node, 1, func_ov254_020d184c);
            break;
        }
        *(signed char *)(*state + 0x1c7) = -1;
    }
    if (!moving) {
        return;
    }
    switch (*(signed char *)(*state + 0x100 + 0xc6)) {
    case 2:
    case 4:
        if (state[0x1e] == 0) {
            return;
        }
        if (*(int *)(state[2] + 4) < *(int *)(*state + 0x4d4) - 0x7b31) {
            return;
        }
        ((B8 *)(*(int *)(*state + 0x3f0) + 8))->f |= 1;
        ((B8 *)(*(int *)(*state + 0x3f0) + 8))->f &= ~2;
        break;
    case 0xa:
        if (state[0x1e] != 0) {
            return;
        }
        if (ground == 3) {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 8) << 0x18) >> 0x10);
        } else {
            ((struct Hw60 *)(*state + 0x60))->hi &= ~8;
        }
        break;
    }
}
