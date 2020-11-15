####=============================####
####      build Script shell     ####
####=============================####
function copy_mv_res() {
    to_copy=$1;
    cmd=$2;
    destination=$3;

    if [[ -d ${to_copy} ]];
    then
      echo "resource is directory, copy recursivly...";
      cmd=${cmd}" -a";
    elif [[ ! -f ${to_copy} ]];
    then 
      echo "Invalid resource "${to_copy};
      echo "exiting...";
      exit -1;
    fi
    ${cmd} ${to_copy} ${destination};
}

echo "Cleanup build artifcats..."
rm -Rf ./build/*;
echo "Making runnable file 'metro.exe'..."
make metro -f makefile;
echo "Copying resource..."
copy_mv_res "./sdk/SDL2/bin/SDL2.dll" "cp" "./build";
copy_mv_res "./metro.exe" "cp" "./build";
copy_mv_res "./assets" "cp" "./build/";