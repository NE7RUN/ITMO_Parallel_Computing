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
echo "Running lab2_WO_sort M=5"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=5"
    ./lab2_gcc_WO_sort $N 5 >> lab2_WO_sort_5_Additional.txt
done
echo "Running lab2-gcc M=6"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=6"
    ./lab2_gcc_WO_sort $N 6 >> lab2_WO_sort_6_Additional.txt
done
echo "Running lab2-gcc M=7"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=7"
    ./lab2_gcc_WO_sort $N 7 >> lab2_WO_sort_7_Additional.txt
done
echo "Running lab2-gcc M=8"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=8"
    ./lab2_gcc_WO_sort $N 8 >> lab2_WO_sort_8_Additional.txt
done
echo "Running lab2-gcc M=10"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=10"
    ./lab2_gcc_WO_sort $N 10 >> lab2_WO_sort_10_Additional.txt
done
echo "Running lab2-gcc M=12"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=12"
    ./lab2_gcc_WO_sort $N 12 >> lab2_WO_sort_12_Additional.txt
done
