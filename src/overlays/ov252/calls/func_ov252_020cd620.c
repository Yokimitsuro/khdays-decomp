/* Record the ov252 actor's +0x310 slot byte for armour piece `which` (+0x39c) and fetch the other three
 * pieces' records from its +0x384 model's +0x88 bank (0202aee0; piece 3 reads record 4). */
typedef unsigned short u16;

extern int func_0202aee0(int bank, u16 id);

void func_ov252_020cd620(int actor, signed char which, int *out)
{
    int bank = *(int *)(*(int *)(actor + 0x384) + 0x88);
    signed char i;

    *(signed char *)(actor + which + 0x39c) = *(signed char *)(actor + 0x310);
    for (i = 0; i < 4; i++) {
        if (i != which) {
            out[i] = func_0202aee0(bank, i == 0 ? 0 : i == 1 ? 1 : i == 2 ? 2 : 4);
        }
    }
}
