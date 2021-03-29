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
repo init -u ssh://vgit.lge.com:29430/vw/qnx/ICAS3/manifest -b icas3cn_migration_r220_200202
repo sync -qcj16
repo start icas3cn_migration_r220_200202 --all

echo "================================================="
echo "Andriud Build ........................."
echo "================================================="

echo "================================================="
echo "non HLOS Build ........................."
echo "================================================="

echo "================================================="
echo "Packaging ........................."
echo "================================================="

