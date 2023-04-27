N1=300000
N2=660000
delta=30000
echo "Running lab2_WO_sort M=1"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=1"
    ./lab2_gcc_WO_sort $N 1 >> lab2_WO_sort_1_Additional.txt
done
echo "Running lab2-gcc M=2"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=2"
    ./lab2_gcc_WO_sort $N 2 >> lab2_WO_sort_2_Additional.txt
done
echo "Running lab2-gcc M=3"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=3"
    ./lab2_gcc_WO_sort $N 3 >> lab2_WO_sort_3_Additional.txt
done
echo "Running lab2-gcc M=4"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=4"
    ./lab2_gcc_WO_sort $N 4 >> lab2_WO_sort_4_Additional.txt
done
