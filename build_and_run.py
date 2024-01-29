import os

os.system('python ./build.py')
os.system('python ./build_iso.py')

os.system('qemu-system-i386.exe -cdrom ./iso/argon.iso')
