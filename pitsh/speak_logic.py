import subprocess
import os
import stat
import platform
from pathlib import Path

def speak(text, output="output_pitch_shift.wav"):
    base_dir = Path(__file__).parent.resolve()
    
    # 1. 実行環境に合わせてバイナリ名を判定
    pf = platform.system()
    if pf == "Windows":
        jtalk_bin = "open_jtalk.exe"
    elif pf == "Darwin":  # macOS
        jtalk_bin = "open_jtalk"
    else:                 # Linux (Ubuntu)
        jtalk_bin = "open_jtalk"

    bin_path = base_dir / "bin" / jtalk_bin
    dict_path = base_dir / "dict"
    voice_path = base_dir / "voice" / "nitech_jp_atr503_m001.htsvoice"

    if not bin_path.exists():
        print(f"Error: Binary not found at {bin_path}")
        # 念のため、古いファイル名でも探す（互換性のため）
        bin_path = base_dir / "bin" / "open_jtalk"
        if not bin_path.exists():
            return

    # 2. Windows以外（Mac/Linux）の場合は実行権限を付与
    if pf != 'Windows':
        st = os.stat(bin_path)
        os.chmod(bin_path, st.st_mode | stat.S_IEXEC)

    cmd = [
        str(bin_path),
        "-x", str(dict_path),
        "-m", str(voice_path),
        "-ow", output,
        "-r", "0.7", "-fm", "2.0", "-a", "0.55"
    ]
    
    try:
        process = subprocess.Popen(cmd, stdin=subprocess.PIPE)
        process.communicate(input=text.encode('utf-8'))
        print(f"Saved: {output} (OS: {pf})")
    except Exception as e:
        print(f"Execution failed: {e}")