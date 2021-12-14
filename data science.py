import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
from datetime import datetime
from pandas_datareader import data

matplotlib.rcParams['font.family']='Malgun Gothic'
matplotlib.rcParams['axes.unicode_minus'] = False

data1 = pd.read_csv('c:/2018.csv',encoding='euc-kr')
data2 = pd.read_csv('c:/2019.csv',encoding='euc-kr')
data3 = pd.read_csv('c:/2020.csv',encoding='euc-kr')

data = pd.concat([data1, data2, data3])
data.set_index('구분',inplace=True)
data

ans2 = data.copy()
ans2.index = pd.to_datetime(ans2.index, format='%Y년%m월')
ans2.set_index([ans2.index.year,ans2.index.month], inplace=True)
ans2.index.names = ['년도','월']
ans2

y = ans2.groupby('년도').mean()[['사망(명)']]
m = ans2.groupby('월').mean()[['사망(명)']]
y, m

ans2.loc[2018][['사망(명)','부상(명)']].plot(kind='bar',rot=0)
ans2.loc[2019][['사망(명)','부상(명)']].plot(kind='bar',rot=0)
ans2.loc[2020][['사망(명)','부상(명)']].plot(kind='bar',rot=0)
plt.show()