/* Ends the asynchronous archive command with status 5 when the ROM thread is still
 * available, otherwise with 0. */
extern int OS_IsThreadAvailable_0x0200f274(void);
extern void FS_NotifyArchiveAsyncEnd(void *arc, int status);

void FSi_OnRomReadDone(void *arc) {
    int status = OS_IsThreadAvailable_0x0200f274() != 0 ? 5 : 0;
    FS_NotifyArchiveAsyncEnd(arc, status);
}
