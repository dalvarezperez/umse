import os
import ctypes

NULL = ctypes.POINTER(ctypes.c_int)()
libUmseDll = ctypes.cdll.LoadLibrary("..\\bin\\Debug\\libUmse.dll")
umseSize = ctypes.c_int()
umse = ctypes.POINTER(ctypes.c_ubyte)()

def test_file(file):
	with open(file, "rb") as f:
		pe_bytes = f.read()
		pe_bytes_length = len(pe_bytes)
		print("[*] Testing: "+file)
		libUmseDll.ChunkToUmse(ctypes.c_int(pe_bytes_length), ctypes.c_char_p(pe_bytes), ctypes.byref(umseSize), ctypes.byref(umse))
		output_name=(file+".umse").replace("samples","output")
		with open(output_name, "wb") as umse_file:
			umse_file.write(bytearray(umse[:umseSize.value]))

def ls(path):
    files = []
    for r, d, f in os.walk(path):
        for file in f:
            files.append(os.path.join(r, file))
    return files

files=ls("samples")
for file in files:
	test_file(file)