"""Bulk-verify all files in build/verify_list.json with tools/match.py.
Reports OK/FAIL per file."""
import json, subprocess, sys, os
fns = json.load(open('build/verify_list.json'))
ok, fail = [], []
for p, n, mode, delink, nrelocs in fns:
    if nrelocs == 0 and '/auto/' in p:
        # reloc-free: pass hex
        import json as _j
        idx = _j.load(open('build/func_index.json'))
        hexb = idx[n]['hex']
        cmd = ['python', 'tools/match.py', p, hexb]
    else:
        cmd = ['python', 'tools/match.py', p, '--obj', delink, '--func', n]
    if mode == 'thumb': cmd.append('--thumb')
    try:
        out = subprocess.run(cmd, capture_output=True, text=True, timeout=30)
        if '>>> MATCH <<<' in out.stdout or '>>> MATCH <<<' in out.stderr:
            ok.append(n)
        else:
            fail.append((n, p, out.stdout[-400:] + out.stderr[-400:]))
    except Exception as e:
        fail.append((n, p, str(e)))
print(f'OK={len(ok)} FAIL={len(fail)}')
for n,p,msg in fail:
    print(f'--- FAIL: {n} ({p})')
    print(msg)
    print()
