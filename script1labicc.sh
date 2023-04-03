N1=1000
N2=38000
delta=3700
echo "Running lab1-icc-par-1"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    ./lab1-icc-par-1 $N >> icc-par-1.txt
done
echo "Running lab1-icc-par-2"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    ./lab1-icc-par-2 $N >> icc-par-2.txt
done
echo "Running lab1-icc-par-4"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    ./lab1-icc-par-4 $N >> icc-par-4.txt
done
echo "Running lab1-icc-par-5"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    ./lab1-icc-par-5 $N >> icc-par-5.txt
done
