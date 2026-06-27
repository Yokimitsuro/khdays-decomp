"""Build a batch from an explicit list of function names (one per line on stdin
or as args). Looks them up in build/func_index.json and emits the same shape
the bulk-decomp agent consumes."""
import json, sys, os
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
out_path = sys.argv[1]
names = sys.argv[2:]
if not names:
    names = [l.strip() for l in sys.stdin if l.strip()]

idx = json.load(open(os.path.join(ROOT, 'build', 'func_index.json')))

# override mode from symbols.txt (index_funcs got some thumb entries wrong)
import re
sym_mode = {}
for root, _, files in os.walk(os.path.join(ROOT, 'config', 'arm9')):
    for f in files:
        if f == 'symbols.txt':
            for line in open(os.path.join(root, f)):
                m = re.match(r'^\s*(func_\S+)\s+kind:function\((arm|thumb),', line)
                if m: sym_mode[m.group(1)] = m.group(2)

def disasm(hexs, mode, relocs):
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode == 'thumb' else CS_MODE_ARM)
    rel = {off: sym for off, sym in relocs}
    out = []
    for i in md.disasm(bytes.fromhex(hexs), 0):
        line = '  %04x: %-6s %s' % (i.address, i.mnemonic, i.op_str)
        if i.address in rel:
            line += '    ; -> ' + rel[i.address]
        out.append(line)
    return '\n'.join(out)

batch = []
for n in names:
    if n not in idx:
        print('SKIP (no idx):', n); continue
    d = idx[n]
    mode = sym_mode.get(n, d['mode'])
    delink = os.path.join(ROOT, 'build', 'delinks', d['module'] + '.o').replace('\\', '/')
    batch.append({
        'name': n, 'size': d['size'], 'mode': mode, 'hex': d['hex'] if 'hex' in d else '',
        'relocs': d['relocs'], 'delink': delink,
        'disasm': disasm(d['hex'], mode, d['relocs']) if 'hex' in d else '',
    })

with open(out_path, 'w') as f: json.dump(batch, f, indent=2)
print('wrote', len(batch), 'entries to', out_path)
for i, e in enumerate(batch):
    print('[%2d] %-30s size=%-4d mode=%-5s relocs=%d' % (i, e['name'], e['size'], e['mode'], len(e['relocs'])))
