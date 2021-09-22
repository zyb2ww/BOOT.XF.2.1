# BOOT.XF.2.1

# Setup
1. ```git clone https://github.com/map220v/BOOT.XF.2.1.git --recursive```
2. Install required tools: ```sudo apt install build-essential uuid-dev gcc g++ python2.7 sqlite3 iasl git nasm```
3. ```sudo ln -s /usr/bin/python2.7 /usr/bin/python```
4. Set in "boot_images/QcomPkg/toolchainconfig.json" absolute path to :
 * "QCOM_LLVM_10.0/bin/"
 * "QCOM_LLVM_10.0/tools/bin/"
 * "QCOM_LLVM_10.0/tools/bin/arm-elfcopy"

# Build
```
python2.7 boot_images/QcomPkg/buildex.py -t SDM670Pkg --variant LA -r DEBUG -c -Wno-error
```
Ignore "sign/default/sbl1/xbl.elf" error at the end (signed xbl.elf not generated)

Final file location stored in BuildProducts.txt that generated after build


