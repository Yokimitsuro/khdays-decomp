/* Draw hook of the ov276 enemy: releases the +0x470 item, runs the base draw and then anchors
 * the +0x474 point either at the +0x3d0 spot or, while bit 7 of the +0x60 flag is set, at the
 * +0xb0 position raised by 0x10cc; the +0x480 word takes the overlay constant. */
typedef struct Vec3 { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov107_020c9ec8(int item);
extern void func_ov107_020c6980(int actor, int arg);

void func_ov276_020d0118(int actor, int arg)
{
    func_ov107_020c9ec8(*(int *)(actor + 0x470));
    func_ov107_020c6980(actor, arg);
    if ((((struct hw60 *)(actor + 0x60))->lo & 0x80) != 0) {
        *(Vec3 *)(actor + 0x474) = *(Vec3 *)(actor + 0xb0);
        *(int *)(actor + 0x478) += 0x10cc;
    } else {
        *(Vec3 *)(actor + 0x474) = *(Vec3 *)(actor + 0x3d0);
    }
    *(int *)(actor + 0x480) = 0x10cc;
}
