for M in 1 2 3 4 8 10 16; do
    echo "running $M threads"
    for N in {200..20600..400}; do
        output=$(./lab5_3 $N $M)
        echo "Output: $output"  # Отладочный вывод

        time=$(echo "$output" | awk -F 'time: ' '{print $2}' | awk -F ' ms' '{print $1}')
        generate=$(echo "$output" | awk -F 'generate: ' '{print $2}' | awk -F ' ms' '{print $1}')
        map=$(echo "$output" | awk -F 'map: ' '{print $2}' | awk -F ' ms' '{print $1}')
        merge=$(echo "$output" | awk -F 'merge: ' '{print $2}' | awk -F ' ms' '{print $1}')
        sort=$(echo "$output" | awk -F 'sort: ' '{print $2}' | awk -F ' ms' '{print $1}')
        reduce=$(echo "$output" | awk -F 'reduce: ' '{print $2}' | awk -F ' ms' '{print $1}')

        echo -n "${time}" | iconv -f UTF-8 -t ASCII//TRANSLIT >> time_${M}_threads.txt
        echo -n "${generate}" | iconv -f UTF-8 -t ASCII//TRANSLIT >> generate_${M}_threads.txt
        echo -n "${map}" | iconv -f UTF-8 -t ASCII//TRANSLIT >> map_${M}_threads.txt
        echo -n "${merge}" | iconv -f UTF-8 -t ASCII//TRANSLIT >> merge_${M}_threads.txt
        echo -n "${sort}" | iconv -f UTF-8 -t ASCII//TRANSLIT >> sort_${M}_threads.txt
        echo -n "${reduce}" | iconv -f UTF-8 -t ASCII//TRANSLIT >> reduce_${M}_threads.txt
    done
done