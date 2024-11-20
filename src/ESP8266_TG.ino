#include <FastBot2.h>
#include <string>

FastBot2 bot;
int64_t chat_id;
void update (fb::Update& u){
    // Добавляем конкретный список userov tg (id)


    // Нужно inline конпку сделать,
    // когда прилетает да, то мы посылаем сигнал по пину и после отправляет измененное сообщение
    // что открыли или просто новое отправляем
    chat_id = u.message().from().id();
    fb::Message msg;
    msg.text = u.message().text().str();
    msg.chatID = chat_id;
    bot.sendMessage(msg);
   
}

void setup() {
  Serial.begin(115200);

  // Тут дополнить подключение к wifi

  bot.setToken("7282964831:AAFpXPLc0eODNVYyO5QNGbrzgDYIfKC3wGE");
  bot.skipUpdates(0);
  bot.setLimit(3);
  bot.setPollMode(fb::Poll::Sync, 4000);
  bot.attachUpdate(update);
}

void loop() {
  bot.tick();
}
