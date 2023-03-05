import telebot
from telebot import types
import requests

token = input("Введите токен бота:\n")
bot = telebot.TeleBot(token)
print("Бот работает.")


@bot.message_handler(commands=['start'])
def start(msg):
    # Рисуем кнопки.
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    btn1 = types.KeyboardButton("Начать")
    markup.add(btn1)
    # Отправляем приветствие и даем пользователю нажать на кнопку.
    bot.send_message(msg.from_user.id,
                     f"Приветствую, {msg.from_user.first_name}! Начать?",
                     reply_markup=markup)


@bot.message_handler(content_types=["text"])
def talk(msg):
    if msg.text.title() == "Начать" or msg.text.title() == "Продолжить":
        bot.send_message(msg.from_user.id, "Введите сумму всех ваших товаров в долларах")
        bot.register_next_step_handler(msg, get_rur)  # Перенаправляем пользователя на ввод суммы (get_rur()).


def get_rur(msg):
    # Отправляет пользователю итоговую цену с комиссией.
    try:
        usd_amount = float(msg.text)  # Если пользователь введет что-то, кроме числа, вызывается исключение.
        if usd_amount <= 0:
            raise Exception  # Также при ненатуральном значении вызовем исключение.

        # Вытаскиваем из API ЦБРФ текущий курс доллара.
        url = "https://www.cbr-xml-daily.ru/daily_json.js"
        data = requests.get(url).json()
        usd_to_rur = data["Valute"]["USD"]["Value"]

        # Считаем комиссию и отправляем итог пользователю.
        if (usd_amount / 10) <= 15:
            result_with_fee = usd_amount + 15
        elif (usd_amount / 10) > 15:
            result_with_fee = usd_amount * 1.10
        bot.send_message(msg.from_user.id,
                         f"Ваш общий заказ на сумму: {round(result_with_fee * usd_to_rur, 2)} рублей.")

        error = False  # Исключений не случилось.
    except:
        # Если было вызвано исключение, даем пользователю ввести сумму еще раз и вызываем функцию заново.
        error = True
        bot.send_message(msg.from_user.id, "Вы точно ввели сумму правильно? Попробуйте снова.")
        bot.register_next_step_handler(msg, get_rur)

    if not error:
        # Если исключение не было вызвано, предлагаем пользователю продолжить.
        markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
        btn1 = types.KeyboardButton("Продолжить")
        markup.add(btn1)
        bot.send_message(msg.from_user.id,
                         "Продолжим?",
                         reply_markup=markup)

bot.polling(none_stop=True)  # Запускаем.
