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
repoauto -b alliance_q_release -m renault_manifest_dev.xml
repo sync -qc --no-tags -j16
repo start alliance_q_release --all

echo "================================================="
echo "Andriud Build ........................."
echo "================================================="
cd ~/${name}/android/
export B1_BUILD=n
source build/envsetup.sh 
lunch aivi2_core-userdebug
make -j16 2>&1 | tee build.log

echo "================================================="
echo "non HLOS Build ........................."
echo "================================================="
cd ~/${name}/non_HLOS/
./build_target_aivi2.sh aivi2_core

echo "================================================="
echo "Packaging ........................."
echo "================================================="
cd ~/${name}/
./release_image_sa6150p_bdv.sh

