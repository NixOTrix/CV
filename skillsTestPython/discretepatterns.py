import pandas as pd

#Class to extract timeframes from discrete-valued data.
class DiscretePatterns:
    def __init__(self):
        self.frame = None
        self.any = False
        self.discs = []
        self.conts = []

    #Add a specific column of discrete data to the dataframe
    def AddDiscrete(self,name,table):
        table = table.rename(columns={'value': name})
        if self.any == False:
            self.any = True
            self.frame = table
        else:
            self.frame = self.frame.join(table,how='outer')        
        self.discs.append(name)

    #Add a specific column of analogue data to the dataframe
    def AddAnalog(self,name,table):
        table = table.rename(columns={'value': name})
        if self.any == False:
            self.any = True
            self.frame = table
        else:
            self.frame = self.frame.join(table,how='outer')
        self.conts.append(name)

    #Set the dataframe to use as the base.
    def SetDataframe(self,frame):
        self.frame = frame

    def combinefunction(self, collist, row):
        val = 0
        for i in range(0,len(collist)):
            val = val + (row[collist[i]] * (i+1))
        return val

    def CombineDigital(self,collist,result):
        self.frame[result] = self.frame.apply(lambda row: int(self.combinefunction(collist,row)),axis=1)

        for n in collist:
            self.frame.drop(n,axis=1,inplace=True)        

    #Perform any interpolation on analogue channels, and forward/backfilling on discrete channels.
    def Ready(self):
        for n in self.conts:
            self.frame[n] = self.frame[n].interpolate(method='linear')
        self.frame = self.frame.fillna(method='backfill')
        self.frame = self.frame.fillna(method='ffill')
        return self.frame

    #Get the time frames for every discrete value present
    def GetAllTimeframes(self, colname):
        frames = {}
        distinct = self.frame[colname].unique()
        for val in distinct:
            #print("Requesting Times For " + str(val))
            tf = self.GetTimeframesFor(lambda row: row[colname] == val)
            v = int(val)
            for n in tf:
                try:
                    frames[v].append(n)
                except:
                    frames[v] = []
                    frames[v].append(n)
        return frames

    #Get the time frames for only those times where the lambda function is 'true'
    def GetTimeframesFor(self,lamb):
        
        frames = []

        seri = self.frame.apply(lamb, axis=1)
 
        lasttime = None
        for n in seri.iteritems():
            if n[1] == True:
                if lasttime is None:
                    lasttime = n[0]
            else:
                if lasttime is not None:
                    frames.append((lasttime,n[0]))
                    lasttime = None
        if lasttime is not None:
            frames.append((lasttime,n[0]))
        
        return frames

    #Get the data present within the lambda function time frames
    def GetInFrameData(self,lamb):
        timeframes = self.GetTimeframesFor(lamb)

        #print(timeframes)

        df = None
        for tf in timeframes:        
            active = self.frame[tf[0] : tf[1]]
            if df is None:
                df = active
            else:                
                df = df.append(active)

        return df

    #Get the total number of seconds that the lambda function is true
    def GetTotalTimeFor(self, lamb):
        timeframes = self.GetTimeframesFor(lamb)

        #print(str(timeframes))

        ttltime = 0
        for tf in timeframes:        
            active = self.frame[tf[0] : tf[1]]            
            mintime = active.index.min()
            maxtime = active.index.max()            

            ttltime = ttltime + float(pd.Timedelta(maxtime - mintime).total_seconds())

        return ttltime

    #Get the total number of seconds in the dataframe
    def GetTotalTime(self):
        mintime = self.frame.index.min()
        maxtime = self.frame.index.max()        

        amnt = float(pd.Timedelta(maxtime - mintime).total_seconds())

        return amnt
