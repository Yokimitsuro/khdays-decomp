struct w3 { int a, b, c; };
/* An enemy's +0x1f4 hook: store its home (the spawner's point, +0x2fc) and its reach (the spawner's
 * radius, its field_110, +0x308). Ov107_Spawner_PlaceActors passes both; no hit is stored here. */
void Ov107_SetHomeAndReach(int self, int pHome, int fxReach) {
    *(struct w3 *)(self + 0x2fc) = *(struct w3 *)pHome;
    *(int *)(self + 0x308) = fxReach;
}
