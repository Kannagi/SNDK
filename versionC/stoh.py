import re

def modify_asm_file(input_file, output_file):
    with open(input_file, 'r', encoding='utf-8') as f_in:
        lines = f_in.readlines()
    
    new_lines = ['asm "']
    
    for line in lines:
        # Remove ';' comments
        line = re.sub(r';.*', '', line)

        # Apply replacements
        line = re.sub(r'\.ascii\b', '.data_s', line)
        line = re.sub(r'\.asciz\b', '.data_s', line)
        line = re.sub(r'\bshort\b', 'data_w', line)
        line = re.sub(r'\blong\b', 'data_l', line)
        line = re.sub(r'\bL.str.\b', 'L_str_', line)
        line = re.sub(r'\bL.str\b', 'L_str', line)

        # Handle special dot with regex - only remove if it's not one of our protected patterns
        line = re.sub(r'\.(?!L|data_)[^\n]*', '', line)

        line = re.sub(r'\+1', '+', line)
        line = re.sub(r'\+2', '*', line)

        line = re.sub(r'mos16hi\((.+?)\)', r'\1>', line)
        line = re.sub(r'mos16lo\((.+?)\)', r'\1', line) 

        line = re.sub(r'__rc', '', line)
        line = re.sub(r'"', '\'', line)


        line = re.sub(r'(stx|ldx|lda|sta|ldy|sty)\s+([a-zA-Z_][a-zA-Z0-9_]*)(?!#\d)', r'\1 @\2', line)

        line = re.sub(r'data_s', 'data.s', line)
        line = re.sub(r'data_w', 'data.w', line)
        line = re.sub(r'data_l', 'data.l', line)
    
        if line.strip():
            new_lines.append(line.rstrip())

    new_lines.append('";')
    
    with open(output_file, 'w', encoding='utf-8') as f_out:
        f_out.write('\n'.join(new_lines))

if __name__ == "__main__":
    import sys
    if len(sys.argv) == 3:
        modify_asm_file(sys.argv[1], sys.argv[2])
    else:
        print("Usage: python script.py input.s output.s")