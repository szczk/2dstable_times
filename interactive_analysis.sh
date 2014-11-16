#! /bin/bash

#cd ~/mean_passages2/
# module add gcc/4.5.3
# make

#if [ ${USER} = "ufszczep" ];
#then
#module add gcc/4.5.3
#module add fftw

#make -f makefile_zeus
#else
#make
#fi


#rm *.png
#rm *.txt
touch jobs_ids.txt

tmpdir="/tmp/"
storagedir="./"
threads=4
# /mnt/lustre/scratch/people/ufszczep/
# /storage/ufszczep/

if [ ${USER} = "ufszczep" ];
then
  tmpdir="\/mnt\/lustre\/scratch\/people\/ufszczep\/"
# storagedir="\/storage\/ufszczep\/"
  storagedir="\/mnt\/lustre\/scratch\/people\/ufszczep\/output\/"

  threads=1
fi 

echo "tmp dir: '$tmpdir'"
echo "storage dir: '$storagedir'"


echo "\n"

# zeby byla kropka w wynikach 'seq' a nie przecinek
export LC_NUMERIC="en_US.UTF-8"


for alpha in 1.5 1.7 1.9 2.0 
do
   for beta in 1.0 
   do
       for sigma in 1.0  #$(seq -w 0.2 0.2 5.0)
       do
	      if [ ${USER} = "ufszczep" ];
	      then
		./analysis.x --alpha $alpha --beta $beta --noise $sigma --storage "$STORAGE/2dstable_times/" --data "$SCRATCH/stable_times/"  --tmp "$SCRATCH"  --data_file_num 5
	      else
		./analysis.x --alpha $alpha --beta $beta --noise $sigma --storage "./results" --data "./data"  --tmp "/tmp" --data_file_num 10
	      fi
       done
   done
done


#text=$(tr '\n' ':' <jobs_ids.txt)

#qsub -W depend=afterok:$text  -f "plot_job.pbs"

# 0.5 0.7 0.9 1.1 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2.0 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3.0 3.1 3.2 3.3 3.4 3.5 3.6 3.7 3.8 3.9 4.0 4.1 4.2 4.3 4.4 4.5
