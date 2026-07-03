extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov165_020d29d0(void);
extern void func_ov165_020d2a74(void);
extern void func_ov165_020d2c64(void);
extern void func_ov165_020d2d34(void);
extern void func_ov165_020d2fb4(void);
extern void func_ov165_020d3224(void);
extern void func_ov165_020d3310(void);
extern void func_ov165_020d3990(void);
extern void func_ov165_020d3c28(void);
extern void func_ov165_020d455c(void);
extern void func_ov165_020d45f8(void);

struct node60 { unsigned short lo : 8, hi : 8; };
struct flagbyte { unsigned int b : 8; };

void func_ov165_020d2734(int *node)
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
            func_0203c634(node, 1, func_ov165_020d29d0);
            break;
        case 1:
            func_0203c634(node, 1, func_ov165_020d2a74);
            break;
        case 2:
            func_0203c634(node, 1, func_ov165_020d2c64);
            break;
        case 4:
            func_0203c634(node, 1, func_ov165_020d2d34);
            break;
        case 9:
            func_0203c634(node, 1, func_ov165_020d2fb4);
            break;
        case 5:
            func_0203c634(node, 1, func_ov165_020d3224);
            break;
        case 6:
            func_0203c634(node, 1, func_ov165_020d3310);
            break;
        case 7:
            func_0203c634(node, 1, func_ov165_020d3990);
            break;
        case 8:
            func_0203c634(node, 1, func_ov165_020d3c28);
            break;
        case 3:
            func_0203c634(node, 1, func_ov165_020d455c);
            break;
        case 10:
            func_0203c634(node, 1, func_ov165_020d45f8);
            break;
        }
    }

    *((signed char *)*(int *)state + 0x1c7) = -1;
}
