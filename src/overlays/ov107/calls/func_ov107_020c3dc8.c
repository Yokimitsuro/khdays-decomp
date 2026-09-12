/* func_ov107_020c3dc8 -- roll the node's 12-byte transform history forward
 * (0xfc -> 0x108, 0xcc -> 0xfc), accumulate the offset at 0xe4 into the new
 * 0xfc slot, reset 0xe4 to its default, snapshot 0xfc into 0x16c, and clear
 * the reset/dirty flag bits. */
typedef struct { int w[3]; } Blk12;

extern void VEC_Add(int *a, int *b, int *out);
extern int data_02041dc8[3];

typedef struct {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
} Flags17a;

typedef struct {
    char pad_00[0xcc];
    Blk12 f_cc;       /* +0xcc */
    char pad_d8[0xc];
    Blk12 f_e4;       /* +0xe4 */
    char pad_f0[0xc];
    Blk12 f_fc;       /* +0xfc */
    Blk12 f_108;      /* +0x108 */
    char pad_114[0x58];
    Blk12 f_16c;      /* +0x16c */
    unsigned char byte_178;
    char pad_179[1];
    Flags17a f_17a;   /* +0x17a */
} Node;

void func_ov107_020c3dc8(int self)
{
    Node *n = (Node *)self;
    n->f_108 = n->f_fc;
    n->f_fc = n->f_cc;
    VEC_Add((int *)&n->f_fc, (int *)&n->f_e4, (int *)&n->f_fc);
    n->f_e4 = *(Blk12 *)data_02041dc8;
    n->f_16c = n->f_fc;
    n->byte_178 = 0;
    n->f_17a.bit4 = 0;
    n->f_17a.bit0 = 0;
    n->f_17a.bit2 = 0;
}
