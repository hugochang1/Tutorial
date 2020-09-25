# ----------------- Anaconda installation -----------------
need to use older version or Jupyter or Spyder cannot be launched
https://repo.anaconda.com/archive/
Anaconda3-5.3.1-Windows-x86_64.exe

# ----------------- build executable -----------------
pip install pyinstaller
pyinstaller --onefile --noconsole --icon=app.ico xxx.py

# ----------------- pip [SSL: CERTIFICATE_VERIFY_FAILED] -----------------
pip install --trusted-host pypi.org --trusted-host files.pythonhosted.org <package_name>
pip install --trusted-host pypi.org --trusted-host files.pythonhosted.org PyPDF2
