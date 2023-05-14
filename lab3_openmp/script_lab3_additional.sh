for SCHEDULE in static dynamic guided
do
    for CHUNKSIZE in 1 4 8 10
    do
        echo "Running lab3 with schedule=$SCHEDULE and chunk_size=$CHUNKSIZE"
        for N in {300000..660000..30000}
        do
                ./lab3_schedule $N 8 $SCHEDULE $CHUNKSIZE >> lab3_${SCHEDULE}_${CHUNKSIZE}_threads8.txt
        done
    done
done