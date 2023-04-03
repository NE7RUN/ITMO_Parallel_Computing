N1=1000
N2=38000
delta=3700
echo "Running lab1-seq..."
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    ./lab1-seq $N >> seq.txt
done
echo "Running lab1-par-1..."
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    ./lab1-par-1 $N >> par-1.txt
done
echo "Running lab1-par-2..."
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    ./lab1-par-2 $N >> par-2.txt
done
echo "Running lab1-par-4..."
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    ./lab1-par-4 $N >> par-4.txt
done
echo "Running lab1-par-5..."
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    ./lab1-par-5 $N >> par-5.txt
done