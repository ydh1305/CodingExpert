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
repolap -b msm8x26_kk_mr1_e7lte_vzw_mp_140719_e9lte_vzw_mp_140810 --reference=/home001/mirror/lap
repo sync -c -j16
repo start msm8x26_kk_mr1_e7lte_vzw_mp_140719_e9lte_vzw_mp_140810 --all
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
choosecombo 1 e9lte_vzw 2
m -j16
#source ./build/envsetup.sh
#choosecombo 1 z_tmo_us 2
#m -j8
#source ./build/envsetup.sh
#choosecombo 1 z_att_us 2
#m -j8
echo "================================================="
echo "build non_HLOS ........................."
echo "================================================="
cd ~/${name}/non_HLOS_8926/
./build_target.sh e9lte_vzw
echo "================================================="
echo "build Full ........................."
echo "================================================="
cd ~/${name}/
./release_image.sh e9lte_vzw
cd ~
echo "================================================="
echo "FINISH_Build"
echo "================================================="
