/* An enemy's +0x1d8 hook: store attack nAttack's power at +0x290 + 6 * nAttack (a level 6 Shadow's two
 * attacks have power 6 and 18, a level 1 one's 3 and 9). */
void Ov107_SetAttackPower(int self, int nAttack, short nPower) {
    *(short *)(self + nAttack * 6 + 0x290) = nPower;
}
