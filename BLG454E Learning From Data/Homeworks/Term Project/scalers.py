# Mustafa Can Caliskan, 150200097
# Yusuf Sahin, 150200016


import numpy as np


def zscoreNormalization(data):
    meanColumn = np.nanmean(data, axis=0)
    stdColumn = np.nanstd(data, axis=0)
    stdColumn[stdColumn == 0] = 1
    normalized_data = (data - meanColumn) / stdColumn
    return normalized_data


def minmaxNormalized(data):
    minCol = np.nanmin(data, axis=0)
    columns_max = np.nanmax(data, axis=0)
    colMinMax = columns_max - minCol
    colMinMax[colMinMax == 0] = 1
    normalizedData = (data - minCol) / colMinMax
    return normalizedData
