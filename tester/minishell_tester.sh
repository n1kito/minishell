#!/bin/bash

# Usage: ./tokenizer_tester
# To add more tests, add them to the corresponding sections below.

################################################################################
##                             USEFUL VARIABLES                               ##
################################################################################

EXECUTABLE_PATH="."
TEST_FILES_DIRECTORY="tests"

# Variables used to dynamically count the number of tests ran.
TEST_COUNT=0
TEST_PASSED=0

## RETURNS
################################################################################

OK="[OK]"
KO="❌"

## COLORS
################################################################################

RED='\033[0;31m'
BRED='\033[1;31m'
GREEN='\033[0;32m'
BGREEN='\033[1;32m'
YELLOW='\033[0;33m'
ITALIC='\e[3m'
CODE='\e[1;41;100m' # White text on grey background
# CODE='\e[7m' # Second option, this one just inverts
NC='\033[0m' # No Color
SEPARATOR='░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░'

################################################################################
##                                  HEADER                                    ##
################################################################################

## DISPLAY TITLE
clear -x # clears screen, equals to CTRL + L in Terminal

echo
echo "$SEPARATOR";
echo
echo "      ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    ";
echo "     ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    ";
echo "     ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    ";
echo "     ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    ";
echo "     ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒";
echo "     ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░";
echo "     ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░";
echo "     ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   ";
echo "            ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░";
printf "                            \e[2m(tester by nikito 🔥)\e[22m"
printf "\n\n\n"

################################################################################
##                             PRELIMINARY CHECKS                             ##
################################################################################

# Checks that:
#   - The directory that holds the test files exists.
#   - That it actually has files in it.
#   - (The individual files checks are done in the testing function).

if [ -d "${TEST_FILES_DIRECTORY}" ]
then
      TEST_FILES_CHECK=$(ls $TEST_FILES_DIRECTORY | wc -l)
      if [ "$TEST_FILES_CHECK" -eq 0 ]; then
        printf "\n         ⚠️  ${BRED}Error${NC}${RED}: there are no test files in the ${BRED}${TEST_FILES_DIRECTORY}${NC}${RED}/ directory${NC} ⚠️\n"
        printf "\n               ${ITALIC}Come back when you have some tests to run 💅${NC}\n"
        printf "\n${SEPARATOR}\n\n"
        exit
     fi
else
      printf "\n              ⚠️  ${BRED}Error${RED}: the ${BRED}${TEST_FILES_DIRECTORY}${NC}${RED}/ directory does not exist${NC} ⚠️\n"
      printf "\n               ${ITALIC}Come back when you have some tests to run 💅${NC}\n"
      printf "\n${SEPARATOR}\n\n"
      exit
fi

################################################################################
##                            TESTING LOOP FUNCTION                           ##
################################################################################

# run_tests()
# Argument 1: Testing Category
# Argument 2: name of the test file

