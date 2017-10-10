for i in ./TEST_PLACE/*
do
if [ ! -d "$i/RX/$1" ]; then
            cp $i/RX/$1 TEST_PLACE/

fi
done
