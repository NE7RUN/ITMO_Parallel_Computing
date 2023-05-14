N1=300000
N2=660000
delta=30000
echo "Running lab3 M=1"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=1"
    ./lab3_try $N 1 >> lab3_ex4_1.txt
done
echo "Running lab3 M=2"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=2"
    ./lab3_try $N 2 >> lab3_ex4_2.txt
done
echo "Running lab3 M=3"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=3"
    ./lab3_try $N 3 >> lab3_ex4_3.txt
done
echo "Running lab3 M=4"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=4"
    ./lab3_try $N 4 >> lab3_ex4_4.txt
done
echo "Running lab3 M=6"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=6"
    ./lab3_try $N 6 >> lab3_ex4_6.txt
done
echo "Running lab3 M=8"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=8"
    ./lab3_try $N 8 >> lab3_ex4_8.txt
done
echo "Running lab3 M=10"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=10"
    ./lab3_try $N 10 >> lab3_ex4_10.txt
done
echo "Running lab3 M=12"
for ((N=$N1; N<=$N2; N+=$delta))
do
    echo "N=$N"
    echo "M=12"
    ./lab3_try $N 12 >> lab3_ex4_12.txt
done