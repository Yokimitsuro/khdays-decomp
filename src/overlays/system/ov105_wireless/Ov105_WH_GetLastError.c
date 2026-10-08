/* WH_GetLastError (wh.c): the last error the helper recorded, sErrCode. */

extern int data_ov105_020c04c0;
int Ov105_WH_GetLastError(void) {
    return *(int *)((char *)&data_ov105_020c04c0 + 0x30);
}
