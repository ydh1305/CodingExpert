#donghyun.yoon@lge.com
#repo sync & make cscope files

if [ $# = 1 ]
then
    name=$1
else
	echo "================================================="
	echo "Please Enter your folder name"
	echo "ex> AI_SPEAKER_0124 (FOLDER_NAME)"
	echo "================================================="
    exit
fi

cd ~
echo "================================================="
echo "Delete all files"
echo "================================================="
rm -rf ${name}/
mkdir ${name}/
echo "================================================="
echo "repo sync source"
echo "================================================="
cd ~/${name}/
repo init -u ssh://"donghyun.yoon"@165.243.137.21:29488/yocto-aud-basic/manifest.git -b mt8516-yocto-linux
repo sync -qcj16 --no-tags
repo start mt8516-yocto-linux --all

echo "================================================="
echo "Full Build ........................."
echo "================================================="
cd ~/${name}/
export TEMPLATECONF=${PWD}/meta/meta-mediatek-mt8516/conf/base/lge-gva-8516-mt7668-slc-32b-user-toshiba
source meta/poky/oe-init-build-env
bitbake lge-image-gva-8516-32b 2>&1 | tee build.log
