/* Advance a pending request: a live request (+0) is dropped once the owner's +0x6bc counter
 * reaches 0x30; while it reads exactly 1 both halves (+4 and +0x10c) are stepped. */
extern int func_0202a818(void *arg0, int arg1);
void func_ov043_020b50ac(char *owner, int *req, int arg) {
    if (*req != 0 && *(int *)(owner + 0x6bc) != 0x30) {
        *req = 0;
    }
    if (*req != 1) return;
    func_0202a818((char *)req + 4, arg);
    func_0202a818((char *)req + 0x10c, arg);
}
