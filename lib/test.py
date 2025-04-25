import os

files = []

for dirpath, dirnames, filenames in os.walk('.'):
    print(f"Directory: {dirpath}")
    print(f"Subdirectories: {dirnames}")
    print(f"Files: {filenames}")
    print("-" * 20)

    files.extend([os.path.join(dirpath, x) for x in filenames])

file_contents = []


for file in files:
    with open(file, "r") as file:
