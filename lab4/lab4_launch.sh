
   
        echo "Running lab4"
        for N in {200..20600..400}
        do
                ./lab4_additional $N 1 | grep -oP '\d+\.\d+' >> lab4_additional.txt
        done