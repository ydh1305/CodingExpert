#!/bin/sh
PATHNAME=$(pwd)

if [ -e "$PATHNAME/.repo" ]
then
    echo ".repo exists!!"
    read -p "Are you trying additional git download? (y/n) "
    case $REPLY in
    [Yy])
        read -p "Input git name (max 3): " gitname1 gitname2 gitname3
        if [ -z $gitname1 ]
        then
            echo "[Error] git name no input"
            exit 1
        fi
        echo "repo sync $gitname1 $gitname2 $gitname3 --no-tags -qcj32"
        repo sync $gitname1 $gitname2 $gitname3 --no-tags -qcj32

        if [ $? -ne 0 ]
        then
            echo "[Error] repo sync fail"
            exit 1
        fi

        if [ -e "$PATHNAME/.repo/config_repocmd" ]
        then
            read branch < $PATHNAME/.repo/config_repocmd
            echo "repo start $branch --all"
            repo start $branch --all
        else
            echo "Success! but, if you need to upload commit, input 'repo start command' yourself"
        fi
        exit 0
    ;;
    [Nn])
        echo "Start new download"
    ;;
    *)
        echo "[Error] input y or n, please re-run repocmd"
        exit 1
    ;;
    esac
fi

read -p "Input branch name: " branch

if [ -z $branch ]
then
    echo "[Error] branch name no input"
    exit 1
fi

read -p "Input manifest: " manifest
read -p "Full donwload? (Y/n) " full

if [ -z $full ]
then
    full=y
fi

if [[ $full != [Nn] ]] && [[ $full != [Yy] ]]
then
    echo "[Error] input y or n or enter for default(y), please re-run repocmd"
    exit 1
fi 

if [ $full = n ]
then
    read -p "Input git name (max 3): " gitname1 gitname2 gitname3
    if [ -z $gitname1 ]
    then
        echo "[Error] git name no input"
        exit 1
    fi
fi

if [ -z $manifest ]
then
    echo "repolr -b $branch --reference=/home001/mirror/lr"
    repolr -b $branch --reference=/home001/mirror/lr
else
    echo "repolr -b $branch -m $manifest --reference=/home001/mirror/lr"
    repolr -b $branch -m $manifest --reference=/home001/mirror/lr
fi

if [ -e "$PATHNAME/.repo/config_repocmd" ]
then
    rm -rf "$PATHNAME/.repo/config_repocmd"
fi
echo $branch > $PATHNAME/.repo/config_repocmd

if [ ! -e "$PATHNAME/.repo/manifest.xml" ] || [ ! -e "$PATHNAME/.repo/manifests" ]
then
    echo "[Error] repolr fail"
    exit 1
fi

echo "repo sync $gitname1 $gitname2 $gitname3 --no-tags -qcj32"
repo sync $gitname1 $gitname2 $gitname3 --no-tags -qcj32

if [ $? -ne 0 ]
then
    echo "[Error] repo sync fail"
    exit 1
fi

echo "repo start $branch --all"
repo start $branch --all
