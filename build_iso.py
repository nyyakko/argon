import os

if (os.path.isfile('./iso/argon.iso')):
    os.remove('./iso/argon.iso')

os.system('cp ./build/debug/kernel.img ./iso/boot')
os.system('genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A argon -input-charset utf8 -quiet -boot-info-table -o ./iso/argon.iso iso')

