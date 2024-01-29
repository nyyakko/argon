import os

if (not os.path.isdir('./iso/modules')):
    os.system('mkdir ./iso/modules')

os.system('cmake --build build --clean-first')
