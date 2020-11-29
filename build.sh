####=============================####
####      build Script shell     ####
####=============================####
function validate_res() {
    to_copy=$1;
    if [[ ! -f ${to_copy} && ! -d ${to_copy} ]];
    then 
      echo "Invalid resource "${to_copy};
      echo "exiting...";
      exit -1;
    fi
}

function copy_mv_res() {
    to_copy=$1;
    cmd=$2;
    destination=$3;
    flat=$4;

    validate_res ${to_copy};

    if [[ -d ${to_copy} ]];
    then
      if [[  ! -z ${flat} && ${flat}="flat" ]];
      then
        echo "resource is directory, copy recursivly (without parent dir)...";
        cmd=${cmd}" -R";
        to_copy=${to_copy}"/*";
      else  
        echo "resource is directory, copy recursivly (includes parent dir)...";
        cmd=${cmd}" -a";
      fi
    fi
    ${cmd} ${to_copy} ${destination};
}

echo "Cleanup build artifcats..."
rm -Rf ./build/*;
find ./src -name "*.o" -exec rm -f {} +;
echo "Making runnable file 'metro.exe'..."
make metro -f makefile;
echo "Copying resource..."
copy_mv_res "./metro.exe" "mv" "./build";
copy_mv_res "./assets" "cp" "./build/";
copy_mv_res "./sdk/SDL2/bin" "cp" "./build" "flat";
copy_mv_res "./sdk/pthread/bin" "cp" "./build" "flat";
