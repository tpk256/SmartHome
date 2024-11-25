#include <FastBot2.h>
#include <cstring>
#include "utilsT.h"



#define D2 4
#define D1 5
#define LEN_COMMAND_ADD_USER 9



OnlyAccessUsers data_bot;
FastBot2 bot;

const char* SSID = "tps";
const char* PASSWORD = "2743113077"; 


// Работу со структурой сделать через команды.

bool isCommand(const char* text){
    return text[0] == '/';
}

// void update_get_keyboard(fb::Update& u){
//     fb::Message msg;
//     fb::InlineMenu menu;
//     msg.chatID = u.message().chat().id();
    
    

//     if ( strcmp(, "/door") == 0){
//       msg.text = "Open the door?\0";
//       menu.addButton("Yes", "open_door_yes");
//       menu.addButton("No", "open_door_no");
//       msg.setInlineMenu(menu);
//     }
//     else{
//       msg.text = "I can't understand this command, use please /door\0";
//     }
//     bot.sendMessage(msg);

// }

void executeCommand(fb::Update& u){
    fb::Message msg;
    fb::Menu menu;
    msg.chatID = u.message().chat().id();
    const char *command = u.message().text().c_str(), *userId = u.message().from().id().c_str();
    if (!isCommand(command)){
      msg.text = "Please use command";
      bot.sendMessage(msg);
      return;
    }
    if (!strcmp("/start", command)){
      if(data_bot.HasAdmin())
          if (!data_bot.ExistUser(userId)) {
              msg.text = "ACCESS DENIED!";
              bot.sendMessage(msg);
              return;
          }
            
      else
        data_bot.AddAdmin(userId);
        
        menu.addButton("/help").addButton("/door");
        msg.setMenu(menu);
    }
    else if(!strcmp("/door", command) && data_bot.ExistUser(userId)){
      // Дописать реализацию
    }
    else if (!strcmp("/help", command) && (data_bot.ExistUser(userId) || data_bot.IsAdmin(userId))){
      // Вывод справочной информации

    }
    else if(
      !strncmp("/add_user", command, LEN_COMMAND_ADD_USER) && 
      data_bot.IsAdmin(userId)){
      

    }
    else if(!strcmp("/delete_users", command ) && 
      data_bot.IsAdmin(userId)){
      // Дописать реализацию
    }
    else if(!strcmp("/reset_admin", command) && 
      data_bot.IsAdmin(userId)){
      // Дописать реализацию
    }
    else{
      msg.text = "Unknown command!\0";

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
        executeCommand(u);
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
