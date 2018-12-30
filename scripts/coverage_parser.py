#!/usr/local/bin/python

# change above line to point to local 
# python executable

import getopt, sys, urllib2
from bs4 import BeautifulSoup

def main(argv):
    try:
        opts, args = getopt.getopt(argv,"i:",["ifile="])
    except getopt.GetoptError:
        usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt in ("-i", "--ifile"):
            inputfile = arg
    
    f = open(inputfile)      # simplified for the example (no urllib)
    soup = BeautifulSoup(f, features="html.parser")
    f.close()
    
    g_a = soup.findAll(id="headerTableEntry")  # the elements from inside the div a element
    alst = []                                # the future result list
    for x in g_a:
        for elem in x.findAll('div'):        # the divs inside the div a
            print elem.contents              # just to see what is inside
            alst.append(elem.contents[0].strip('\n\t ,'))  # collect the wanted info

    print alst               # wanted result in a technical form
    print ', '.join(alst)    # wanted result as a string (items separated by comma and space


def usage():
    print ' ------------------------------------------------'
    print ' Mrunmoy Samal (mrunmoy@gmail.com) , 2018'
    print ' python coverage_parser.py -i coverage-html-filename'
    print ' ------------------------------------------------'


#-------------------------------
if __name__ == "__main__":
    main(sys.argv[1:])

