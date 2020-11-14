####=============================####
####      build Script shell     ####
####=============================####
function copy_dll() {
    to_copy=$1;
    destination="./build";

    if [[ ! -f ${to_copy} ]];
    then 
      echo "Invalid resource "${to_copy};
      echo "exiting...";
      exit -1;
    else
      cp ${to_copy} ${destination};
    fi
}

echo "Cleanup build artifcats..."
rm -f ./build/*;
echo "Making runnable file 'metro.exe'..."
make metro -f makefile;
echo "Copying resource..."
copy_dll "./sdk/SDL2/bin/SDL2.dll";