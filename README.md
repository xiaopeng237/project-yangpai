当win下更改脚本后输入以下指令，更改win和linux的格式差
sed -i 's/\r$//' daemon-yp.sh

拉取后修改一下CmakeList.txt变量地址
set(TOOLCHAIN_DIR "/home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/")
