# BOOT.XF.2.1

# Setup
1. Install required tools: ```sudo apt install build-essential uuid-dev gcc g++ python2.7 sqlite3 iasl git nasm```
2. Set in "boot_images/QcomPkg/toolchainconfig.json" absolute path to :
 * "QCOM_LLVM_10.0/bin/"
 * "QCOM_LLVM_10.0/tools/bin/"
 * "QCOM_LLVM_10.0/tools/bin/arm-elfcopy"
3. For more info read "boot_images\QcomPkg\Docs\*"

# Build
```
python2.7 boot_images/QcomPkg/buildex.py -t SDM670Pkg --variant LA -r DEBUG -c -Wno-error
```
Ignore "sign/default/sbl1/xbl.elf" error at the end (signed xbl.elf not generated)

Final file location stored in BuildProducts.txt that generated after build


