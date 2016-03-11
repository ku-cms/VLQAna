#!/bin/python

import subprocess

options = [
           #['cutflow'],
           #['npv_noreweight'],
           #['npv'],
           #['ptak4leading'],
           #['etaak4leading'],
           #['ptak42nd'],
           #['etaak42nd'],
           #['ptak8leading'],
           #['etaak8leading'],
           #['ptak82nd'],
           #['etaak82nd'],
           #['nzelel'],
           ['pt_leading_el'],
           #['pt_2nd_el'],
           #['dr_elel'],
           #['mass_elel'],
           #['pt_zelel'],
           #['st'],
           #['ht'],
           #['nak4'],
           #['nak8'],
           #['nbjets'],
           #['ptbjetleading'],
           #['etabjetleading'],
           #['mTprime'],
    ]

command = 'python plot.py --var={0:s}'

for option in options :
    s = command.format(
        option[0]
        )

    subprocess.call( ["echo --------------------------------------------------------------------------",""], shell=True)
    subprocess.call( ["echo --------------------------------------------------------------------------",""], shell=True)
    subprocess.call( ["echo %s"%s,""]                                                                      , shell=True)
    subprocess.call( ["echo --------------------------------------------------------------------------",""], shell=True)
    subprocess.call( ["echo --------------------------------------------------------------------------",""], shell=True)
    subprocess.call( [s, ""]                                                                               , shell=True)
