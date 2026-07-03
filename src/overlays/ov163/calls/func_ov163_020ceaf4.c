extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov163_020ced90(void);
extern void func_ov163_020cee34(void);
extern void func_ov163_020cf024(void);
extern void func_ov163_020cf0f4(void);
extern void func_ov163_020cf374(void);
extern void func_ov163_020cf5e4(void);
extern void func_ov163_020cf6d0(void);
extern void func_ov163_020cfd50(void);
extern void func_ov163_020cffe8(void);
extern void func_ov163_020d091c(void);
extern void func_ov163_020d09b8(void);

struct node60 { unsigned short lo : 8, hi : 8; };
struct flagbyte { unsigned int b : 8; };

void func_ov163_020ceaf4(int *node)
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
            func_0203c634(node, 1, func_ov163_020ced90);
            break;
        case 1:
            func_0203c634(node, 1, func_ov163_020cee34);
            break;
        case 2:
            func_0203c634(node, 1, func_ov163_020cf024);
            break;
        case 4:
            func_0203c634(node, 1, func_ov163_020cf0f4);
            break;
        case 9:
            func_0203c634(node, 1, func_ov163_020cf374);
            break;
        case 5:
            func_0203c634(node, 1, func_ov163_020cf5e4);
            break;
        case 6:
            func_0203c634(node, 1, func_ov163_020cf6d0);
            break;
        case 7:
            func_0203c634(node, 1, func_ov163_020cfd50);
            break;
        case 8:
            func_0203c634(node, 1, func_ov163_020cffe8);
            break;
        case 3:
            func_0203c634(node, 1, func_ov163_020d091c);
            break;
        case 10:
            func_0203c634(node, 1, func_ov163_020d09b8);
            break;
        }
    }

    *((signed char *)*(int *)state + 0x1c7) = -1;
}
