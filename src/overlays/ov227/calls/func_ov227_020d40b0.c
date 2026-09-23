/* Target pick of an ov227 part: the world's +0xa8 object list is walked twice -- first counting the
 * live objects (bit 1 of +0x40 and bit 0 of the +0x60 low byte), then stopping at the object whose
 * position in the list equals a d(count) roll when that object is live -- leaving the pick in +8.
 * With one, the +0xc velocity takes a random heading within +/-0x3244 at 0.075 and a 0.25 lift,
 * and the owner requests sub-state 1. */
#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

struct Bits40 { int b0 : 1, b1 : 1; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list, int cur);
extern int func_02023eb4(int n);
extern const short data_0203d210[];

void func_ov227_020d40b0(int *part)
{
    int n;
    int i;
    int world = *(int *)(*part + 4);
    int *it;
    int pick;
    int heading;

    it = func_01fffd70((void *)(world + 0xa8));
    part[2] = it == 0 ? 0 : *it;
    n = 0;
    while (part[2] != 0) {
        if (((struct Bits40 *)(part[2] + 0x40))->b1 != 0 && (((struct hw60 *)(part[2] + 0x60))->lo & 1) != 0) {
            n++;
        }
        it = func_01fffd8c((void *)(world + 0xa8), part[2]);
        part[2] = it == 0 ? 0 : *it;
    }
    if (n == 0) {
        return;
    }
    pick = func_02023eb4(n);
    it = func_01fffd70((void *)(world + 0xa8));
    part[2] = it == 0 ? 0 : *it;
    i = 0;
    while (part[2] != 0) {
        if (((struct Bits40 *)(part[2] + 0x40))->b1 != 0 && (((struct hw60 *)(part[2] + 0x60))->lo & 1) != 0
            && i == pick) {
            break;
        }
        it = func_01fffd8c((void *)(world + 0xa8), part[2]);
        part[2] = it == 0 ? 0 : *it;
        i++;
    }
    if (part[2] == 0) {
        return;
    }
    heading = func_02023eb4(0x6489) + -0x3244;
    part[3] = FX_MUL(data_0203d210[ANG2IDX(heading) * 2], 0x133);
    part[5] = FX_MUL(data_0203d210[ANG2IDX(heading) * 2 + 1], 0x133);
    part[4] = 0x400;
    *(unsigned char *)(*part + 0x1c7) = 1;
}
