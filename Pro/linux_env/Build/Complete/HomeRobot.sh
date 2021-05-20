
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
repohome -b atom_n_mr1_release -m apq8053/apq8053-recent.xml
repo sync -c -j8
repo start atom_n_mr1_release --all

echo "================================================="
echo "build android ........................."
echo "================================================="
cd ~/${name}/android/
export USE_PEGA_PREBUILT=true
export USE_LGE_MOTOR_INTERFACE=true
source ./build/envsetup.sh
lunch r2d2-userdebug
m -j32

echo "================================================="
echo "build non_HLOS ........................."
echo "================================================="
cd ~/${name}/non_HLOS/
./build_nonhlos.sh r2d2

cd ~/${name}/non_HLOS/common/build
python build.py

cd ~/${name}/RELEASE/
./release_image.sh r2d2


