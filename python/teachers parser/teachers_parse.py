from bs4 import BeautifulSoup
import requests
import pandas as pd
from pprint import pprint

def main():
    page = requests.get("https://www.rudn.ru/sveden/employees/pps/index.html")
    print("Status code: ", page.status_code)
    if page.status_code != 200:
        print("Connection failed.")
        return
    else:
        print("Connected successful.")
    soup = BeautifulSoup(page.text, "lxml")
    table = soup.find("table").find("tbody")
    attributes = table.find("tr").find_all("th")
    teachers_info = dict()
    for col in table.find("tr").find_all("td"):
        try:
            #print(col.attrs["itemprop"])
            teachers_info[col.attrs["itemprop"]] = list()
        except KeyError:
            #print(col)
            teachers_info["number"] = list()
    for row in table.find_all("tr"):
        for col in row.find_all("td"):
            try:
                attr_name = col.attrs["itemprop"]
            except KeyError:
                attr_name = "number"
            teachers_info[attr_name].append(col.text.strip('\n').strip())
    del teachers_info["number"]
    teachers_df = pd.DataFrame(teachers_info)
    teachers_df.to_csv("teachers.csv")

if __name__ == "__main__":
    main()