import requests
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import dates as  pltdates
from matplotlib import gridspec
import discretepatterns as dispat
import json
from datetime import datetime


# URLS for the http endpoint 
furnaceTempUrl = #inser URL
furnaceStatusUrl = #insert URL

#get requests and deserialization
furnaceStatus = requests.get(furnaceStatusUrl)
furnaceStatusJson = furnaceStatus.json()
furnaceStatusValues =furnaceStatusJson['results'][0]["value"]

furnaceTemp = requests.get(furnaceTempUrl)
furnaceTempJson = furnaceTemp.json()
furnaceTempValues = furnaceTempJson['results'][0]["value"]

# extracting relevant data
furnaceTempHist = []
furnaceStatHist = []
for i in range(0,3):
    furnaceStatHist.append(furnaceStatusValues[i]["history"])
    furnaceTempHist.append(furnaceTempValues[i]["history"])

# creating the subplots and spacing them
fig = plt.figure()
gs  = gridspec.GridSpec(2, 1, height_ratios=[1, 0.25])
tempPlot = plt.subplot(gs[0])
statusPlot = plt.subplot(gs[1])

# looping 3 times for each machine to plot on the same graph
for j in range(0, 3):
# clearing arrays for the loops
    time = []
    temp = []
    for x in furnaceTempHist[j]:
        time.append(x[0])
        temp.append(x[1])

# setting up the data to be sorted
    temp = list(map(float, temp))
    time = pd.to_datetime(time)
    time.sort_values()

    # labeling my string plots for the legend
    nameString = "Furnace " + str(j+1)
    tempPlot.plot_date(time, temp, linestyle='solid', marker='', label=nameString)

# formatting the x axis and setting up labels for the temperature plot
date_format = pltdates.DateFormatter('%H')
tempPlot.xaxis.set_major_formatter(date_format)
tempPlot.set_title('Temperature Over Time')
tempPlot.set_xlabel('Time (Hours)')
tempPlot.set_yticks(np.arange(min(temp)-1, max(temp)+1, 100))
tempPlot.set_ylabel('Temperature (Deg C)')
tempPlot.legend()



# now we do the status plot
# setting up the inpupts and taking on the applicable values from the json document
time = []
state = []
for x in furnaceStatHist[1]:
    time.append(x[0])
    state.append(x[1])
    
# sorting the data to fit for the given code
state = list(map(int, state))
time = pd.to_datetime(time)
time.sort_values()

# from the sample code given
index = pd.DatetimeIndex(time)
df = pd.DataFrame(state, index=index)
dp = dispat.DiscretePatterns()
dp.SetDataframe(df)
dp.Ready()
timeframes = dp.GetAllTimeframes(0)

# setting up arrays for later use
timely = []
timely2 = []
timely3 = []
totimely = []
totimely2 = []
totimely3 = []

# converting all time stamps to pydatetime types so that I can do accurate subtraction to determine the length of a bar in the graph
for i in range(0, 6):
    timely.append(pd.Timestamp.to_pydatetime(timeframes[1][i][0]))
    timely2.append(pd.Timestamp.to_pydatetime(timeframes[2][i][0]))
    timely3.append(pd.Timestamp.to_pydatetime(timeframes[3][i][0]))
    totimely.append(pd.Timestamp.to_pydatetime(timeframes[1][i][1]))
    totimely2.append(pd.Timestamp.to_pydatetime(timeframes[2][i][1]))
    totimely3.append(pd.Timestamp.to_pydatetime(timeframes[3][i][1]))
        

# plotting the values onto a bar graph
    # the colors dont quite match up to the pdf
for i in range(0, 6):
    statusPlot.broken_barh([(timely[i], totimely[i]-timely[i])], (0, 1), facecolors='tab:green')
    statusPlot.broken_barh([(timely2[i], totimely2[i]-timely2[i])], (0, 1), facecolors='tab:red')
    statusPlot.broken_barh([(timely3[i], totimely3[i]-timely3[i])], (0, 1), facecolors='olive')
    statusPlot.broken_barh([(timely[i], totimely[i]-timely[i])], (1, 1), facecolors='olive')
    statusPlot.broken_barh([(timely2[i], totimely2[i]-timely2[i])], (1, 1), facecolors='tab:green')
    statusPlot.broken_barh([(timely3[i], totimely3[i]-timely3[i])], (1, 1), facecolors='tab:red')
    statusPlot.broken_barh([(timely[i], totimely[i]-timely[i])], (2, 1), facecolors='tab:red')
    statusPlot.broken_barh([(timely2[i], totimely2[i]-timely2[i])], (2, 1), facecolors='olive')
    statusPlot.broken_barh([(timely3[i], totimely3[i]-timely3[i])], (2, 1), facecolors='tab:green')


#labeling the status graph, and setting the y axis labels to machine numbers
statusPlot.set_yticks(ticks=[1,2,3])
statusPlot.set_yticklabels(labels=['#1', '#2','#3'])
statusPlot.set_title('Machine Status Over Time')
statusPlot.set_ylabel('Machine')
statusPlot.set_xlabel('Time (Hours)')

#formatting the x label so it is not an ugly string showing the date-time
    #can edit this to show more than just the Hour as necessary
date_format = pltdates.DateFormatter('%H')
statusPlot.xaxis.set_major_formatter(date_format)


#Showing the graph
plt.tight_layout()
plt.show()
