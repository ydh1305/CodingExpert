if test -z $2
then
# All repo sync mirror & no_tags
echo $1 repsy init
repolr -b lamp_l_release -m $1.xml --reference=/home001/mirror/lr/
echo $1 repo sync
repo sync --no-tags -cqj16
repo start lamp_l_release --all

else
if test -z $3
then
# Part repo sync mirror & no_tags 
echo $1 repsy init
repolr -b lamp_l_release -m $1.xml --reference=/home001/mirror/lr/

echo $1 repo sync $2
repo sync $2 --no-tags -cqj16
else
# Part repo for upload
echo $1 repsy init
repolr -b lamp_l_release -m $1-recent.xml

echo $1 repo sync $2
repo sync $2 -cqj16
fi
repo start lamp_l_release --all
fi
