library=$1 #첫번째 인자
symbols="$*" #모든 인자
symbols=${symbols#$1} #symbols앞에서부터 $1을 찾아 첫번째로 나타나는 패턴 버림 

if [ ! -f $library ];
then echo "library not exist";
else echo "library exist";
echo "libraray size:" $(cat $library | wc -c);
fi

for symbolname in $symbols;
do
echo "libraryname:" $library "symbol:" $symbolname ;
return=$(./build/CheckSymbol ./$library $symbolname);

if [ $? = 0 ]; 
then echo "OK";#최근 명령어의 종료 상태가 정상
else echo "FAIL";
fi

done
