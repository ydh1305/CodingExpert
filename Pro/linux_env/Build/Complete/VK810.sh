
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
repolr -b apq8064_l_altev_vzw_mp_150324 --reference=/home001/mirror/lr
repo sync -c -j16
repo start apq8064_l_altev_vzw_mp_150324 --all

echo "================================================="
echo "make mkscope & tags"
echo "================================================="
#cd ~/${name}/android/
#~/mkcscope.sh
#cd ~/${name}/non_HLOS_8926/
#~/mkcscope.sh

echo "================================================="
echo "build android ........................."
echo "================================================="
cd ~/${name}/android/
source ./build/envsetup.sh
choosecombo 1 altev_vzw 2
m -j16

echo "================================================="
echo "build non_HLOS ........................."
echo "================================================="
cd ~/${name}/MDM9x15_LA165_NI40/
./build_target.sh -b all altev

echo "================================================="
echo "build Full ........................."
echo "================================================="
cd ~/${name}/
./release_image.sh altev_vzw
cd ~
echo "================================================="
echo "FINISH_Build"
echo "================================================="
