extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov133_020d298c(void);
extern void func_ov133_020d2a30(void);
extern void func_ov133_020d2c20(void);
extern void func_ov133_020d2cf0(void);
extern void func_ov133_020d2f70(void);
extern void func_ov133_020d31e0(void);
extern void func_ov133_020d32cc(void);
extern void func_ov133_020d394c(void);
extern void func_ov133_020d3b48(void);
extern void func_ov133_020d4454(void);
extern void func_ov133_020d451c(void);

struct node60 { unsigned short lo : 8, hi : 8; };
struct flagbyte { unsigned int b : 8; };

void func_ov133_020d26f0(int *node)
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
            func_0203c634(node, 1, func_ov133_020d298c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov133_020d2a30);
            break;
        case 2:
            func_0203c634(node, 1, func_ov133_020d2c20);
            break;
        case 4:
            func_0203c634(node, 1, func_ov133_020d2cf0);
            break;
        case 9:
            func_0203c634(node, 1, func_ov133_020d2f70);
            break;
        case 5:
            func_0203c634(node, 1, func_ov133_020d31e0);
            break;
        case 6:
            func_0203c634(node, 1, func_ov133_020d32cc);
            break;
        case 7:
            func_0203c634(node, 1, func_ov133_020d394c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov133_020d3b48);
            break;
        case 3:
            func_0203c634(node, 1, func_ov133_020d4454);
            break;
        case 10:
            func_0203c634(node, 1, func_ov133_020d451c);
            break;
        }
    }

    *((signed char *)*(int *)state + 0x1c7) = -1;
}
