import pdfplumber

filename = "OMA-TS-ULP-V2_0_4-20181213-A.pdf"
out_filename = "asn.txt"

"""
parsing_state
0=seek for " AUTOMATIC TAGS ::="
1=seek for "END"
"""
parse_state = 0
from_flag = False
num_parenthese = 0

def extract_asn(txt, f):
    global parse_state, from_flag, num_parenthese
    skip_begin_tag = False
    lines = txt.split("\n")
    for line in lines:
        if "2018 Open Mobile Alliance" in line:
            return
        if "OMA-TS-ULP-V2_0_4-20181213-A Page" in line:
            continue
        if skip_begin_tag:
            skip_begin_tag = False
            continue
        if parse_state == 0:
            if " AUTOMATIC TAGS ::=" in line:
                skip_begin_tag = True
                parse_state = 1
        elif parse_state == 1:
            if "END" == line:
                parse_state = 0
            else:
                if from_flag:
                    f.write("    ")
                    from_flag = False
                if "FROM " in line and ";" not in line:
                    from_flag = True
                for i in range(num_parenthese):
                    f.write("  ")

                try:
                    f.write(line + "\n")
                except Exception as err:
                    print(err)
                
                num_parenthese += line.count("{")
                val = line.count("}")
                num_parenthese -= val
                if num_parenthese == 0 and val > 0:
                    f.write("\n")

                if "FROM " in line and ";" in line:
                    f.write("\n")
                print(line)
                pass


if __name__ == "__main__":
    f = open(out_filename, "w")

    with pdfplumber.open(filename) as pdf:
        for i in range(296, 333): # 333
            page = pdf.pages[i]
            extract_asn(page.extract_text(), f)

    f.close()