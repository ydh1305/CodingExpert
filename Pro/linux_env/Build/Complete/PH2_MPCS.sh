
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
repolr -b lamp_m_mr1_release -m msm8937/msm8937.xml
repo sync -c -j32
repo start lamp_m_mr1_release --all

echo "================================================="
echo "build android ........................."
echo "================================================="
cd ~/${name}/android/
source ./build/envsetup.sh
choosecombo 1 ph2n_mpcs_us 2
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
./build_target.sh ph2n_mpcs_us
echo "================================================="
echo "build Full ........................."
echo "================================================="
cd ~/${name}/
./release_image.sh ph2n_mpcs_us
cd ~
echo "================================================="
echo "FINISH_Build"
echo "================================================="

echo "================================================="
echo "make mkscope & tags"
echo "================================================="
cd ~/${name}/android/kernel
~/mkcscope.sh
#cd ~/${name}/non_HLOS_8926/
#~/mkcscope.sh

