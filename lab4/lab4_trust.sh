for N in {200..20600..400}
do
    ./lab4_trust $N 1 >> output.txt

    lower_bound=$(grep "lower" output.txt | awk '{print $2}')
    upper_bound=$(grep "upper" output.txt | awk '{print $2}')

    echo "$lower_bound" > lower_bound.txt
    echo "$upper_bound" > upper_bound.txt
done
