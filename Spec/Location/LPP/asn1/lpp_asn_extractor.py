import pdfplumber

filename = "ts_137355v160200p.pdf"
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
        
        # skip tail
        if line == "ETSI" and len(line) == 4:
            return
        
        # skip header
        if "3GPP TS 37.355 version 16.2.0 Release 16" in line:
            continue

        if parse_state == 0:
            if "-- ASN1START" in line:
                parse_state = 1
        elif parse_state == 1:
            if "-- ASN1STOP" in line:
                parse_state = 0
                continue

            for i in range(num_parenthese):
                line = "  " + line

            print(line)
            
            try:
                f.write(line + "\n")
            except Exception as err:
                print(err)
            
            num_parenthese += line.count("{")
            val = line.count("}")
            num_parenthese -= val
            if num_parenthese == 0 and val > 0:
                f.write("\n")


if __name__ == "__main__":
    f = open(out_filename, "w")

    with pdfplumber.open(filename) as pdf:
        for i in range(35, 294):
            page = pdf.pages[i]
            extract_asn(page.extract_text(), f)

    f.close()