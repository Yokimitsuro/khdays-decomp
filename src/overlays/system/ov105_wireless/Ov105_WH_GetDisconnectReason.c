/* The reason of the first disconnection the helper saw (its statics' +0xc). */

/* Read the u16 field at (&data_ov105_020c04c0 + 0xc). */
extern int data_ov105_020c04c0;
int Ov105_WH_GetDisconnectReason(void) {
    return *(unsigned short *)((char *)&data_ov105_020c04c0 + 0xc);
}
