from tkinter import *
from tkinter.filedialog import askopenfilename
from tkinter.scrolledtext import ScrolledText
import PyPDF2
import threading
import traceback

tool_version = "1.00"
"""
version history
1.00  initial release
"""

def pdf_asn_extract_start(file_name_in, file_name_out, file_header_suffix):
    print("pdf_asn_extract_start file_name_in=[" + file_name_in + "] file_name_out=["
          + file_name_out + "] file_header_suffix=[" + file_header_suffix + "]")
    btn_choosefile["state"] = "disabled"
    btn_startextract["state"] = "disabled"
    entry_choosefile["state"] = "disabled"
    entry_headersuffix["state"] = "disabled"
    
    try:
        fd = open(file_name_in, "rb")
        fw = open(file_name_out, "w")
        
        pdf = PyPDF2.PdfFileReader(fd)
        
        is_asn1_start = True
        
        for i in range(0, pdf.numPages):
            
            page = pdf.getPage(i)
            txt = page.extractText()
            
            # no idea why so many \n inserted in txt, just remove them
            txt = txt.replace("\n", "");

            text.delete("1.0", END)
            text.insert(END, "progress page (" + str(i + 1) + "/" + str(pdf.numPages) + ")")
            
            # remove the header
            pos = txt.find(file_header_suffix)
            if pos != -1:
                pos += len(file_header_suffix)
                txt = txt[pos:]
            else:
                text.insert(END, ", header is not found")
            
            
            while True:
                if is_asn1_start:
                    pos = txt.find("-- ASN1START")
                    if pos == -1:
                        break
                    else:
                        txt = txt[pos:]
                        is_asn1_start = False
                else:
                    pos = txt.find("-- ASN1STOP")
                    if pos == -1:
                        fw.write(txt)
                        break
                    else:
                        pos += 11 # plus 11 is to include ASN1STOP tag
                        fw.write(txt[:pos] + "\n")
                        txt = txt[pos:]
                        is_asn1_start = True
        
        fd.close()
        fw.close()
        
        entry_outputfile.insert(0, file_name_out)

        text.insert(END, "\nextraction is successful")
        text.mark_set("m1", "2.0")
        text.mark_set("m2", END)
        text.tag_add("t1", "m1", "m2")
        text.tag_config("t1", foreground="#00af00", background="#ffffff", font=("", 15))
    except Exception as err:
        tb = traceback.format_exc()
        text.delete("1.0", END)
        text.insert(END, str(err) + "\n" + str(tb))
        text.mark_set("m1", "1.0")
        text.mark_set("m2", END)
        text.tag_add("t1", "m1", "m2")
        text.tag_config("t1", foreground="#ff0000", background="#ffffff", font=("", 15))
        print(err)
        print(tb)
        fd.close()
        fw.close()
    finally:
        btn_choosefile["state"] = "normal"
        btn_startextract["state"] = "normal"
        entry_choosefile["state"] = "normal"
        entry_headersuffix["state"] = "normal"
    
def pdf_asn_extract_thread(filename, file_header_suffix):
    pdf_asn_extract_start(filename, filename + "_asn.txt", file_header_suffix)

def buttonChooseFile():
    filename = askopenfilename(initialdir = "./")
    if filename == "":
        return
    entry_choosefile.delete(0, END)
    entry_choosefile.insert(0, filename)

def buttonStartExtract():
    threading.Thread(target=pdf_asn_extract_thread, 
        args=[entry_choosefile.get(), entry_headersuffix.get()]).start()


tk = Tk()
# -------------------------------------
btn_choosefile = Button(tk, text="Choose a PDF file", font=("Calibri", 16), command=buttonChooseFile)
btn_choosefile.grid(row=0, column=0)
entry_choosefile = Entry(tk, font=("Calibri", 12), width=100)
entry_choosefile.grid(row=0, column=1)

Label(tk, text="Header Suffix", font=("Calibri", 16)).grid(row=1, column=0)
entry_headersuffix = Entry(tk, font=("Calibri", 12), width=100)
entry_headersuffix.insert(0, "[OMA-Template-Spec-20160602-I]")
entry_headersuffix.grid(row=1, column=1)

btn_startextract = Button(tk, text="Start Extract ASN.1", font=("Calibri", 16), command=buttonStartExtract)
btn_startextract.grid(row=2, column=0)

Label(tk, text="Output File", font=("Calibri", 16)).grid(row=3, column=0)
entry_outputfile = Entry(tk, font=("Calibri", 12), width=100)
entry_outputfile.grid(row=3, column=1)
entry_outputfile.bind("<Key>", lambda e: "break")

text = ScrolledText(tk, width=150, height=10, wrap="none", undo=True)
pop = Menu(tk, tearoff=False)
#pop.add_command(label="Cut", command=lambda:text.event_generate("<<Cut>>"))
pop.add_command(label="Copy", command=lambda:text.event_generate("<<Copy>>"))
#pop.add_command(label="Paste", command=lambda:text.event_generate("<<Paste>>"))
text.grid(row=5, column=0, columnspan=2)
text.bind("<Key>", lambda e: "break")
text.bind("<Button-3>", lambda event:pop.post(event.x_root, event.y_root))

# -------------------------------------
tk.title("PDF ASN.1 Extractor v" + tool_version)
tk.geometry("1200x400+0+0")
#tk.config(bg="#e0e0e0")  # RGB
# tk.iconify()  # adjust to min window size
# tk.state("zoomed")  # adjust to max window size
tk.bind_all("<KeyPress-Escape>", lambda event:tk.destroy())
tk.resizable(True, True)
tk.lift()
tk.focus_force()
#tk.after(50000, tk.destroy)
tk.mainloop()
