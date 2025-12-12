import subprocess
import re
import os
import sys
import shlex

def get_git_status():
    try:
        # Use --porcelain for parsing
        lines = subprocess.check_output(['git', 'status', '--porcelain'], cwd=os.getcwd()).decode('utf-8').splitlines()
    except subprocess.CalledProcessError as e:
        print("Error getting status:", e)
        return []
        
    entries = []
    for line in lines:
        if not line: continue
        status = line[:2]
        raw_path = line[3:]
        # Handle quoting if present
        if raw_path.startswith('"') and raw_path.endswith('"'):
            # This is a quoted path
            # We can use eval to interpret basic string escapes or shlex
            # git quotes are fairly standard.
            try:
                path = raw_path[1:-1]
                # Git escapes quotes as \", backslashes as \\. 
                # Basic unescape:
                path = path.replace('\\"', '"').replace('\\\\', '\\')
                # Git might also use octal escapes for unicode, but hopefully not common here.
            except:
                path = raw_path
        else:
            path = raw_path
            
        entries.append((status, path))
    return entries

def generate_msg(status, path):
    filename = os.path.basename(path)
    # Clean status for logic
    s = status.strip()
    action = "Update"
    if 'D' in status: action = "Delete"
    if '?' in status: action = "Init" # Untracked usually valid for new files
    
    # Rule 1: NeetCode Todo
    if "NeetCode Todo List" in path:
        # e.g. trees.md -> tree (naive)
        topic = os.path.splitext(filename)[0]
        suffix = "進度更新"
        if 'D' in status: suffix = "總表移除"
        return f"<NeetCode> {topic} {suffix}"
        
    # Rule 2: Problem - Main
    # "139. Word Break - Main.md"
    match = re.search(r'(\d+)\. (.+) - Main\.md', filename)
    if match:
        num = match.group(1)
        name = match.group(2)
        if action == "Init": return f"[{num}] {name} - Init"
        if action == "Delete": return f"[{num}] {name} - Delete"
        return f"[{num}] {name} - Update"

    # Rule 3: Problem - Ans
    # "1. Two Sum - Ans 1 - Hash - N.md"
    match = re.search(r'(\d+)\. (.+) - Ans', filename)
    if match:
        num = match.group(1)
        name = match.group(2)
        ans_action = "Update"
        if action == "Init": ans_action = "Add"
        if action == "Delete": ans_action = "Delete"
        
        # Try to find extra details "Hash - N"
        # filename is "1. Two Sum - Ans 1 - Hash - N.md"
        # group(2) is "Two Sum"
        # Remainder: " - Ans 1 - Hash - N.md"
        extra = ""
        try:
            parts = filename.split(" - Ans ")
            if len(parts) > 1:
                # "1 - Hash - N.md"
                rest = parts[1].replace('.md', '')
                # "1 - Hash - N"
                extra = " " + rest
        except:
            pass
            
        return f"[{num}] {name} - {ans_action} Answer{extra}"

    # Rule 4: Generic Problem File via Number
    match = re.search(r'(\d+)\. (.+)\.md', filename)
    if match:
        num = match.group(1)
        name = match.group(2)
        return f"[{num}] {name} - {action}"
    
    # Rule 5: Overall View
    if "OverallView" in path:
        name = filename.replace('.md', '')
        if "Tree" in name: 
            return f"<OverallView> Tree - {action}"
        return f"<OverallView> {name} - {action}"

    return f"{action} {filename}"

def main():
    entries = get_git_status()
    print(f"Found {len(entries)} changes.")
    
    for status, path in entries:
        # Check if file exists (for Add)
        if 'D' not in status and not os.path.exists(path):
            # Might be a rename source or confusion
            print(f"Skipping {path} (not found)")
            continue
            
        msg = generate_msg(status, path)
        print(f"Processing: {path}")
        print(f"  Message: {msg}")
        
        try:
            # git add
            if 'D' in status:
                subprocess.run(['git', 'rm', path], check=True, stdout=subprocess.DEVNULL)
            else:
                subprocess.run(['git', 'add', path], check=True, stdout=subprocess.DEVNULL)
            
            # git commit
            res = subprocess.run(['git', 'commit', '-m', msg], capture_output=True, text=True, encoding='utf-8')
            if res.returncode != 0:
                print(f"  Commit Failed: {res.stderr.strip()}")
            else:
                print(f"  Committed.")
                
        except Exception as e:
            print(f"  Error: {e}")

if __name__ == "__main__":
    main()
