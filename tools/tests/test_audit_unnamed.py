"""Naming debt belongs to the module's address space, not its symbol spelling."""
import contextlib
import io
import re
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import audit_unnamed


class AuditUnnamedTests(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.root = Path(directory.name)

    def add_function(self, module, name, address, ghidra_name):
        symbols = self.root / 'config/arm9' / module / 'symbols.txt'
        symbols.parent.mkdir(parents=True, exist_ok=True)
        with symbols.open('a', encoding='utf-8') as fh:
            fh.write('%s kind:function(arm,size=0x4) addr:0x%s\n' % (name, address))
        source = self.root / 'src' / module / (name + '.c')
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text('void %s(void) {}\n' % name, encoding='utf-8')
        space = 'arm9_%s::' % module if module.startswith('ov') else ''
        return '%s at %s%s' % (ghidra_name, space, address)

    def run_audit(self, lines):
        output = io.StringIO()
        with patch.object(audit_unnamed, 'ROOT', str(self.root)), \
                patch.object(audit_unnamed, '_SYMBOLS', None), \
                patch.object(audit_unnamed, 'get', return_value='\n'.join(lines)), \
                patch.object(sys, 'argv', ['audit_unnamed.py', '--list']), \
                contextlib.redirect_stdout(output):
            self.assertEqual(audit_unnamed.main(), 0)
        return output.getvalue()

    def unit_counts(self, output):
        return {unit: int(count) for unit, count in
                re.findall(r'^   (\S+)\s+(\d+)$', output, re.M)}

    def test_renamed_overlay_functions_use_their_address_space(self):
        lines = [
            self.add_function('ov000', 'Ov000_First', '020593f4', 'FUN_020593f4'),
            self.add_function('ov000', 'UnprefixedSecond', '02059400', 'ov000_helper_59400'),
            # Overlays can share addresses: the space is part of the identity.
            self.add_function('ov002', 'Ov002_Third', '020593f4', 'FUN_020593f4'),
        ]
        output = self.run_audit(lines)
        self.assertEqual(self.unit_counts(output), {'ov000': 2, 'ov002': 1})
        self.assertIn('still named FUN_* in Ghidra: 2', output)
        self.assertIn('3 total', output)
        self.assertIn('UnprefixedSecond', output)

    def test_config_overrides_a_misleading_legacy_prefix(self):
        line = self.add_function('ov002', 'func_ov030_020593f4', '020593f4', 'FUN_020593f4')
        self.assertEqual(self.unit_counts(self.run_audit([line])), {'ov002': 1})

    def test_legacy_overlay_name_without_config_keeps_fallback(self):
        source = self.root / 'src/ov030/func_ov030_020593f4.c'
        source.parent.mkdir(parents=True)
        source.write_text('void func_ov030_020593f4(void) {}\n', encoding='utf-8')
        output = self.run_audit(['FUN_020593f4 at arm9_ov030::020593f4'])
        self.assertEqual(self.unit_counts(output), {'ov030': 1})

    def test_default_space_stays_main_and_non_debt_is_excluded(self):
        lines = [
            self.add_function('arm9', 'MainFunction', '02001000', 'FUN_02001000'),
            self.add_function('itcm', 'ItcmFunction', '01ff8100', 'FUN_01ff8100'),
            self.add_function('dtcm', 'DtcmFunction', '027e0000', 'helper_7e0000'),
            self.add_function('ov000', 'AlreadyNamed', '020593f4', 'AlreadyNamed'),
        ]
        self.add_function('ov002', 'MissingInGhidra', '02059400', 'FUN_02059400')
        output = self.run_audit(lines)
        self.assertEqual(self.unit_counts(output), {'main': 3})
        self.assertIn('(1 had no defined function in Ghidra at all)', output)
        self.assertNotIn('AlreadyNamed', output)
        self.assertNotIn('MissingInGhidra', output)
