#! /usr/bin/env bash

set -o errexit
set -o pipefail
set -o nounset

function log_info()
{
  log_ "info" "$@"
}

function log_()
{
  local type=$1
  local message=$2
  local date_str=; date_str=$(date +'%Y-%m-%d %H:%M:%S')
  echo "[${type}] [${date_str}] ${message}"
}

function main() {
  work_dir=../solution
  supp_dir=../support
  local bin=solution

  log_info "Stage #1 Compiling..."
  if ! (cd ${work_dir} && make clean && make) ; then
    echo "ERROR: Failed to compile file."
    exit 1
  fi

  log_info "Stage #2 Test generating..."
  local test_dir=../tests
  rm -rf ${test_dir}
  mkdir -p ${test_dir}
  if ! (cd ${supp_dir} && python3 generator.py) ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
  fi

  log_info "Stage #3 Checking..."
  for test_file in $(ls ${test_dir}/*.t); do
    echo "Execute ${test_file}"
    local tmp_output=${test_dir}/tmp
    if ! ${work_dir}/${bin} < ${test_file} > ${tmp_output} ; then
      echo "ERROR"
      continue
    fi
    answer_file="${test_file%.*}"

    if ! diff -u "${answer_file}.a" ${tmp_output} ; then
      echo "Failed ${test_file}"
    else
      echo "Test ${test_file} OK"
    fi
  done

  rm ${tmp_output}
  rm -rf ${test_dir}
  cd ${work_dir} && make clean
}

main $@