run_tests() {

  # Print test title

  printf "\n \e[4m$1\e[24m:\n"

  # This section checks that the test file exists and that it is not empty.
  # If it is not empty, it checks that the file has at least 2 lines in it.

  if [ -f "${TEST_FILES_DIRECTORY}/$2" ]; then
    FILE_CHECK=$(cat ${TEST_FILES_DIRECTORY}/$2 | wc -l)
    if [ "$FILE_CHECK" -eq 0 ]; then
      printf " ${BRED}Error: ${RED}There are no tests in the \"$2\" file.${NC}\n"
      return
    elif [ "$FILE_CHECK" -lt 2 ]; then
      printf " ${BRED}Error: ${RED}The \"$2\" file has less than 2 lines. That's not a test.${NC}\n"
      return
    fi
  else
    printf " ${BRED}Error: ${RED}\"$2\" file does not exist.${NC}\n"
    return
  fi

  # This is the test loop
  # Thanks @alienard for showing me how to use the read function in a loop :)

  i=0
  input="$TEST_FILES_DIRECTORY/$2"
  while IFS= read -r TEST
  do
    IFS= read -r EXPECTED_RESULT
    RESULT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "$TEST" 2>/dev/null)
    if [ "$RESULT" = "$EXPECTED_RESULT" ]; then # COMPARES RESULT WITH CORRESPONDING EXPECTED RESULT
          printf " ${GREEN}[${i}.${NC}${BGREEN}OK${NC}${GREEN}]${NC} " # IF RESULT MATCHES EXPECTED_OUTPUT, PRINT 'OK'
          (( TEST_PASSED++ ))
          (( TEST_COUNT++ ))
    else
          printf "\n ${RED}${KO}${NC}\t${RED}Tested:  ${NC} ${CODE}%s${NC} \n\t${RED}Expected:${NC} ${CODE}%s${NC}\n\t${RED}Returned:${NC} ${CODE}%s${NC}${RED}${NC}\n" "$TEST" "$EXPECTED_RESULT" "$RESULT" # IF RESULTS DON'T MATCH, PRINT 'KO' ND SHOW TEST, EXPECTED OUTPUT AND RESULT
          (( TEST_COUNT++ ))
    fi
    IFS= read -r TEST

    # this statement inserts a new line every 9 tests
    if [ $i != "0" ]; then
      if [ "$(( $i % 8 ))" = "0" ]; then
        echo
      fi
    fi
    #
    (( i++ ))
  done < "$input"
  echo
}

################################################################################
##                                  TOKENIZER                                 ##
################################################################################

printf "${YELLOW}                         ┌┬┐┌─┐┬┌─┌─┐┌┐┌┬┌─┐┌─┐┬─┐   ${NC}\n";
printf "${YELLOW}                      **  │ │ │├┴┐├┤ ││││┌─┘├┤ ├┬┘ **${NC}\n";
printf "${YELLOW}                          ┴ └─┘┴ ┴└─┘┘└┘┴└─┘└─┘┴└─   ${NC}\n";

# Running make

printf "\n"
printf "                      🌈 Running ${YELLOW}make${NC} on Tokenizer...\n"
make --no-print-directory tokenizer

# Running tests

EXECUTABLE="tokenizer"
run_tests "Word tokens" "word_tests"
run_tests "Operator tokens" "operator_tests"
run_tests "Quote tokens" "quote_tests"
run_tests "Environment variable tokens" "environment_tests"
run_tests "Symbols we don't need to handle" "symbol_tests"

printf "\n\n";

################################################################################
##                                   PARSER                                   ##
################################################################################
printf "${YELLOW}                             ╔═╗╔═╗╦═╗╔═╗╔═╗╦═╗   ${NC}\n";
printf "${YELLOW}                          ** ╠═╝╠═╣╠╦╝╚═╗║╣ ╠╦╝ **${NC}\n";
printf "${YELLOW}                             ╩  ╩ ╩╩╚═╚═╝╚═╝╩╚═   ${NC}\n";

# Running make

printf "\n"
printf "                        🌈 Running ${YELLOW}make${NC} on Parser...\n"
make --no-print-directory parser

# Running tests

EXECUTABLE="parser"
run_tests "Parsing tests" "parser_tests"
run_tests "Syntax error tests" "syntax_error_tests"

rm expander
make --no-print-directory expander
EXECUTABLE="expander"
run_tests "Expansion and quote removal tests" "expansion_tests"
echo

################################################################################
##                                PRINT RESULTS                               ##
################################################################################

printf " \e[4mTests passed\e[24m: "
if [ ${TEST_PASSED} -eq ${TEST_COUNT} ]
then
  printf "✅ ${GREEN}${TEST_PASSED}/${TEST_COUNT}${NC}"
else
  printf "\e[5m💀\e[0m ${BRED}${TEST_PASSED}${NC}/${TEST_COUNT}"
fi

echo
echo
echo "$SEPARATOR";
echo
