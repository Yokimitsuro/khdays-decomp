/* Tick of the ov248 actor's release step: unless bit 0 of the +0x60 low byte is set, the +0x394 node
 * is unlinked from the +0x3c list and cleared; then the base tick runs. */
typedef struct { unsigned short lo : 8; unsigned short hi : 8; } Flags60;

extern void func_0203c650(int list, int node);
extern void func_ov107_020c7ca4(int obj);

void func_ov248_020d0534(int self)
{
    if (!(((Flags60 *)(self + 0x60))->lo & 1) && *(int *)(self + 0x394) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x394));
        *(int *)(self + 0x394) = 0;
    }
    func_ov107_020c7ca4(self);
}
