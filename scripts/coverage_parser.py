#!/usr/local/bin/python

# change above line to point to local
# python executable

import getopt
import sys
from bs4 import BeautifulSoup


def main(argv):
    try:
        opts, args = getopt.getopt(argv, "i:", ["ifile="])
    except getopt.GetoptError:
        usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt in ("-i", "--ifile"):
            inputfile = arg

    f = open(inputfile)  # simplified for the example (no urllib)
    soup = BeautifulSoup(f, features="html.parser")
    f.close()

    line_details = soup.find("td", text="Lines:")
    stats_lines_executed = line_details.find_next(attrs={"class": "headerTableEntry"})
    stats_lines_total = stats_lines_executed.find_next(attrs={"class": "headerTableEntry"})
    stats_lines_coverage = stats_lines_total.find_next(attrs={"class": "headerTableEntry"})

    branch_details = soup.find("td", text="Legend:")
    stats_branch_executed = branch_details.find_next(attrs={"class": "headerTableEntry"})
    stats_branch_total = stats_branch_executed.find_next(attrs={"class": "headerTableEntry"})
    stats_branch_coverage = stats_branch_total.find_next(attrs={"class": "headerTableEntry"})
    print('Coverage Stats:')
    print('--------------------------')
    print('lines_executed: {}\nlines_total: {}\nlines_coverage: {}'.format(stats_lines_executed.text,
                                                                         stats_lines_total.text,
                                                                         stats_lines_coverage.text))
    print('\nbranch_executed: {}\nbranch_total: {}\nbranch_coverage: {}'.format(stats_branch_executed.text,
                                                                            stats_branch_total.text,
                                                                            stats_branch_coverage.text))
    print('---------------------------\n')


def usage():
    print(' ------------------------------------------------')
    print(' Mrunmoy Samal (mrunmoy@gmail.com) , 2018')
    print(' python coverage_parser.py -i coverage-html-filename')
    print(' ------------------------------------------------')


# -------------------------------
if __name__ == "__main__":
    main(sys.argv[1:])
