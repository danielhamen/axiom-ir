import os

files = []

for dirpath, dirnames, filenames in os.walk('.'):
    files.extend([os.path.join(dirpath, x) for x in filenames])

file_contents = []


count = 0
for file in files:
    if file.endswith("cpp") or file.endswith("hpp"):
        with open(file, "r") as infile:
            contents = infile.read()
            if "OperandStack underflow" in contents:
                print(f"File {file} has an error")
            file_contents.append(f"""```{file}
{contents}
# ```
# """)

with open("Contents", "w") as file:
    file.write("\n\n".join(file_contents))
