extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov162_020cf2ec(void);
extern void func_ov162_020cf390(void);
extern void func_ov162_020cf580(void);
extern void func_ov162_020cf650(void);
extern void func_ov162_020cf8d0(void);
extern void func_ov162_020cfb40(void);
extern void func_ov162_020cfc2c(void);
extern void func_ov162_020d02b0(void);
extern void func_ov162_020d05f8(void);
extern void func_ov162_020d0f30(void);
extern void func_ov162_020d0fcc(void);

struct node60 { unsigned short lo : 8, hi : 8; };
struct flagbyte { unsigned int b : 8; };

void func_ov162_020cf050(int *node)
{
    int *state = (int *)node[1];
    int *obj = (int *)*state;

    if ((signed char)*((char *)obj + 0x100 + 0xc7) != -1) {
        ((struct node60 *)((char *)obj + 0x60))->hi &= ~0xce;

        *(unsigned short *)((char *)*(int *)state + 0x100 + 0xae) &= ~1;

        ((struct flagbyte *)((char *)*(int *)((char *)*(int *)state + 0x388) + 8))->b |= 1;

        {
            int *o = (int *)*state;
            *((signed char *)o + 0x1c6) = (signed char)*((char *)o + 0x100 + 0xc7);
        }

        switch ((signed char)*((char *)*(int *)state + 0x100 + 0xc6)) {
        case 0:
            func_0203c634(node, 1, func_ov162_020cf2ec);
            break;
        case 1:
            func_0203c634(node, 1, func_ov162_020cf390);
            break;
        case 2:
            func_0203c634(node, 1, func_ov162_020cf580);
            break;
        case 4:
            func_0203c634(node, 1, func_ov162_020cf650);
            break;
        case 9:
            func_0203c634(node, 1, func_ov162_020cf8d0);
            break;
        case 5:
            func_0203c634(node, 1, func_ov162_020cfb40);
            break;
        case 6:
            func_0203c634(node, 1, func_ov162_020cfc2c);
            break;
        case 7:
            func_0203c634(node, 1, func_ov162_020d02b0);
            break;
        case 8:
            func_0203c634(node, 1, func_ov162_020d05f8);
            break;
        case 3:
            func_0203c634(node, 1, func_ov162_020d0f30);
            break;
        case 10:
            func_0203c634(node, 1, func_ov162_020d0fcc);
            break;
        }
    }

    *((signed char *)*(int *)state + 0x1c7) = -1;
}
