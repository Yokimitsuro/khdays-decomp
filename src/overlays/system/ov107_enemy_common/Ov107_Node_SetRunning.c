/* Sets a node's "running" bit, bit 1 of its state word +0x40 (Ov107_InitNodeBase):
 * Ov107_Region_TickChildren ticks only the running members, and a region sets the bit on its
 * members only when it is enabled (Ov107_Region_SetEnabled, called by Ov107_Region_AddMember when a
 * player joins it). A spawner made after its region's players joined never runs. */

struct b2 { unsigned int b0 : 1, b1 : 1; };
void Ov107_Node_SetRunning(int pNode, int bRunning)
{
    ((struct b2 *)(pNode + 0x40))->b1 = bRunning;
}
