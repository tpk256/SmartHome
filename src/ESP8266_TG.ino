#include <FastBot2.h>
#include <cstring>

#define D2 4
#define D1 5



FastBot2 bot;
int64_t chat_id;
const char* SSID = "tps";
const char* PASSWORD = "2743113077"; 


void update_get_keyboard(fb::Update& u){
  fb::Message msg;
  fb::InlineMenu menu;
  msg.chatID = u.message().chat().id();

  if ( strcmp(u.message().text().c_str(), "/menu") == 0){
    msg.text = "Open the door?\0";
    menu.addButton("Yes", "open_door_yes");
    menu.addButton("No", "open_door_no");
    msg.setInlineMenu(menu);
  }
  else{
    msg.text = "I can't understand this command, use please /menu\0";
  }
  bot.sendMessage(msg);

}


void update_open_door(fb::Update& u){

}


void update (fb::Update& u){
    // Добавляем конкретный список userov tg (id)


    // Нужно inline конпку сделать,
    // когда прилетает да, то мы посылаем сигнал по пину и после отправляет измененное сообщение
    // что открыли или просто новое отправляем
    

    // ЛОГИКА ПОСЫЛАЕТСЯ КОМАНДА МЕНЮ, А МЫ ИНЛАЙН КНОПКУ ОТКРЫИТЬ
  
    if (u.isQuery()){
        update_open_door(u);
     }
    else if (u.isMessage()){
        update_get_keyboard(u);
    }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(SSID,  PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected");

  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW); 
  bot.setToken("7282964831:AAFpXPLc0eODNVYyO5QNGbrzgDYIfKC3wGE");
  bot.skipUpdates(0);
  bot.setLimit(3);
  bot.setPollMode(fb::Poll::Sync, 4000);
  bot.attachUpdate(update);
}

void loop() {
  bot.tick();
}
