#!/bin/bash

#this is cscope/c${TAGS_OUT} index build script
#[jongho3.lee@lge.com] 2010.04.17
#

#############variables###########################
REF_DIR=~/workspace/.cscopefiles/
CUR_DIR=`pwd`
BASE_DIR=`basename $CUR_DIR`
PROJECT_NAME=$BASE_DIR

CSCOPE_FILES=cscope.files
CSCOPE_FILES2=cscope.out.in
CSCOPE_FILES3=cscope.out.po
CSCOPE_OUT=cscope.out
TAGS_OUT=tags

############functions#############################

mvfiles ()
{
	FILE_FROM=$1
	FILE_TO=$2

		if [ -f ${REF_DIR}${FILE_TO} ]
		then
		mv -f ${REF_DIR}${FILE_TO} ${REF_DIR}${FILE_TO}.bak
		fi
		mv -f ${FILE_FROM} ${REF_DIR}${FILE_TO}
}

############ code ###############################
echo " "
echo "################################### "
echo "building cscope.files ...."
find $1 ! \( -type d -path './android/external' -prune \) -type f \(  -iname '*.c' -o -iname '*.cpp' -o -iname '*.cc' -o -iname '*.h' -o -iname '*.java' -o -iname '*.jni' -o -iname '*.mk' -o -iname '*.xml' -o -iname '*.aidl' -o -iname '*.s' -o -iname '*.S' -o -iname '*.rc' -o -iname '*.defconfig' -o -iname '*_defconfig'  -o -iname '*.cfg' -o -iname '*.config'  -o -iname '*.min' -o -iname 'Makefile' -o -iname 'Kconfig' -o -iname '*.dts' -o -iname '*.scons' -o -iname '*.dtsi' -o -iname '*.conf' -o -iname '*.sh' \) -print > ${CSCOPE_FILES}

echo " "
echo "################################### "
echo "building cscope.out ...."
cscope -b -q -k -i ${CSCOPE_FILES} -f ${CSCOPE_OUT}

echo " "
echo "################################### "
echo "building ctags ...."
#ctags -R -f ${TAGS_OUT}
#ctags -R ./
ctags -R --sort=1 --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ -f ${TAGS_OUT}
#ctags -R --sort=1 --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ -f cpp cpp_src

set tags+=${CUR_DIR}

#echo "moving index files to ${REF_DIR} ...."

#mvfiles ${CSCOPE_OUT} ${CSCOPE_OUT}
#mvfiles ${TAGS_OUT} ${TAGS_OUT}
#mvfiles ${CSCOPE_FILES} ${CSCOPE_FILES}
#mvfiles ${CSCOPE_FILES2} ${CSCOPE_FILES2}
#mvfiles ${CSCOPE_FILES3} ${CSCOPE_FILES3}


