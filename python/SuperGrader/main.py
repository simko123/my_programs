from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC


def parse_cool_buttons_id(url, driver):
    cool_buttons_id = []
    html = driver.page_source # сохраняем разметку в переменную
    soup = BeautifulSoup(html, "lxml") # создаем суп объект для парсинга
    rows = soup.find_all("tr") # собираем строки таблицы
    for row in rows:
        if row.find_all("input"):
            # если столбцы в строке таблицы кликабельны, сохраняем айди последней кнопки
            cool_buttons_id.append(list(row.find_all("input"))[-1]["id"])
    return cool_buttons_id


def select_webdriver():
    webdriver_number = int(input(
        "Выберите ваш браузер (номер):\n"
        "1. Firefox\n"
        "2. Chrome\n"
        "3. Edge\n"
        "4. Safari\n"
        ">>> ")
    )
    print("\n\n\n")
    if webdriver_number == 1:
        return webdriver.Firefox()
    elif webdriver_number == 2:
        return webdriver.Chrome()
    elif webdriver_number == 3:
        return webdriver.Edge()
    elif webdriver_number == 4:
        return webdriver.Safari()


def main():
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
          "--------- S U P E R _ G R A D E R ---------\n"
          "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n")
    driver = select_webdriver()
    url = input("Введите ссылку на оценивание первой лабы\n"
                "(осторожно, ошибочный ввод не предусмотрен)\n"
                ">>> ")
    driver.get(url)
    input("Сейчас я открою страницу, но сначала удостоверьтесь, что вы авторизованы.\n"
          "Когда удостоверитесь, нажмите Enter.")
    cool_btns_id = parse_cool_buttons_id(url, driver) # собираем айди кнопок
    # и циклом оцениваем шесть лаб включая свою
    for i in range(6):
        for cool_btn_id in cool_btns_id:
            WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.ID, cool_btn_id))).click()
        WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.NAME, "saveandshownext"))).click()
        WebDriverWait(driver, 10)
    WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.NAME, "saveandclose"))).click()
    input("Нажмите Enter, чтобы выйти из программы...")
    driver.close()


if __name__ == "__main__":
    main()
