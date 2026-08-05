/*
 * func_ov002_020766e0 - record a hit against an array element and test its result (ARM).
 *
 * Copies the element's tag byte into rec[1], derives the element's index within its owning array
 * (byte offset from the array base divided by the element size, via func_02020400) and stores it
 * into rec[2]. Then submits the record with tag 5 through func_02031384, returning 1 when the
 * returned id is a real value (not the 0xffff sentinel), 0 otherwise.
 */
typedef struct {
    char _0[0x11];
    unsigned char tag;          /* +0x11 */
} Ov002Elem;

typedef struct {
    char _0[0x4e];
    unsigned short elemSize;    /* +0x4e */
    char _50[0x54 - 0x50];
    int arrayBase;              /* +0x54 */
} Ov002Owner;

extern int func_02020400(int numer, int denom);
extern int func_02031384(int tag, int record, int arg);

int func_ov002_020766e0(Ov002Elem *elem, unsigned char *rec, int param_3)
{
    Ov002Owner *owner;
    rec[1] = elem->tag;
    owner = *(Ov002Owner **)((char *)elem + 8);
    *(unsigned short *)(rec + 2) = func_02020400((int)elem - owner->arrayBase, owner->elemSize);
    return func_02031384(5, (int)rec, (unsigned short)param_3) != 0xffff;
}
