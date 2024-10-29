#open ./compartido/seriaResult and ./compartido/mpiResult and export to excel
import os
import pandas as pd

"""
#Structure of seriaResult
it may have blank lines at the beginning and end
```

%n_subintervals%, %iter%
%time%
$n_subintervals%, %iter%
%time%
...
%n_subintervals%, %iter%
%time%
"""

resultList = []

with open('/home/zerotwo/hpc.docker/compartido/serialResultMatrix', 'r') as f:
    fileBuffer = f.read().split('\n')
    #remove blank lines
    fileBuffer = list(filter(None, fileBuffer))
    continueFlag = True
    while continueFlag:
        try:
            n_subintervals, iter = fileBuffer.pop(0).split(',')
            time = fileBuffer.pop(0)
            resultList.append({'n_subintervals': n_subintervals, 'iter': iter, 'time': time})
        except:
            continueFlag = False
    
df = pd.DataFrame(resultList)
df = df.sort_values(by=['n_subintervals'])
df.to_csv('/home/zerotwo/hpc.docker/serialResultMatrix.csv', index=True)

"""
#Structure of mpiResult
it may have blank lines at the beginning and end
```

%num_processes%, %n_subintervals%, %iter%
%time%
%num_processes%, %n_subintervals%, %iter%
%time%
...
%num_processes%, %n_subintervals%, %iter%
%time%
"""

resultList = []

with open('/home/zerotwo/hpc.docker/compartido/mpiResultMatrix', 'r') as f:
    fileBuffer = f.read().split('\n')
    #remove blank lines
    fileBuffer = list(filter(None, fileBuffer))
    continueFlag = True
    while continueFlag:
        try:
            num_processes, n_subintervals, iter = fileBuffer.pop(0).split(',')
            time = fileBuffer.pop(0)
            resultList.append({'num_processes': num_processes, 'n_subintervals': n_subintervals, 'iter': iter, 'time': time})
        except:
            continueFlag = False
    
df = pd.DataFrame(resultList)
df = df.sort_values(by=['n_subintervals', 'num_processes'])
df.to_csv('/home/zerotwo/hpc.docker/mpiResultMatrix.csv', index=True)
    