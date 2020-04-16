# Author: Oleksii Poleshchuk
#
# KU Leuven 2016-2020
#
# This script is used for automatic file name generation used in
# the SpecMATSim_TotalNoRes_Analysis_AddBack.C script
#
# \file createFileNameForGEANT4sortingEnergyScanAddBack.py
#
f = open("generatedFileNamesEnergyScanAddBack.txt", "w+")


def formatNumber(num):
    if num % 1 == 0:
        return int(num)
    else:
        return num


for i in range(20, 300, 10):
    j = i/1000
    j = formatNumber(j)
    print(j)
    f.write('convertRoot("AddBack_CeBr3_48mmx48mmx48mm_15x1x3crystals_R131.25mm_gamma' + str(j) + 'MeV_Aluminum5083_Chamber_wallThick_3mm_linear_sourcePosition_129mm_FCEpoxy_epoxy_gap3mm", ' + str(j) + ', ' + str(i) + ',1);\n')
for i in range(300, 2000, 100):
    j = i/1000
    j = formatNumber(j)
    print(j)
    f.write('convertRoot("AddBack_CeBr3_48mmx48mmx48mm_15x1x3crystals_R131.25mm_gamma' + str(j) + 'MeV_Aluminum5083_Chamber_wallThick_3mm_linear_sourcePosition_129mm_FCEpoxy_epoxy_gap3mm", ' + str(j) + ', ' + str(i) + ',1);\n')
for i in range(2000, 16000, 1000):
    j = i / 1000
    j = formatNumber(j)
    print(j)
    f.write('convertRoot("AddBack_CeBr3_48mmx48mmx48mm_15x1x3crystals_R131.25mm_gamma' + str(j) + 'MeV_Aluminum5083_Chamber_wallThick_3mm_linear_sourcePosition_129mm_FCEpoxy_epoxy_gap3mm", ' + str(j) + ', ' + str(i) + ',1);\n')
f.close()
