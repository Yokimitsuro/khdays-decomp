/* Configuration of the ov144 enemy (and its byte-identical twin) from a spawn record: releases
 * the previous +0x39c waypoint list, copies the record's +0x4c waypoints (16 bytes each, when
 * there are at least two) into a fresh allocation, and stores the count (+0x3b8), the +0/+4
 * ids (+0x3a4/+0x3a8), the +8 piece (+0x3ec), the +0xc angle converted from 360ths to 0x6488
 * units (+0x3e8), the +0x10 size class (+0x3bc), the +0x3c vector (+0x3ac) and the five
 * +0x28/+0x14 pairs (+0x3c0/+0x3d4). */
struct Vecx32 { int x, y, z; };

extern void func_0203d194(void *block);
extern void *func_0203d15c(int size);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void func_ov145_020ce2ac(char *actor, int a, int *rec)
{
    int i;

    if (*(void **)(actor + 0x39c) != 0) {
        func_0203d194(*(void **)(actor + 0x39c));
        *(void **)(actor + 0x39c) = 0;
    }
    if (rec[0x12] >= 2) {
        *(void **)(actor + 0x39c) = func_0203d15c(rec[0x12] << 4);
        MI_CpuCopy8(rec + 0x13, *(void **)(actor + 0x39c), rec[0x12] << 4);
    }
    *(int *)(actor + 0x3b8) = rec[0x12];
    *(int *)(actor + 0x3a4) = rec[0];
    *(int *)(actor + 0x3a8) = rec[1];
    *(int *)(actor + 0x3ec) = rec[2];
    *(int *)(actor + 0x3e8) = rec[3] * 0x6488 / 360;
    *(int *)(actor + 0x3bc) = rec[4];
    *(struct Vecx32 *)(actor + 0x3ac) = *(struct Vecx32 *)(rec + 0xf);
    for (i = 0; i < 5; i++) {
        ((int *)(actor + 0x3c0))[i] = rec[10 + i];
        ((int *)(actor + 0x3d4))[i] = rec[5 + i];
    }
}
