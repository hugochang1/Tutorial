# ----------------- Anaconda installation -----------------
need to use older version or Jupyter or Spyder cannot be launched
https://repo.anaconda.com/archive/
Anaconda3-5.3.1-Windows-x86_64.exe

# ----------------- build executable -----------------
pip install pyinstaller
pyinstaller --onefile --noconsole --icon=app.ico xxx.py

# ----------------- pip [SSL: CERTIFICATE_VERIFY_FAILED] -----------------
[solution 1]
pip install --trusted-host pypi.org --trusted-host files.pythonhosted.org <package_name>
pip install --trusted-host pypi.org --trusted-host files.pythonhosted.org PyPDF2

[solution 2]
https://dotblogs.com.tw/what_s_note/2017/10/24/112508
pip -v install <package name> >out.txt
pip install --index-url=http://pypi.python.org/simple/ --trusted-host pypi.python.org <package_name>

----------------- pip install -----------------
py -m pip --version
py -m pip install pyinputplus

# ----------------- regular expression  -----------------
https://www.datacamp.com/community/tutorials/python-regular-expression-tutorial?utm_source=adwords_ppc&utm_medium=cpc&utm_campaignid=14989519638&utm_adgroupid=127836677279&utm_device=m&utm_keyword=&utm_matchtype=b&utm_network=g&utm_adpostion=&utm_creative=332602034364&utm_targetid=dsa-473406579035&utm_loc_interest_ms=&utm_loc_physical_ms=9040379&gclid=CjwKCAiA7dKMBhBCEiwAO_crFCAlhOxsYLkxtarooP1jfeE7HaxhpHzDnCxcbHznNKlb5uYouRqvtBoC5rUQAvD_BwE
