
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
repolr -b lamp_n_mr2_release -m msm8909/msm8909.xml --reference=/home001/mirror/lr/
repo sync -c -j32
repo start lamp_n_mr2_release --all

echo "================================================="
echo "build android ........................."
echo "================================================="
cd ~/${name}/android/
source ./build/envsetup.sh
choosecombo 1 cv109_lao_com 2
m -j32
#source ./build/envsetup.sh
#choosecombo 1 z_tmo_us 2
#m -j8
#source ./build/envsetup.sh
#choosecombo 1 z_att_us 2
#m -j8
echo "================================================="
echo "build non_HLOS ........................."
echo "================================================="
cd ~/${name}/non_HLOS/
./build_target.sh cv109_lao_com
echo "================================================="
echo "build Full ........................."
echo "================================================="
cd ~/${name}/
./release_image.sh cv109_lao_com
dhwlghks1!
cd ~
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

