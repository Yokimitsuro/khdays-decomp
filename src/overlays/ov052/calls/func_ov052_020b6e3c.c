/* Message handler of the ov032 enemy (and its byte-identical twins): forwards the message to the
 * +0x2644 item and its +0x30 sub-item, runs the overlay's own handling (46e4) and, on the local
 * player's session only, mirrors the item's +0x18 owner byte into bit 27 of the 64-bit flag
 * word (set for owner 0, cleared otherwise) and into the shared byte at +0x110 of 0204c3d8. */
extern void func_ov022_0209145c(int item, int msg);
extern void func_ov052_020b6ee4(int obj);
extern void func_ov002_0205de40(int owner);
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern char data_0204c3d8[];

void func_ov052_020b6e3c(int obj, int msg)
{
    int owner;

    func_ov022_0209145c(*(int *)(obj + 0x2644), msg);
    func_ov022_0209145c(*(int *)(obj + 0x2644) + 0x30, msg);
    func_ov052_020b6ee4(obj);
    owner = *(unsigned char *)(*(int *)(obj + 0x2644) + 0x18);
    func_ov002_0205de40(owner);
    if (func_02030788() == 0) {
        if (owner <= 0) {
            *(unsigned long long *)obj |= 0x8000000LL;
        } else {
            *(unsigned long long *)obj &= ~0x8000000LL;
        }
    }
    data_0204c3d8[0x110] = (char)owner;
}
