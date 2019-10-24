export NEWNAME=$1

set -e

if [ -z ${NEWNAME}]
	then
		exit 1
fi

git clone https://github.com/kracejic/cleanCppProject.git ${NEWNAME}

cd ${NEWNAME}

mv .git .git-cleanCppProject
git init
git add .
git commit -m "first commit"

git mv packaging/exampleApp.desktop    packaging/${NEWNAME}.desktop
git mv packaging/exampleApp.ico        packaging/${NEWNAME}.ico
git mv packaging/exampleApp.icon.in.rc packaging/${NEWNAME}.icon.in.rc
git mv packaging/exampleApp.png        packaging/${NEWNAME}.png

find . -type f -iname "*.*" -exec sed -i -e "s/exampleApp/${NEWNAME}/g" '{}' \;
find . -type f -iname "*.*" -exec sed -i -e "s/cleancpp/${NEWNAME}/g" '{}' \;
find . -type f -iname "*.*" -exec sed -i -e "s/cleanCpp/${NEWNAME}/g" '{}' \;
find . -type f -iname "*cleanCpp*" -exec rename "s/cleanCpp/${NEWNAME}/" '{}' \;

mkdir build
cd build

cmake ../
make

cd source

./${NEWNAME}