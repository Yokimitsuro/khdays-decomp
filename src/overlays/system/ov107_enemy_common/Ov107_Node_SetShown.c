/* Sets a node's "shown" bit, bit 0 of its state word +0x40 (Ov107_InitNodeBase). */

struct b1 { unsigned int b0 : 1; };
void Ov107_Node_SetShown(int pNode, int bShown)
{
    ((struct b1 *)(pNode + 0x40))->b0 = bShown;
}
