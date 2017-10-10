for i in ./TEST_PLACE/*
do
if [ -f "$i/RX/$1" ]; then
	ls -l
	for j in ./TEST_PLACE/*
        do	
	if [ $j != $i ];
	then
	    cp $i/RX/$1 $j/TX/$1
	fi
	done
	rm $i/RX/$1
fi
done
