import subprocess
import re
import os
import sys

def get_git_status():
    try:
        # Use --porcelain
        lines = subprocess.check_output(['git', 'status', '--porcelain'], cwd=os.getcwd()).decode('utf-8').splitlines()
    except:
        return []
        
    entries = []
    for line in lines:
        if len(line) < 4: continue
        status = line[:2]
        raw_path = line[3:]
        # Unquote if needed (simple)
        if raw_path.startswith('"') and raw_path.endswith('"'):
            raw_path = raw_path[1:-1].replace('\\"', '"').replace('\\\\', '\\')
        
        entries.append((status, raw_path))
    return entries

def generate_msg(path):
    filename = os.path.basename(path)
    if not filename: return f"Add {path}"
    
    # Rule: Progress Overview
    if "_進度總覽" in path or "進度分析" in path:
        name = os.path.splitext(filename)[0]
        return f"<Progress> {name} - Init"

    # Rule: Problem Directory/Files
    # Trees/[111] min depth .../file.md
    # Try to extract number from path
    match = re.search(r'\[(\d+)\]', path)
    if match:
        num = match.group(1)
        # Try to guess name from filename or parent
        # If filename is "111 題目.md" etc
        return f"[{num}] {filename} - Init"

    # Generic Problem pattern
    match = re.search(r'(\d+)\. (.+)', filename)
    if match:
        return f"[{match.group(1)}] {match.group(2)} - Init"
        
    return f"Add {filename}"

def commit_file(path):
    if os.path.isdir(path):
        # Recurse
        for root, dirs, files in os.walk(path):
            for file in files:
                full_path = os.path.join(root, file)
                # Ignore .git things
                if '.git' in full_path: continue
                commit_file(full_path)
    else:
        # It's a file
        msg = generate_msg(path)
        print(f"Committing {path} -> {msg}")
        try:
            subprocess.run(['git', 'add', path], check=True, stdout=subprocess.DEVNULL)
            subprocess.run(['git', 'commit', '-m', msg], check=True, stdout=subprocess.DEVNULL)
        except Exception as e:
            print(f"Error: {e}")

def main():
    entries = get_git_status()
    print(f"Found {len(entries)} top-level changes.")
    for status, path in entries:
        if '?' in status:
            # Untracked, might be file or dir
            if os.path.exists(path):
                commit_file(path)

if __name__ == "__main__":
    main()
