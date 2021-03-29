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
rm -rf ~/Project/${name}/
mkdir ~/Project/${name}/
echo "================================================="
echo "repo sync source"
echo "================================================="
cd ~/Project/${name}/
repo init -u ssh://mod.lge.com:29456/platform/manifest.git -b vmb_sa8155
repo sync -c -j4 --no-tags
repo start vmb_sa8155 --all
cd apps_proc/build-webos-auto-GVM
./mcf -p 16 -b 16 qtiquingvm

echo "================================================="
echo "webOS Build ........................."
echo "================================================="
source oe-init-build-env
bitbake webos-auto-image

echo "================================================="
echo "Packaging ........................."
echo "================================================="

