import requests
from bs4 import BeautifulSoup
import pandas
 
 
source = requests.get('https://www.weather.go.kr/weather/observation/currentweather.jsp')
soup = BeautifulSoup(source.content,"html.parser")
 
table = soup.find('table',{'class':'table_develop3'})
data = []
 
print("#"*30)
print("\nHello! Here's today's weather!\n")
print("#"*30)

print(len(table.find_all('tr')))
 
for idx, tr in enumerate(table.find_all('tr')):
    tds = list(tr.find_all('td'))
    #print(len(tds))
    for td in tds:
        if td.find('a') and (idx == 32 or idx == 40 or idx == 42):
            #point = td.find('a').text
            
            temp = tds[5].text
            humidity = tds[9].text
            data.append([temp,humidity])
    
print("#"*30)
print("\nIt ends here. thanks!\n")
print("#"*30)
 
print(data)
 
with open('weather.csv','w') as f:
    f.write('temp, humidity\n')
    for i in data:
        f.write('{0},{1}\n'.format(i[0],i[1]))

