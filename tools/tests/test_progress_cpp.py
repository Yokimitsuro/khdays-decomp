"""C++ matching sources contribute their original function bytes to progress."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import progress


class ProgressCppTest(unittest.TestCase):
    def test_cpp_function_bytes_are_counted(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "src/calls/func_example.cpp"
            symbols = root / "config/arm9/symbols.txt"
            source.parent.mkdir(parents=True)
            symbols.parent.mkdir(parents=True)
            source.write_text("int func_example() { return 1; }\n")
            symbols.write_text("func_example kind:function(arm,size=0x10) addr:0x02000000\n")
            with patch.object(progress, "ROOT", root):
                self.assertEqual(progress.compute_byte_progress(), (16, 16))
