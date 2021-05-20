
#donghyun.yoon@lge.com
#repo sync & make cscope files

if [ $# = 1 ]
then
    name=$1
else
	echo "================================================="
	echo "Please Enter your folder name"
	echo "ex> lamp_l_release (FOLDER_NAME)"
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
repo init -u ssh://mod.lge.com:29421/HomeRobot/manifest.git -b dev -m default.xml
repo sync -c -j8
repo start dev --all

echo "================================================="
echo "build android ........................."
echo "================================================="
cd ~/${name}/android/
export USE_PEGA_PREBUILT=true
source ./build/envsetup.sh
lunch r2d2-userdebug
m -j8

echo "================================================="
echo "build non_HLOS ........................."
echo "================================================="
export USE_PEGA_PREBUILT=true
source build/envsetup.sh
cd vendor/qcom/nonhlos/source
./conv_build_nonhlos.sh r2d2

echo "================================================="
echo "build Full ........................."
echo "================================================="
chmod 755 conv_pack.py
python conv_pack.py
cd deploy/fastboot/

echo "================================================="
echo "FINISH_Build"
echo "================================================="

echo "================================================="
echo "make mkscope & tags"
echo "================================================="
#cd ~/${name}/android/kernel
#~/mkcscope.sh
#cd ~/${name}/non_HLOS_8926/
#~/mkcscope.sh

