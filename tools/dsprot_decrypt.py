"""Descifra los cuerpos protegidos de ov028 usando el algoritmo de DS Protect 1.10.

Fuente del algoritmo: https://github.com/taxicat1/dsprot (rama 1.10), src/rc4.c +
src/encryptor.c. Reimplementado aqui en Python para VERIFICAR que ov028 es DS Protect;
no se copia codigo al repo.
"""
import sys
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

BASE = 0x0208a7e0                      # inicio de ov028 en memoria
BIN  = r'E:\KH 3582\decomp\build\build\arm9_ov028.bin'
data = bytearray(open(BIN, 'rb').read())

def w(off):
    return int.from_bytes(data[off:off+4], 'little')

def rc4_init(key):
    """KSA modificado: i va de 255 a 0, no de 0 a 255 (comentario del propio dsprot)."""
    S = list(range(256))
    Si = 0
    Ki = 0
    for i in range(255, -1, -1):
        t1 = S[i]
        Si = (Si + key[Ki] + t1) & 0xFF
        t2 = S[Si]
        S[Si] = t1
        S[i] = t2
        Ki = (Ki + 1) % len(key)
    return {'i': 0, 'j': 0, 'S': S}

def rc4_byte(c):
    S = c['S']
    i = (c['i'] + 1) & 0xFF
    ival = S[i]
    j = (ival + c['j']) & 0xFF
    jval = S[j]
    c['i'] = i; c['j'] = j
    S[j] = ival; S[i] = jval
    return S[(ival + jval) & 0xFF]

def decrypt_range(off, nwords):
    """Byte 0 y 1 con RC4, byte 2 XOR 1, byte 3 intacto (por eso el opcode alto se ve)."""
    key_ins = w(off - 4)
    key = []
    for i in range(16):
        b = (key_ins >> ((i % 4) * 8)) & 0xFF
        if i % 15 == 0:
            b ^= 0xFF
        key.append(b)
    c = rc4_init(key)
    out = bytearray()
    for k in range(nwords):
        o = off + k * 4
        out.append(data[o]     ^ rc4_byte(c))
        out.append(data[o + 1] ^ rc4_byte(c))
        out.append(data[o + 2] ^ 0x01)
        out.append(data[o + 3])
    return bytes(out)

def find_range(off):
    """El tamano se deduce buscando hacia delante la repeticion de la palabra clave."""
    key_ins = w(off - 4)
    n = 0
    while w(off + n * 4) != key_ins:
        n += 1
        if n > 400:
            return None
    return n

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
targets = [0x0208b040, 0x0208b120, 0x0208b200, 0x0208b2e0, 0x0208b3c0, 0x0208b490]
for t in targets:
    off = t - BASE
    print('=' * 66)
    print('func_ov028_%08x' % t)
    # prologo en claro: localizar el bl al descifrador y de ahi el inicio del rango
    start = None
    for k in range(0, 12):
        ins = list(md.disasm(bytes(data[off + k*4: off + k*4 + 4]), t + k*4))
        if ins and ins[0].mnemonic == 'bl':
            start = off + (k + 1) * 4 + 4   # tras el bl va la palabra clave, luego el cuerpo
            break
    for i in md.disasm(bytes(data[off:off + 16]), t):
        print('   %08x  %-8s %s' % (i.address, i.mnemonic, i.op_str))
    if start is None:
        print('   (no encuentro el bl del descifrador)'); continue
    n = find_range(start)
    print('   rango cifrado en %08x, %s palabras' % (BASE + start, n))
    if not n:
        continue
    clear = decrypt_range(start, n)
    for i in md.disasm(clear, BASE + start):
        print('   %08x  %-8s %s' % (i.address, i.mnemonic, i.op_str))
