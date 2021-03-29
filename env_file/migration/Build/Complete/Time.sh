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
repolr -b lamp_q_release -m sm8250/sm8250.xml
repo sync -cqj32 --no-tags
repo start lamp_q_release --all

echo "================================================="
echo "Full Build ........................."
echo "================================================="
cd ~/${name}/android/
source build/envsetup.sh
lunch timelm-userdebug
make -j32 2>&1 | tee build.log
cd ~/${name}/non_HLOS/
./build_target.sh timelm
cd ~/${name}/
./release_image_sm8250.sh timelm
