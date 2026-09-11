typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed char s8;

typedef struct {
    u8 pad_00[2];
    u8 flag;       /* +2 */
    u8 pad_03;     /* +3 */
    u8 field_04;   /* +4 */
    s8 field_05;   /* +5 */
    u16 vx;        /* +6 */
    u16 vy;        /* +8 */
    u16 vz;        /* +0xa */
    u16 field_0c;  /* +0xc */
    s16 field_0e;  /* +0xe */
    s16 field_10;  /* +0x10 */
    s16 field_12;  /* +0x12 */
    u8 packed[9];  /* +0x14..0x1c */
    u8 field_1d;   /* +0x1d */
    u16 field_1e;  /* +0x1e */
    u8 field_20;   /* +0x20 */
    u8 field_21;   /* +0x21 */
    s16 field_22;  /* +0x22 */
} Msg;

typedef struct {
    int pad0;
    int pad4;
    unsigned int flags : 8;
} ListItem;

extern void MI_CpuFill8(void *dst, int value, int size);
extern int func_01fffd70(void *listObj);
extern int func_01fffd8c(int *listObj);
extern void func_ov107_020c4bf0(int self, Msg *msg, int arg);

void func_ov107_020c7a90(int self, Msg *msg, int arg3)
{
    if (msg->flag == 0) {
        int *node;
        int i;

        if (*(int *)(self + 0x30c) != 1) {
            return;
        }

        msg->field_1e = *(u16 *)(self + 0x1ae);
        MI_CpuFill8(&msg->field_20, 0, 2);

        i = 0;
        node = (int *)func_01fffd70((void *)(self + 0x22c));
        if (node != 0) {
            do {
                if (((ListItem *)node)->flags & 1) {
                    msg->field_20 |= (1 << i);
                }
                if (((ListItem *)node)->flags & 2) {
                    msg->field_21 |= (1 << i);
                }
                i++;
                node = (int *)func_01fffd8c((int *)(self + 0x22c));
            } while (node != 0);
        }

        msg->field_22 = *(s16 *)(self + 0x21a);
        msg->field_05 = *(s8 *)(self + 0x1c6);
        msg->field_1d = *(u8 *)(self + 0x1c5);
    }

    func_ov107_020c4bf0(self, msg, arg3);
}
