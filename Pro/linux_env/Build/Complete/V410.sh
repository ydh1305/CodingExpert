
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
repolr -b msm8x26_l_e7e9lte_us_mp_150318
repo sync -c -j16
repo start msm8x26_l_e7e9lte_us_mp_150318 --all
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
choosecombo 1 e7lte_att_us 2
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
./build_target.sh e7lte_att_us
echo "================================================="
echo "build Full ........................."
echo "================================================="
cd ~/${name}/
./release_image.sh e7lte_att_us
cd ~
echo "================================================="
echo "FINISH_Build"
echo "================================================="
