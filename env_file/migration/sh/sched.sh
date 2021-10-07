echo "********************************************"
echo "Input Target Name"
echo "ex) my_source_folder < default : msm8x26_kk_mr1_release >"
echo "********************************************"
read TARGET_NAME
if [ ! "${TARGET_NAME}" ];
then
TARGET_NAME=msm8x26_kk_mr1_release
fi

echo "********************************************"
echo "Input Target Time (current time $(date +%H:%M))"
echo "ex) 01:30 < default 22:30 >"
echo "********************************************"
read TARGET_TIME
if [ ! "${TARGET_TIME}" ];
then
TARGET_TIME=22:30
fi

echo "********************************************"
echo "Input Build Shell Command"
echo -e "ex) repo sync < default './Jaguar_build.sh' >"
echo "********************************************"
read TARGET_CMD
if [ ! "${TARGET_CMD}" ];
then
TARGET_CMD=./Jaguar_build.sh" "${TARGET_NAME}
fi

echo -e "When reach to ${TARGET_TIME}, '${TARGET_CMD}' will be executed."

PINWHEEL="/"

while [ 1 ]; do
CURR_TIME=$(date +%H:%M)
	if [ "${PINWHEEL}" == "-" ];
	then
	PINWHEEL="\\"
	else
		if [ "${PINWHEEL}" == "\\" ];
		then
		PINWHEEL="|"
		else
			if [ "${PINWHEEL}" == "|" ];
			then
			PINWHEEL="/"
			else
			PINWHEEL="-"
			fi
		fi
	fi
echo -ne "\\rCurrent time is ${CURR_TIME} ${PINWHEEL} "
if [ "${TARGET_TIME}" == "${CURR_TIME}" ];
then
$TARGET_CMD
date
exit 0
else
sleep 3
fi
done;
