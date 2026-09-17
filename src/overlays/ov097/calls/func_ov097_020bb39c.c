/* Per-frame step of this enemy's three 0x110-byte projectile slots (from +0x330 of the part
 * block), then, while the enemy is in state 0x30, fire the volley that its progress counter has
 * just reached: every 0x6000 of progress selects a launch angle (0x5fff at 0x2a000; 0x1e000
 * launches straight ahead with the spread flag cleared). Progress values between the marks do
 * nothing. */
extern void func_ov097_020bb64c(char *self, char *slot, void *arg);
extern void func_ov097_020bb484(char *self, char *parts, int angle, int spread);

void func_ov097_020bb39c(char *self, char *parts, void *arg)
{
    int progress;
    int hit;
    int spread;
    int angle;
    int i;
    char *slot;

    slot = parts + 0x330;
    for (i = 0; i < 3; i++) {
        func_ov097_020bb64c(self, slot, arg);
        slot += 0x110;
    }
    if (*(int *)(self + 0x6bc) != 0x30) {
        return;
    }
    progress = *(int *)(self + 0x7b0);
    hit = 0;
    spread = 1;
    switch (progress) {
    case 0x6000:
        hit = 1;
        angle = 0x51c6;
        break;
    case 0xc000:
        hit = 1;
        angle = 0xf555;
        break;
    case 0x12000:
        hit = 1;
        angle = 0xaaaa;
        break;
    case 0x1e000:
        hit = 1;
        angle = 0;
        spread = 0;
        break;
    case 0x2a000:
        hit = 1;
        angle = 0x5fff;
        break;
    }
    if (hit) {
        func_ov097_020bb484(self, parts, angle, spread);
    }
}
