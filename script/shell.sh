library=$1
symbols="$*"
symbols=${symbols#$1}

if [ ! -f $library ];
then echo "library not exist";
else echo "library exist";
cat $library | wc -c
fi

for symbolname in $symbols;
do
echo "libraryname:" $library "symbol:" $symbolname ;
return=$(./build/CheckSymbol ./$library $symbolname);

if [ $? = 0 ]; 
then echo "OK";
else echo "FAIL";
fi

done
