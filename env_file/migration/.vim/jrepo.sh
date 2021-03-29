############################################################
# Concurrent repo forall utility
#    made by Kihyung Lee (kihyung2.lee@lge.com)

function do_command() {
    local PROJECT_LIST=`cat .repo/project.list`
    local MY_TURN=$1
    local NUM_AT_ONCE=$2
    local i=0

    for v in ${PROJECT_LIST[@]}
    do
        if [ $(($i % $NUM_AT_ONCE)) = $MY_TURN ]; then
            pushd $v >> /dev/null
            export REPO_PATH=$v
            export REPO_REMOTE=`git remote | head -1`
            export REPO_PROJECT=`git config remote.${REPO_REMOTE}.projectname`
            echo -e "${@:3}\n" | bash
            popd >> /dev/null
        fi
        i=$(($i + 1))
    done
}

function launch_sub_processes() {
    local repo_root="."
    while [ ! -d "${repo_root}/.repo" ]; do repo_root="../${repo_root}"; done
    pushd $repo_root >> /dev/null

    local n=0
    local PIDs
    while [ $n -lt $1 ]; do
        $SELF $n/$1 ${@:2} &
        PIDs[$n]=$!
        n=$(($n + 1))
    done

    # Wait for child processes done...
    for v in ${PIDs[@]}; do
        while [ -d "/proc/$v" ]; do sleep 0.1; done
    done

    popd >> /dev/null
}

SELF=$0
SELF_DIR=`expr "$SELF" : '\(.*/\)[^/]*'`
SELF_SCRIPT=${SELF#${SELF_DIR}}
SELF="`cd $SELF_DIR && pwd`/$SELF_SCRIPT"

PARAM_NTH=`expr "$1" : '\([0-9]*\)/*'`
PARAM_OVER_N=`expr "$1" : '.*/\([0-9]*\)'`

if [ "$PARAM_OVER_N" ]; then
    do_command $PARAM_NTH $PARAM_OVER_N ${@:2}
elif [ "$PARAM_NTH" ]; then
    launch_sub_processes $1 ${@:2}
else
    echo -e "Error: Invalid argument."
    echo -e "Sample Usage with 10 concurrent jobs:"
    echo
    echo -e "\tjrepo.sh 10 'COMMAND arg1 arg2 ...'"
    echo
    echo -e "You can also use variables such as \${REPO_PATH}, \${REPO_REMOTE} and \${REPO_PROJECT}."
    echo -e "Try following example to understand the usage of those variables:"
    echo
    echo -e "\tjrepo.sh 10 'echo PATH: \${REPO_PATH}, REMOTE: \${REPO_REMOTE} && echo PROJECT: \${REPO_PROJECT}'"
    echo
fi