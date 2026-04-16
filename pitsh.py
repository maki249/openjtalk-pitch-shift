import subprocess
import os

def speak(text, output="output_pitch_shift.wav"):
    base_dir = os.path.dirname(__file__)
    
    bin_path = os.path.join(base_dir, "open_jtalk-1.11", "bin", "open_jtalk")
    dict_path = os.path.join(base_dir, "dict")
    voice_path = os.path.join(base_dir, "voice", "nitech_jp_atr503_m001.htsvoice")

    if not os.path.exists(bin_path):
        print(f"Error: Binary not found at {bin_path}")
        return

    cmd = [
        bin_path,
        "-x", dict_path,
        "-m", voice_path,
        "-ow", output,
        "-r", "0.7", "-fm", "2.0", "-a", "0.55"
    ]
    
    process = subprocess.Popen(cmd, stdin=subprocess.PIPE)
    process.communicate(input=text.encode('utf-8'))
    print(f"Saved: {output}")