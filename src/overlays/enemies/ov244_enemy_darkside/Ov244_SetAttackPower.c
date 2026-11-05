/* The Darkside's +0x1d8 hook, Ov107_SetAttackPower's override: stores attack nAttack's power
 * as the base does, then gives attack 3's power to attack 0 of each of its two parts (+0x400)
 * and attack 4's to their attack 1, through each part's own +0x1d8 hook. */
extern void Ov107_SetAttackPower(int self, int nAttack, int nPower);

void Ov244_SetAttackPower(int self, int nAttack, int nPower) {
    int i;
    Ov107_SetAttackPower(self, nAttack, nPower);
    if (nAttack == 3) {
        int nPartAttack = 0;
        for (i = 0; i < 2; i++) {
            int part = (*(int **)(self + 0x400))[i];
            void (*pSetPartPower)(int, int, int) = *(void (**)(int, int, int))(part + 0x1d8);
            if (pSetPartPower != 0) pSetPartPower(part, nPartAttack, nPower);
        }
    } else if (nAttack == 4) {
        int nPartAttack = 1;
        for (i = 0; i < 2; i++) {
            int part = (*(int **)(self + 0x400))[i];
            void (*pSetPartPower)(int, int, int) = *(void (**)(int, int, int))(part + 0x1d8);
            if (pSetPartPower != 0) pSetPartPower(part, nPartAttack, nPower);
        }
    }
}
