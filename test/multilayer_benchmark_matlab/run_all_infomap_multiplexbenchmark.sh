
rs=(-1 $(seq 0 .1 1))

for r in "${rs[@]}"
    do
    for p in $(.5 .85 .95 .99 1)
        do
        for mu in $(seq 0 0.1 1)
            do
            #echo "${eps} ${gamma} ${omega}"
            sbatch -t 1000 -n 1 -o /nas/longleaf/home/wweir/ModBP_proj/ModularityBP_Cpp/test/multilayer_benchmark_matlab/test_infomap_mulitplex.txt -p general \
            --wrap "python /nas/longleaf/home/wweir/ModBP_proj/ModularityBP_Cpp/test/multilayer_benchmark_matlab/run_multilayer_matlab_test_infomap.py\
            1000 15 ${mu} ${eta} ${r} 1"
            done
        done
    done