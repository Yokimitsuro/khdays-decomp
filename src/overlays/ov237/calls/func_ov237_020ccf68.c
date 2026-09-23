/* Hit relay of the ov237 actor: a linked partner (+0x4a4) runs its own +0x1ec hit callback with the
 * same hit and takes over the actor's health (+0x21a); the base hit handler (020c8500) then runs. */
typedef void (*HitCallback)(char *actor, int hit);

extern int func_ov107_020c8500(char *self, int hit);

int func_ov237_020ccf68(char *self, int hit)
{
    char *partner = *(char **)(self + 0x4a4);

    if (partner != 0) {
        HitCallback cb = *(HitCallback *)(partner + 0x1ec);

        if (cb != 0) {
            cb(partner, hit);
        }
        *(short *)(*(char **)(self + 0x4a4) + 0x21a) = *(short *)(self + 0x21a);
    }
    return func_ov107_020c8500(self, hit);
}
