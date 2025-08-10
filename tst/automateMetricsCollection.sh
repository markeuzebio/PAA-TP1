#!/bin/bash

ROOT_DIR="$( cd .. >/dev/null 2>&1 ; pwd -P )";
INPUT_FILES_DIR="${ROOT_DIR}/input_files"
APP_DIR="${ROOT_DIR}/app"

METRICS_OUT_FILE="metrics.txt"

# Compile the project
(cd $ROOT_DIR ; make 1>/dev/null ; make gen 1>/dev/null)

printf "%-20s%-20s%-20s\n" DINAMICO BACKTRACKING BRANCH-AND-BOUND > ${METRICS_OUT_FILE};
printf "%.0s-" {1..58} >> ${METRICS_OUT_FILE}

W=10

# Initially W = 10 and N increases
for ((N = 100 ; N <= 1000 ; N += 100)); do
    printf "\n\nW = ${W}\tN = ${N}" >> ${METRICS_OUT_FILE}

    input_file_name="w${W}_n${N}.txt"

    for ((i = 1 ; i <= 10 ; i++)); do
        # Generate instances with W = 10 and N = ${N}
        (cd ${INPUT_FILES_DIR} ; ./exe ${W} ${N} && mv ${input_file_name} ${APP_DIR})
        t_dynamic=$(cd ${APP_DIR} && ./exe ${input_file_name} dynamic | egrep -o '[0-9]\.[0-9]+s')
        t_backtracking=$(cd ${APP_DIR} && ./exe ${input_file_name} backtracking | egrep -o '[0-9]\.[0-9]+s')
        t_branch_n_bound=$(cd ${APP_DIR} && ./exe ${input_file_name} bnb | egrep -o '[0-9]\.[0-9]+s')

        printf "\n%-20s%-20s%-20s" ${t_dynamic} ${t_backtracking} ${t_branch_n_bound} >> ${METRICS_OUT_FILE};
    done
done

# Now N and W increases at the same rate
for ((N = 100 ; N <= 1000 ; N += 100)); do
    W=$N
    printf "\n\nW = ${W}\tN = ${N}" >> ${METRICS_OUT_FILE}
    input_file_name="w${W}_n${N}.txt"

    for ((i = 1 ; i <= 10 ; i++)); do
        # Generate instances with W = 10 and N = ${N}
        (cd ${INPUT_FILES_DIR} ; ./exe ${W} ${N} && mv ${input_file_name} ${APP_DIR})
        t_dynamic=$(cd ${APP_DIR} && ./exe ${input_file_name} dynamic | egrep -o '[0-9]\.[0-9]+s')
        # t_backtracking=$(cd ${APP_DIR} && ./exe ${input_file_name} backtracking | egrep -o '[0-9]\.[0-9]+s')
        t_backtracking="N/A"
        t_branch_n_bound=$(cd ${APP_DIR} && ./exe ${input_file_name} bnb | egrep -o '[0-9]\.[0-9]+s')

        printf "\n%-20s%-20s%-20s" ${t_dynamic} ${t_backtracking} ${t_branch_n_bound} >> ${METRICS_OUT_FILE};
    done
done