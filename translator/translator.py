import re

def remove_comments(code: str) -> str:
    # remove (/* ... */)
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
    # remove (// ...)
    code = re.sub(r'//.*', '', code)
    return code

def add_semicolon_except_keywords_and_braces(code: str) -> str:
    keywords = ('void','do','else','if')
    new_lines = []

    for line in code.splitlines():
        stripped = line.strip()

        if stripped == '':
            new_lines.append(line)
            continue

        if any(stripped.startswith(kw) for kw in keywords):
            new_lines.append(line)
            continue

        if '{' in line or '}' in line:
            new_lines.append(line)
            continue

        if not stripped.endswith(';'):
            new_lines.append(line + ';')
        else:
            new_lines.append(line)

    return '\n'.join(new_lines)

def replace_proc_outside_strings(code: str) -> str:

    pattern = r'"(?:\\.|[^"\\])*"|[^"\\]+'

    def replacer(match):
        text = match.group(0)
        if text.startswith('"'):
            return text  # Ne pas modifier les chaînes
        else:
            text = re.sub(';', '', text)
            text = text.replace('$', '&')
            text = re.sub(r'#.*?,', '0,', text)
            text = re.sub(':', '(', text)
            text = re.sub(r'\b(SNDK_memcopy)\b' , 'SNDK_memcopy(' , text)
            text = re.sub(r'\b(SNDK_SendVRAM)\b', 'SNDK_SendVRAM(', text)
            text = re.sub('.incbin', 'SNDK_ROM_LOAD(', text)
            text = re.sub('.endmacro', '}', text)
            text = re.sub(r'\b(if)\b', 'if(', text)
            text = re.sub(r'\b(while)\b', 'while(', text)
            text = re.sub(r'\b(loop)\b', 'while(--', text)
            text = re.sub('.data.s', 'const char* =', text)
            text = re.sub('.data.b', 'const uint8 * = {', text)
            text = re.sub('.data.w', 'const uint16 * = {', text)
            text = re.sub(r'\b(spm|lib|call|MODE16|MODE8|FORCED_BLANK)\b', '', text)
            text = re.sub(r'\b(proc|func|funcspm|funclib)\b', 'void', text)
            text = re.sub(r'\[([a-zA-Z_][\w\.]*)\s*,\s*([^\]]+)\]', r'\1[\2]', text)
            text = re.sub(r'\.macro\s+([a-zA-Z_]\w*)', r'void \1 (){', text)

            text = re.sub(r'\(,', ',', text)



            # add ');'
            lines = text.splitlines()
            new_lines = []

            for line in lines:
                stripped = line.strip()

                if (
                    '(' in stripped
                    and not stripped.endswith('{')
                    and not stripped.endswith(')')
                ):
                    new_lines.append(line.rstrip() + ')')
                else:
                    new_lines.append(line)

            text = '\n'.join(new_lines)

            return text

    return ''.join(replacer(m) for m in re.finditer(pattern, code))

def process_file(input_path: str, output_path: str):
    with open(input_path, 'r', encoding='utf-8') as f:
        code = f.read()

    code = remove_comments(code)
    code = replace_proc_outside_strings(code)
    code = add_semicolon_except_keywords_and_braces(code)

    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(code)

import os
# use
def process_all_egl_files():
    for filename in os.listdir('.'):
        if filename.endswith('.egl'):
            outfile = filename[:-4] + '.c'  # remplace .egl par .c
            print(f"Transpiling {filename} → {outfile}")
            process_file(filename, outfile)

if __name__ == '__main__':
    process_all_egl_files()



