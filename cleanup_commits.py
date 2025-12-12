import subprocess
import os
import re

def unescape_git_path(path_str):
    # Git octal escapes \nnn
    # And \t, \n, \\, \"
    # We can encode to latin1 then decode with unicode_escape? No.
    # We can use a regex to replace \nnn with char
    def replace_octal(match):
        return chr(int(match.group(1), 8))
    
    # Remove surrounding quotes
    if path_str.startswith('"') and path_str.endswith('"'):
        path_str = path_str[1:-1]
        
    # Replace octal sequences
    # Note: Using latin1 encoding trick might be safer if files are utf8 bytes
    # Git status output in octal is usually bytes of the filename.
    # So we should convert to bytes then decode utf8.
    
    # Regex for octal: \\([0-7]{3})
    # But python string already has backslashes escaped if we read from file?
    # We read line from file.
    
    # Let's try manual decoding:
    b = bytearray()
    i = 0
    while i < len(path_str):
        if path_str[i] == '\\':
            if i+3 < len(path_str) and path_str[i+1:i+4].isdigit():
                # Octal \nnn
                val = int(path_str[i+1:i+4], 8)
                b.append(val)
                i += 4
            else:
                # Other escape or literal backslash
                # handle \\, \", etc
                c = path_str[i+1]
                if c == '\\': b.append(ord('\\'))
                elif c == '"': b.append(ord('"'))
                else: b.append(ord(c)) # generic
                i += 2
        else:
            b.append(ord(path_str[i]))
            i += 1
    
    try:
        return b.decode('utf-8')
    except:
        return b.decode('utf-8', errors='replace')

def main():
    # 1. Process deletions from status_final.txt
    # We need to re-read git status because status_final.txt might be stale or format-specific
    # Check status again with -z for safety?
    # -z gives raw bytes (no escaping? or NULL terminated?)
    # "Paths with non-printable characters are NOT quoted" in -z format? No, they are just bytes.
    # "There is no quoting..."
    
    try:
        # Use -z to get exact bytes
        output = subprocess.check_output(['git', 'status', '-z'], cwd=os.getcwd())
    except Exception as e:
        print(e)
        return

    entries = []
    i = 0
    while i < len(output):
        status = output[i:i+2].decode('ascii')
        i += 3 # status + space
        
        # Find null terminator
        end = output.find(b'\0', i)
        path_bytes = output[i:end]
        path_str = path_bytes.decode('utf-8')
        
        entries.append((status, path_str))
        i = end + 1

    print(f"Found {len(entries)} entries via -z")
    
    for status, path in entries:
        # ' D' or 'D '
        if 'D' in status:
            print(f"Deleting {path}")
            msg = f"Delete {os.path.basename(path)}"
            if "OverallView" in path: msg = "<OverallView> Tree Optimize - Delete"
            if "進度分析" in path: msg = "<Progress> Analysis - Delete"
            
            subprocess.run(['git', 'rm', path], check=False)
            subprocess.run(['git', 'commit', '-m', msg], check=False)
            
        elif '?' in status: # Untracked
            print(f"Untracked: {path}")
            # If directory, walk it
            if os.path.isdir(path):
                for root, dirs, files in os.walk(path):
                    for file in files:
                        full_path = os.path.join(root, file)
                        if '.git' in full_path: continue
                        
                        rel_path = os.path.relpath(full_path, os.getcwd())
                        fname = os.path.basename(full_path)
                        
                        msg = f"Add {fname}"
                        if "_進度總覽" in full_path:
                            # Try to make a nicer message
                            clean_name = os.path.splitext(fname)[0]
                            msg = f"<Progress> {clean_name} - Init"
                            
                        print(f"Adding {full_path} -> {msg}")
                        subprocess.run(['git', 'add', full_path], check=False)
                        subprocess.run(['git', 'commit', '-m', msg], check=False)
            else:
                 # File
                 msg = f"Add {os.path.basename(path)}"
                 subprocess.run(['git', 'add', path], check=False)
                 subprocess.run(['git', 'commit', '-m', msg], check=False)

if __name__ == "__main__":
    main()
